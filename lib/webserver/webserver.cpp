#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

WebServer::WebServer(){

}

String WebServer::GetPage() {
	String page;
	page = "<html><head><title>ESP-W3</title></head> ";
	page += "<body> ";
	page += "<h1>ESP-02</h1> ";
	page += "<p>Temperature: <strong> ";
	page += String(Dht11::GetTemperature(),2);
	page += "*</strong> </p> ";
	page += "<p>Huminidity: <strong> ";
	page += String(Dht11::GetHuminidity(),2);
	page += "%</strong> </p> ";
	page += "<h2>Head</h2>";
	page += "<a href='/headleft'>&larr;</a> <a href='headcenter'>&uarr;</a> <a href='/headright'>&rarr;</a> <br/> ";
	page += "<h2>Move</h2>";
	page += "<a style='margin-left: 20px;' href='/forward'>&uarr;</a> <br/> <a href='/left'>&larr;</a>  <a href='/back'>&darr;</a> <a href='/right'>&rarr;</a>  </body></html>";

	return page;
}



WebServer::~WebServer() {
	// TODO Auto-generated destructor stub
}

void WebServer::Setup(Movement movement, Look look, const char* ssid, const char* password, const char* hostname) {

	this->move = movement;
	this->look = look;

	this->look.Setup(D0);

	Logger::Write("Connecting to ");
	Logger::Write(ssid);
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Logger::Write(".");
	}
	Logger::Write(" Connected");

	// Print the IP address
	Logger::Write("Url: ");
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
		this->server.send(200, "text/html", this->GetPage());
	});

	server.on("/forward", [&](){
		this->move.GoForward(moveAmount);
		this->server.send(200, "text/html", this->GetPage());
	});

	this->server.on("/back", [&](){
		this->move.GoBack(moveAmount);
		this->server.send(200, "text/html", this->GetPage());
	});

	this->server.on("/left", [&](){
		this->move.TurnLeft(rotateAmount);
		this->server.send(200, "text/html", this->GetPage());
	});

	this->server.on("/right", [&](){
		this->move.TurnRight(rotateAmount);
		this->server.send(200, "text/html", this->GetPage());
	});

	this->server.on("/headleft", [&](){
		this->look.Left(headVerticalSteps);
		this->server.send(200, "text/html", this->GetPage());
	});


	this->server.on("/headcenter", [&](){
		this->look.SetAngle(90);
		this->server.send(200, "text/html", this->GetPage());
	});

	this->server.on("/headright", [&](){
		this->look.Right(headVerticalSteps);
		this->server.send(200, "text/html", this->GetPage());
	});

	this->server.begin();
}

void WebServer::Serve(){
	this->server.handleClient();
	this->move.Loop();
	this->look.Think();
}
