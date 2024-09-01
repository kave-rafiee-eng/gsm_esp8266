#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "LittleFS.h"
#include <FS.h>
 
/* Put your SSID & Password */
const char* ssid = "RAVIS";  // Enter SSID here
const char* password = "123456789";  //Enter Password here
 
/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(0,0,0,0);
 
ESP8266WebServer server(80);
 
void handleRoot();
void handleLogin();

void setup() {
  Serial.begin(115200);
  
  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }
  
  Serial.print("Setting soft-AP ... ");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, NULL);
 
  server.on("/", HTTP_GET, handleLogin);
  server.onNotFound(handle_NotFound);
   
  server.begin();
  Serial.println("HTTP server started");

  //handleLogin();
  
  byte data[10000];
  int i=0;
  
  File file = LittleFS.open("/wifi_setting.txt", "r");
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }
  
  String myString = file.readString();
  file.close();

  Serial.println(myString);
  
}
void loop() {
 
  server.handleClient();
  
}

// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);
  return String();
}

  String wifi_name ="kave2" ;
  String wifi_pass = "1234";
  
void handleLogin() {
                   
  /*if( ! server.hasArg("username") || ! server.hasArg("password") 
      || server.arg("username") == NULL || server.arg("password") == NULL) { // If the POST request doesn't have username and password data
    server.send(400, "text/plain", "400: Invalid Request");         // The request is invalid, so send HTTP status 400
    return;
  }
  if(server.arg("username") == "John Doe" && server.arg("password") == "password123") { // If both the username and the password are correct
    server.send(200, "text/html", "<h1>Welcome, " + server.arg("username") + "!</h1><p>Login successful</p>");
  } else {                                                                              // Username and password don't match
    server.send(401, "text/plain", "401: Unauthorized");
  }*/

  Serial.println("hadle_login");

  if( sizeof(server.arg("name")) > 1 ){
    
    wifi_name = server.arg("name");
    wifi_pass = server.arg("password");

  }

  

  Serial.println(wifi_name);
  Serial.println(wifi_pass);

  File file = LittleFS.open("/wifi_setting.txt", "r");
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.println("File Content:");
  
  String myString = file.readString();
  file.close();  

  myString.replace("wifi_name", wifi_name);
  myString.replace("wifi_password", wifi_pass);
  myString.replace("device_serial", "device_serialxxx");

  server.send(200, "text/html", myString); 

  // server.send(LittleFS, "/index.html", String(), false, processor);
  
}
 
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
 
String SendHTML(uint8_t led1stat,uint8_t led2stat){
  String ptr;
  return ptr;
}
