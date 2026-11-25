#include "radiolib_transport.h"
RadioLibTransport::RadioLibTransport()
: module(new Module(PIN_LORA_NSS, PIN_LORA_DIO0, PIN_LORA_RST, PIN_LORA_DIO1)),
  radio(new SX1276(module)) {}
bool RadioLibTransport::begin() {
  SPI.begin(PIN_LORA_SCK, PIN_LORA_MISO, PIN_LORA_MOSI, PIN_LORA_NSS);
  int16_t state=radio->begin(SLMP_RF_FREQUENCY_MHZ);
  if(state!=RADIOLIB_ERR_NONE) { Serial.printf("Radio init error: %d\n", state); return false; }
  radio->setOutputPower(10);
  radio->setBandwidth(125.0);
  radio->setSpreadingFactor(9);
  radio->setCodingRate(7);
  radio->setCRC(true);
  ready=true;
  radio->startReceive();
  return true;
}
bool RadioLibTransport::send(const uint8_t* data,size_t length) {
  if(!ready || !data || !length) return false;
  int16_t state=radio->transmit(const_cast<uint8_t*>(data),length);
  radio->startReceive();
  if(state!=RADIOLIB_ERR_NONE) Serial.printf("TX error: %d\n",state);
  return state==RADIOLIB_ERR_NONE;
}
int RadioLibTransport::receive(uint8_t* buffer,size_t capacity) {
  if(!ready || !buffer || !capacity) return 0;
  size_t n=radio->getPacketLength();
  if(!n) return 0;
  if(n>capacity) { radio->startReceive(); return -1; }
  int16_t state=radio->readData(buffer,n);
  radio->startReceive();
  if(state!=RADIOLIB_ERR_NONE) return -1;
  return static_cast<int>(n);
}
