#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/*Put your SSID & Password*/
const char* ssid = "TECHNOLOGICS- Embedded IoT";
const char* password = "l0($kR#!u@oP8)#@$Fy#2!PK0";

ESP8266WebServer server(80);

uint8_t light = D2;
uint8_t fan = D3;
bool lightstatus = LOW;
bool fanstatus = LOW;

void setup() {
  Serial.begin(9600);
  delay(100);
  pinMode(light, OUTPUT);
  pinMode(fan, OUTPUT);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.on("/lon", handle_lighton);
  server.on("/loff", handle_lightoff);
  server.on("/fon", handle_fanon);
  server.on("/foff", handle_fanoff);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
  if (lightstatus) {
    digitalWrite(light, HIGH);
    Serial.println("LIGHT is ON");
  }
  if (!lightstatus) {
    digitalWrite(light, LOW);
    Serial.println("LIGHT is OFF");
  }
  if (fanstatus) {
    digitalWrite(fan, HIGH);
    Serial.println("FAN is ON");
  }
  if (!fanstatus) {
    digitalWrite(fan, LOW);
    Serial.println("FAN is OFF");
  }
}

void handle_OnConnect() {
  lightstatus = LOW;
  fanstatus = LOW;
  server.send(200, "text/html", SendHTML(false));
}

void handle_lighton() {
  lightstatus = HIGH;
  server.send(200, "text/html", SendHTML(true));
}

void handle_lightoff() {
  lightstatus = LOW;
  server.send(200, "text/html", SendHTML(false));
}

void handle_fanon() {
  fanstatus = HIGH;
  server.send(200, "text/html", SendHTML(true));
}

void handle_fanoff() {
  fanstatus = LOW;
  server.send(200, "text/html", SendHTML(false));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t led) {
  String ptr = "<!DOCTYPE html>\n";
  ptr += "<html>\n";
  ptr += "<head>\n";
  ptr += "<title>HOME AUTOMATION</title>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
