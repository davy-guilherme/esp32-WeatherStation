#include "index.h" // Inclui o arquivo "index.h"

#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <SimpleDHT.h>
//
//const char* ssid = "2.4G_Apto94";
//const char* password = "gatinhos";
const char* ssid = "CONEXAO LENTA 2.4G";
const char* password = "solderachar00!";
WebServer server(80);

int pinDHT11 = 23;
SimpleDHT11 dht11(pinDHT11);

int temperatura = 0;
int humidade = 0;


void medirTemperaturaHumidade () {

  Serial.println("Vai medir");

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

//  *temperaturaPtr = (int)temperature;
  temperatura = (int)temperature;
  humidade = (int)humidity;

}
void handleRoot() {
  // byte temperature = 0;
  // byte humidity = 0;
  // int err = SimpleDHTErrSuccess;

  // if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
  //   Serial.print("Read DHT11 failed, err=");
  //   Serial.print(SimpleDHTErrCode(err));
  //   Serial.print(",");
  //   Serial.println(SimpleDHTErrDuration(err));
  //   return;
  // }

  // temperatura = (int)temperature; // Atualiza a variável global com a temperatura atual.

  medirTemperaturaHumidade ();

//  String html = "<html><body>";
//  html += "<h1>Temperatura:</h1>";
//  html += "<p id='temperatura'>";
//  html += temperatura;
//  html += " &#8451;</p>"; // rever
//  html += "<script>";
//  html += "setInterval(function() {";
//  html += "  var xhttp = new XMLHttpRequest();";
//  html += "  xhttp.onreadystatechange = function() {";
//  html += "    if (this.readyState == 4 && this.status == 200) {";
//  html += "      document.getElementById('temperatura').innerHTML = this.responseText;";
//  html += "    }";
//  html += "  };";
//  html += "  xhttp.open('GET', '/get-temperatura', true);";
//  html += "  xhttp.send();";
//  html += "}, 5000);"; // Atualiza a temperatura a cada 5 segundos.
//  html += "</script>";
//  html += "</body></html>";
//  server.send(200, "text/html", html);

  // Substitui o marcador de posição %TEMPERATURE% pelo valor real da temperatura
  String response = String(html_content);
  response.replace("%TEMPERATURE%", String(temperatura));
  server.send(200, "text/html", response);
}

void handleGetTemperatura() {
  medirTemperaturaHumidade();
  server.send(200, "text/plain", String(temperatura) + " &#8451;");
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("teste")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/get-temperatura", HTTP_GET, handleGetTemperatura); // Adiciona um novo endpoint para buscar a temperatura.

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
  delay(2);
}
