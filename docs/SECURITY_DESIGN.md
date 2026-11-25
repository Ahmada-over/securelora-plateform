# Security Design

Menaces visées : écoute passive, modification, frames forgées, rejeu, duplication, confusion de session, réutilisation accidentelle de nonce.

Contrôles : PSK par paire; challenge-response mutuel lié aux deux identités et nonces frais; HKDF-SHA-256 avec labels de domaine; AES-256-GCM; clés directionnelles et préfixes distincts; header comme AAD; fenêtre anti-rejeu; retransmission des octets exacts; fail-closed si RNG/authentification échoue.

Limites : métadonnées radio visibles, brouillage et déni de service non empêchés, capture physique/firmware compromis hors garantie. LoRa ne garantit ni livraison ni disponibilité.

Tests : mauvais PSK, transcript altéré, AAD/ciphertext/tag altéré, rejeu, doublon, ancien paquet après nouvelle session, reset, épuisement de séquence, RNG indisponible.
