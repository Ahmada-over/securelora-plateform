# SLMP 1.0 — Spécification technique

Statut : baseline de conception à figer par vecteurs de test avant implémentation interopérable.

## Périmètre
Transport de messages courts H2H et M2M sur lien direct. Pas de routage multi-sauts, LoRaWAN ou fragmentation avancée en v1.0.

## Confiance et clés
Chaque paire autorisée dispose d'une PSK 256 bits distincte, provisionnée hors bande. L'identifiant d'appareil n'est pas une preuve d'identité. Pas de PSK universelle pour toute une flotte.

## Suite cryptographique
- AEAD : AES-256-GCM
- KDF : HKDF-SHA-256
- Authentification handshake : HMAC-SHA-256
- Nonce GCM : 96 bits
- Tag : 128 bits
- Aléatoire : source cryptographique ESP32; échec fermé si non disponible.

Clés directionnelles distinctes. Nonce = préfixe de session directionnel 32 bits || compteur 64 bits big-endian. Le préfixe est dérivé par HKDF avec séparation de domaine. Le compteur ne reboucle jamais. Une session doit être détruite avant épuisement.

## Handshake
HELLO, HELLO_ACK, FINISH, SESSION_READY. Le transcript authentifié lie le protocole/version, rôles, IDs des deux pairs, deux nonces frais, types et capacités négociées. Les deux côtés authentifient le même transcript canonique avec labels de rôle distincts. HKDF dérive les clés A→B et B→A, préfixes de nonce et clés de confirmation à partir de la PSK, des nonces et du hash de transcript. Les dispositions binaires exactes et labels HKDF doivent être figés dans des vecteurs connus avant implémentation.

## En-tête
Tous les entiers sont big-endian. En-tête fixe de 21 octets :
- version: 1
- type: 1
- source_id: 2
- destination_id: 2
- session_id: 4
- sequence: 8
- flags: 1
- payload_length: 2

Trame chiffrée : `header[21] || ciphertext[payload_length] || tag[16]`. L'en-tête complet est AAD GCM. Il reste visible et constitue une métadonnée.

## Types provisoires
0x01 HELLO, 0x02 HELLO_ACK, 0x03 FINISH, 0x04 SESSION_READY, 0x05 DATA, 0x06 ACK, 0x07 PING, 0x08 PONG, 0x09 CLOSE, 0x0A ERROR.

## DATA et profils
Payload binaire typé : H2H_TEXT, M2M_TELEMETRY, EVENT. JSON uniquement pour outils de débogage.

## Fiabilité
ACK chiffré/authentifié dans le sens inverse, avec son propre nonce/sequence. Le contenu identifie la séquence acquittée. L'émetteur conserve la trame sérialisée exacte et retransmet les mêmes octets. Le récepteur authentifie avant de mettre à jour l'anti-rejeu et ne livre jamais deux fois le même DATA.

## Anti-rejeu
Fenêtre par session et direction. Authentifier avant de modifier l'état. Rejeter doublons et paquets hors fenêtre.

## Taille radio
La limite de payload n'est pas fixée à 160 octets par principe. Calculer la taille totale en-tête+ciphertext+tag et vérifier la limite radio, le temps d'occupation et les règles locales. Fragmentation hors v1.

## Reset
L'état de session est en RAM. Reset = session invalidée, clés effacées et nouveau handshake requis. Aucun DATA avant confirmation mutuelle.
