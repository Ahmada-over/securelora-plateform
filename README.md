# SecureLoRa — Platforme de communication sécurisée

Dépôt de démarrage pour SLMP 1.0 : architecture, spécification et projet PlatformIO ESP32.

**État réel :** les documents définissent la conception cible. Le firmware fourni est uniquement un test de transport LoRa brut via le port série. Il n'implémente pas encore le chiffrement, le handshake, les ACK SLMP ou l'anti-rejeu. Ne pas le présenter comme une messagerie sécurisée.

## Matériel
LILYGO T3 V1.6.1 / LoRa32 V2.1.6, ESP32, SX127x. Vérifier le marquage exact du module radio et la fréquence autorisée avant toute émission.

Brochage T3 V1.6.1 non-TCXO utilisé : SCK=5, MISO=19, MOSI=27, NSS=18, RESET=23, DIO0=26, DIO1=33. OLED SDA=21, SCL=22. Confirmer sur le schéma de la révision exacte.

## Compilation
1. Ouvrir le dossier dans VS Code + PlatformIO.
2. Définir `SLMP_RF_FREQUENCY_MHZ` après vérification de la variante radio et des règles locales.
3. `pio run`
4. `pio run -t upload`
5. `pio device monitor`

Le firmware n'émet pas automatiquement au démarrage. Saisir une ligne dans le moniteur série pour envoyer un texte de test. Ce texte n'est pas chiffré.

## Sécurité
- Ne jamais committer de secret.
- Ne jamais réutiliser un nonce AES-GCM avec la même clé.
- Les retransmissions doivent renvoyer les mêmes octets chiffrés.
- Un reset invalide la session volatile et impose un nouveau handshake.
- Le header public doit être authentifié comme AAD.
- Pas de routage multi-sauts dans la v1.0.

## Références
- LILYGO : https://wiki.lilygo.cc/products/t3-series/t3-lora32/
- PlatformIO : https://docs.platformio.org/en/latest/platforms/espressif32.html
- RadioLib : https://github.com/jgromes/RadioLib
