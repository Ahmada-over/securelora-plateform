#include <Arduino.h>
#include "slmp_config.h"
#include "radiolib_transport.h"
RadioLibTransport transport;
uint8_t rx[ MAX_TEST_TEXT + 1 ];
void setup() {
  Serial.begin(115200); delay(700);
  Serial.printf("\\nSecureLoRa raw radio test — device 0x%04X\\n",SLMP_DEVICE_ID);
  if(!transport.begin()) Serial.println("Radio initialization failed.");
  else Serial.println("Ready. Type a line and press Enter. WARNING: plaintext test only.");
}
void loop() {
  static String line;
  while(Serial.available()) {
    char c=static_cast<char>(Serial.read());
    if(c=='\\r') continue;
    if(c=='\\n') {
      if(line.length()) transport.send(reinterpret_cast<const uint8_t*>(line.c_str()),line.length());
      line="";
    } else if(line.length()<MAX_TEST_TEXT) line+=c;
  }
  int n=transport.receive(rx,sizeof(rx)-1);
  if(n>0) { rx[n]=0; Serial.printf("[RX] %s\\n",reinterpret_cast<char*>(rx)); }
  delay(5);
}
