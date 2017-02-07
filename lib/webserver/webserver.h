#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <movement.h>
#include <look.h>
#include <logger.h>

class WebServer {
public:
	WebServer();
	virtual ~WebServer();
	String GetIpAddress();

	void Setup(Movement move, Look look, const char* ssid, const char* password, const char* hostname);
	void Serve();

private:
	char ssid[];
	char password[];
	Movement move;
	Look look;
	String ipAddress;
	ESP8266WebServer server;
	MDNSResponder mdns;
	String page;
	void SetupResponses();

};

#endif /* WEBSERVER_H_ */
