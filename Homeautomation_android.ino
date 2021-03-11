#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);
const char* ssid = "TECHNOLOGICS- Embedded IoT";
const char* password = "l0($kR#!u@oP8)#@$Fy#2!PK0";
String  command = ""; // Command received from Android device

// Set Relay Pins
int geyser = D1;
int fan = D2;

void setup()
{
  Serial.begin(115200);

  pinMode(geyser, OUTPUT);
  pinMode(fan, OUTPUT);

  digitalWrite(geyser, LOW);
  digitalWrite(fan, LOW);

  connectWiFi();
  server.begin();
}

void loop()
{
  client = server.available();
  if (!client) return;
  command = checkClient ();
  Serial.println(command);

  if (command == "gon"  )        {
    digitalWrite(geyser, 1);
    Serial.println("geyser is ON");
  }
  else if (command == "goff" )     {
    digitalWrite(geyser, 0);
    Serial.println("geyser is OFF");
  }
  else if (command == "fon"  )     {
    digitalWrite(fan, 1);
    Serial.println("FAN is ON");
  }
  else if (command == "foff" )   {
    digitalWrite(fan, 0);
    Serial.println("FAN is OFF");
  }
  sendBackEcho(command); // send command echo back to android device
  command = "";
}

/* connecting WiFi */
void connectWiFi()
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
}

/* check command received from Android Device */
String checkClient (void)
{
  while (!client.available()) delay(1);
  String request = client.readStringUntil('\r');
  Serial.println(request);
  request.remove(0, 5);
  request.remove(request.length() - 9, 9);
  return request;
}

/* send command echo back to android device */
void sendBackEcho(String echo)
{
  client.println("HTTP/1.1 200 OK ");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println(echo);
  client.println("</html>");
  client.stop();
  delay(1);
}
