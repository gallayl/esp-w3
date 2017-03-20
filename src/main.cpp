#include <Arduino.h>
#include <Servo.h>
#include <movement.h>
#include <webserver.h>
#include <logger.h>
#include <look.h>
#include <Dht11.h>

Movement move = Movement();
WebServer server = WebServer();
Look look = Look();

const char* WifiSsid = "Gallay_Guest";
const char* WifiPass = "P@ssw0rd1";
const char* HostName = "ESP-W2";

//The setup function is called once at startup of the sketch
void setup() {
  delay(100);
  Serial.begin(9600);
  Dht11::Setup();
  Logger::Setup();
  Logger::WriteLine("Booting E2-W...");
	//move.Setup(D0, D2, D1);

	server.Setup(move, look, WifiSsid, WifiPass, HostName);
}

// The loop function is called in an endless loop
void loop() {
	server.Serve();
}
