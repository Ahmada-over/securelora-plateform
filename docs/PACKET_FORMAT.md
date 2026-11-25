# SLMP Packet Format

En-tête fixe de 21 octets, entiers big-endian :
offset 0 version(1), 1 type(1), 2 source_id(2), 4 destination_id(2), 6 session_id(4), 10 sequence(8), 18 flags(1), 19 payload_length(2).

Trame chiffrée : header || ciphertext || tag GCM 16 octets. Le nonce est reconstruit depuis le préfixe directionnel et la séquence. Handshake possède un format et transcript HMAC séparés.

Validation : longueur minimale, version/type, longueur exacte, pair/session/direction, vérification AEAD avec header AAD, puis seulement mise à jour anti-rejeu et livraison.
