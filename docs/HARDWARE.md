# Hardware Baseline

Carte attendue : LILYGO T3 V1.6.1 / LoRa32 V2.1.6 ESP32. Variante SX1276 attendue pour la version annoncée 868/915 MHz, mais confirmer le marquage du module et la fréquence permise localement.

Brochage non-TCXO : LoRa SCK=5, MISO=19, MOSI=27, NSS=18, RESET=23, DIO0=26, DIO1=33; OLED SDA=21, SCL=22; SD CS=13, MOSI=15, MISO=2, SCK=14; batterie ADC=35; LED=25.

Le starter n'utilise que les pins radio. Vérifier le schéma exact avant branchement. GPIO33 est input-only. Respecter les règles locales sur fréquence, puissance, largeur de bande et airtime.
