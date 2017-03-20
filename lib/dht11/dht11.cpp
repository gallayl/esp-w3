#include "Dht11.h"

DHT dht(D4, DHT11);

void Dht11::Setup(){
  dht.begin();
}

int Dht11::GetTemperature(){
  return dht.readTemperature();
}

int Dht11::GetHuminidity(){
  return  dht.readHumidity();
}
