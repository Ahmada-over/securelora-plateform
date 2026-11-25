# Architecture SecureLoRa

## Vision
Plateforme modulaire de communication authentifiée et confidentielle pour terminaux humains (H2H) et objets connectés (M2M), sans dépendance Internet en P2P.

## Couches
1. Matériel : ESP32, SX127x, capteurs, écran, clavier.
2. Transport : interface indépendante `SlmpTransport`; première implémentation RadioLib.
3. Protocole : framing, types, adressage, sessions, séquences.
4. Sécurité : PSK par paire, authentification mutuelle, HKDF, AES-GCM, anti-rejeu.
5. Services : messagerie, télémétrie, événements, ACK.
6. Applications : Messenger, IoT, passerelle/supervision locale.

Le cœur SLMP ne doit importer aucune classe RadioLib. La passerelle et le routage multi-sauts sont hors périmètre v1.0.

## Matériel
T3 V1.6.1 non-TCXO : SPI SCK 5, MISO 19, MOSI 27; NSS 18, RESET 23, DIO0 26, DIO1 33; OLED I2C 21/22. Confirmer avec le schéma de la carte réelle.
