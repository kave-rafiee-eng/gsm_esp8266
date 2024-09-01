#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
 
/* Put your SSID & Password */
const char* ssid = "NodeNCU";  // Enter SSID here
const char* password = "123456789";  //Enter Password here
 
/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(0,0,0,0);
 
ESP8266WebServer server(80);
 
bool LED1status = LOW;
 
bool LED2status = LOW;
 
void setup() {
  Serial.begin(115200);

  Serial.print("Setting soft-AP ... ");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);
 
  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.onNotFound(handle_NotFound);
   
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
 
  server.handleClient();

   
}
 
void handle_OnConnect() {

  Serial.println("GPIO7 Status: OFF | GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status)); 
}
 
void handle_led1on() {
  LED1status = HIGH;
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(true,LED2status)); 
}
 
void handle_led1off() {
  LED1status = LOW;
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(false,LED2status)); 
}
 
void handle_led2on() {
  LED2status = HIGH;
  Serial.println("GPIO6 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,true)); 
}
 
void handle_led2off() {
  LED2status = LOW;
  Serial.println("GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,false)); 
}
 
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
 
String SendHTML(uint8_t led1stat,uint8_t led2stat){

  /*String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
  ptr +="<h3>Using Access Point(AP) Mode</h3>\n";
   
   if(led1stat)
  {ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}
 
  if(led2stat)
  {ptr +="<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}
 
  ptr +="</body>\n";
  ptr +="</html>\n";*/

  String ptr = "";

  ptr +="      <!doctype html> ";

  ptr +="      <html >";
  ptr +="      <head>";
      
   ptr +="         <meta charset=\"UTF-8\">";
   ptr +="         <title>WIFI Setting</title>";

  ptr +="          <style>";

  ptr +="              body {";
  ptr +="                  background: #456;";
   ptr +="                 font-family: 'Open Sans', sans-serif;";
  ptr +="              }";

  ptr +="              .login {";
  ptr +="                  width: 400px;";
  ptr +="                 margin: 16px auto;";
  ptr +="                 font-size: 16px;";
  ptr +="                 direction: rtl;";
  ptr +="             }";

  ptr +="             .login-header,";
  ptr +="            .login p {";
  ptr +="                  margin-top: 0;";
  ptr +="                  margin-bottom: 0;";
  ptr +="              }";
  ptr +="              .login-triangle {";
  ptr +="                  width: 0;";
  ptr +="                  margin-right: auto;";
  ptr +="                  margin-left: auto;";
  ptr +="                  border: 12px solid transparent;";
  ptr +="                  border-bottom-color: #28d;";
  ptr +="              }";

  ptr +="              .login-header {";
  ptr +="                  background: #28d;";
  ptr +="                  padding: 20px;";
  ptr +="                  font-size: 1.4em;";
  ptr +="                  font-weight: normal;";
  ptr +="                  text-align: center;";
  ptr +="                  text-transform: uppercase;";
  ptr +="                  color: #fff;";
  ptr +="              }";

  ptr +="              .login-container {";
  ptr +="                  background: #ebebeb;";
  ptr +="                  padding: 12px;";
  ptr +="              }";


  ptr +="              .login p {";
  ptr +="                  padding: 12px;";
  ptr +="              }";

  ptr +="              .login input {";
  ptr +="                  box-sizing: border-box;";
  ptr +="                  display: block;";
  ptr +="                  width: 100%;";
  ptr +="                  border-width: 1px;";
  ptr +="                  border-style: solid;";
  ptr +="                  padding: 16px;";
  ptr +="                  outline: 0;";
  ptr +="                  font-family: inherit;";
  ptr +="                  font-size: 0.95em;";
  ptr +="              }";

  ptr +="              .login input[type=\"email\"],";
  ptr +="              .login input[type=\"password\"] {";
  ptr +="                  background: #fff;";
  ptr +="                  border-color: #bbb;";
  ptr +="                  color: #555;";
  ptr +="              }";


  ptr +="              .login input[type=\"email\"]:focus,";
  ptr +="              .login input[type=\"password\"]:focus {";
  ptr +="                  border-color: #888;";
  ptr +="              }";

  ptr +="              .login input[type=\"submit\"] {";
  ptr +="                  background: #28d;";
  ptr +="                  border-color: transparent;";
  ptr +="                  color: #fff;";
  ptr +="                  cursor: pointer;";
  ptr +="              }";

  ptr +="              .login input[type=\"submit\"]:hover {";
  ptr +="                  background: #17c;";
  ptr +="              }";


  ptr +="              .login input[type=\"submit\"]:focus {";
  ptr +="                  border-color: #05a;";
  ptr +="              }";

  ptr +="          </style>";


  ptr +="      </head>";


  ptr +="      <body >";

  ptr +="          <div >";

  ptr +="              <div class=\"login\" action=\"\" >";
  ptr +="                  <div class=\"login-triangle\"></div>";
  ptr +="                  <h2 class=\"login-header\">wifi setting</h2>";
  ptr +="                  <form class=\"login-container\">";
  ptr +="                      <p><input type=\"email\" placeholder=\"name\"></p>";
  ptr +="                      <p><input type=\"password\" placeholder=\"password\"></p>";
  ptr +="                      <p><input type=\"submit\" value=\"save\"></p>";
  ptr +="                 </form>";
  ptr +="              </div>";

  ptr +="          </div>";

  ptr +="      </body>";



  return ptr;
}