#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESP32_Servo.h>

const char* ssid     = "Tele2_325de9";
const char* password = "fjyirmn5";

#define SERVO_PIN 23

// Set your Static IP address
IPAddress local_IP(192, 168, 0, 15);
// Set your Gateway IP address
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4);  //optional

AsyncWebServer server(80);
Servo servo;

void setup(){
  Serial.begin(115200);
  
  servo.attach(SERVO_PIN);

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String message = "Send a number from 0 to 180 to set the servo position";
    request->send(200, "text/plain", message);
    servo.write(0);
    servo.write(180);
    delay(500);
    servo.write(0);
  });

  // server.on("/servo", HTTP_GET, [](AsyncWebServerRequest *request){
  //   String pos = request->getParam("pos")->value();
  //   servo.write(pos.toInt());
  //   request->send(200, "text/plain", "Servo moved");
  // });

  server.begin();
}

void loop(){}
