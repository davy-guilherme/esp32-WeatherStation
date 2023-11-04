#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include <SimpleDHT.h>


// WebServer
const char* ssid = "SOCRATES";
const char* password = "21061993";
WebServer server(80);

// DHT11
int pinDHT11 = 23;
SimpleDHT11 dht11(pinDHT11);

int temperatura = 0;

void handleRoot () {

  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); 
    Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); 
    Serial.println(SimpleDHTErrDuration(err)); 
    return;
  }

  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");

  String html = "<html><body>";
  html += "<h1>Temperatura 2:</h1>";
//  html += "<p>" + String((int)temperature) + " &#8451;</p>";  // Mostra o símbolo de grau Celsius
  html += "<p>";
  html += (int)temperature;
//  html += (int)temperatura;
  html += " &#8451;</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);

}

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

//  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  
}

void loop() {
  // start working...
//  Serial.println("=================================");
//  Serial.println("Sample DHT11...");

//  byte temperature = 0;
//  byte humidity = 0;
//  int err = SimpleDHTErrSuccess;
//  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
//      Serial.print("Read DHT11 failed, err="); 
//      Serial.print(SimpleDHTErrCode(err));
//      Serial.print(","); 
//      Serial.println(SimpleDHTErrDuration(err));
//      delay(1000);
//      return;
//  }
//  temperatura = (int)temperature;

  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
//delay(2000);
  
}
