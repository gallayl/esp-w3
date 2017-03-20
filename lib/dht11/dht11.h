#ifndef EDHT11_H_
#define EDHT11_H_

#include <DHT.h>
#include <logger.h>

class Dht11 {
public:
  static void Setup();
  static int GetTemperature();
  static int GetHuminidity();
};

#endif
