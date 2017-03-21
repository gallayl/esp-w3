#include "Dht11.h"

DHT dht(D4, DHT11);

void Dht11::Setup(){
  dht.begin();
}

float Dht11::GetTemperature(){
  return dht.readTemperature();
}

float Dht11::GetHuminidity(){
  return  dht.readHumidity();
}
