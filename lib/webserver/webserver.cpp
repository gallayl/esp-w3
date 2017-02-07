#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

WebServer::WebServer() {
	this->page = "<html><head><title>ESP-W3</title></head> ";
	this->page += "<body> ";
	this->page += "<h1>ESP-02</h1> ";
	this->page += "<h2>Head</h2>";
	this->page += "<a href='/headleft'>&larr;</a> <a href='headcenter'>&uarr;</a> <a href='/headright'>&rarr;</a> <br/> ";
	this->page += "<h2>Move</h2>";
	this->page += "<a style='margin-left: 20px;' href='/forward'>&uarr;</a> <br/> <a href='/left'>&larr;</a>  <a href='/back'>&darr;</a> <a href='/right'>&rarr;</a>  </body></html>";
}

WebServer::~WebServer() {
	// TODO Auto-generated destructor stub
}

void WebServer::Setup(Movement movement, Look look, const char* ssid, const char* password, const char* hostname) {

	this->move = movement;
	this->look = look;

	this->look.Setup(D3);

	Logger::Write("Connecting to ");
	Logger::Write(ssid);
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Logger::Write(".");
	}
	Logger::WriteLine("");
	Logger::Write("WiFi connected");

	// Print the IP address
	Logger::Write("Use this URL to connect: ");
	Logger::Write("http://");
	Logger::Write(WiFi.localIP().toString());
	Logger::WriteLine("/");

	this->server = ESP8266WebServer(80);
	this->SetupResponses();
	this->server.begin();
}

const int moveAmount = 250;
const int rotateAmount = 250;

const int headVerticalSteps = 50;

void WebServer::SetupResponses(){
	this->server.on("/", [&](){
		this->server.send(200, "text/html", page);
	});

	server.on("/forward", [&](){
		this->move.GoForward(moveAmount);
		this->server.send(200, "text/html", page);
	});

	this->server.on("/back", [&](){
		this->move.GoBack(moveAmount);
		this->server.send(200, "text/html", page);
	});

	this->server.on("/left", [&](){
		this->move.TurnLeft(rotateAmount);
		this->server.send(200, "text/html", page);
	});

	this->server.on("/right", [&](){
		this->move.TurnRight(rotateAmount);
		this->server.send(200, "text/html", page);
	});

	this->server.on("/headleft", [&](){
		this->look.Left(headVerticalSteps);
		this->server.send(200, "text/html", page);
	});


	this->server.on("/headcenter", [&](){
		this->look.SetAngle(90);
		this->server.send(200, "text/html", page);
	});

	this->server.on("/headright", [&](){
		this->look.Right(headVerticalSteps);
		this->server.send(200, "text/html", page);
	});

	this->server.begin();
}

void WebServer::Serve(){
	this->server.handleClient();
	this->move.Loop();
	this->look.Think();
}
