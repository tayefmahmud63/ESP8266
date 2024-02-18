#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266WebServer.h>

WiFiClient client;
const char* ssid = "SSID"; // replace ssid
const char* password = "PASSWORD"; //replace password

// Define API endpoints
const char* apiEndpoint1 = "https://api-bdc.net/data/client-ip"; // api for fetch the public ip


ESP8266WebServer server(80);

String getDataFromAPI(const char* endpoint) {  //function for getting JSON from api's

  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure); 
  client->setInsecure();
  
  HTTPClient httpClient;
  httpClient.begin(*client,endpoint);
  int httpCode = httpClient.GET();
  String data = "";
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      data = httpClient.getString();
    }
  }
  httpClient.end();
  return data;
}

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // Print ESP8266 local IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Handle root URL request
  server.on("/", HTTP_GET, []() {


  JsonDocument doc; //Initialing JSON Document 1
 
 deserializeJson(doc, getDataFromAPI(apiEndpoint1)); // deserialize public ip JSON
   const char* ipString = doc["ipString"];
   Serial.print(String(ipString));
   
    String response = "<h1>Your Public IP : </h1><p>" + String(ipString) + "</p>";
    server.send(200, "text/html", response);
  });

  // Start server
  server.begin();
  Serial.println("HTTP server started");
}
void loop(){
   server.handleClient();
  }

  
