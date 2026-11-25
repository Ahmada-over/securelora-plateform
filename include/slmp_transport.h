#pragma once
#include <Arduino.h>
class SlmpTransport {
public:
  virtual ~SlmpTransport() = default;
  virtual bool begin() = 0;
  virtual bool send(const uint8_t* data, size_t length) = 0;
  virtual int receive(uint8_t* buffer, size_t capacity) = 0;
};
