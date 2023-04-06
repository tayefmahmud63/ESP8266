#include<ESP8266WiFi.h>

void setup() {

  Serial.begin(115200); //initializing the buad rate
  WiFi.mode(WIFI_STA); // initializing the mode of the board
  WiFi.begin("SSID","PASSSWORD"); // replace the ssid with your wifi ssid and password with your wifi password

  while(WiFi.status() !=WL_CONNECTED ){ //checking the board in connected with wifi or not 

    Serial.print(".");
    delay(200);
  }
  Serial.println(WiFi.localIP()); // this will print the ip address the board is assigned 
}

void loop() {


}