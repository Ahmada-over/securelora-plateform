# Test Plan

Bring-up : radio initialisée avec configuration régionale validée, envoi/réception dans les deux sens.

Protocoles : encode/decode, endianness, type/version inconnus, troncature, longueur incohérente.

Crypto : vecteurs AES-GCM, HKDF et HMAC; mauvais PSK; modification AAD/ciphertext/tag; clés directionnelles distinctes; unicité nonce.

Rejeu/fiabilité : doublon non livré deux fois, hors fenêtre rejeté, ACK valide, ACK invalide rejeté, retransmission octets identiques, ancien paquet rejeté après nouvelle session.

Performance : latence, PDR, RSSI/SNR, paramètres modem et airtime, heap/stack, flash et consommation mesurée.

Ne pas déclarer SLMP sécurisé/conforme avant réussite des vecteurs cryptographiques, handshake, anti-rejeu et intégration deux cartes.
