
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

#include <ArduinoJson.h>

ESP8266WiFiMulti WiFiMulti;

//JsonDocument doc;
DynamicJsonDocument doc(1000);

char travel_time[10];
char door_control_type[10];

char temp[100];

char travel_time_send_F;
char door_control_type_send_F;

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();
  
  //char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
  
  Serial.println();
  Serial.println();
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("kave", "123456789");
}



void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    String url = "http://www.ravis-gsm.ir/GSM_RAVIS/gsm_connection.php?serial=100&";

    if( travel_time_send_F){travel_time_send_F=0;
      url += "name1=general*travel_time";
      url += "&"; 
      url += "data1=";
      url += travel_time; 
      url += "&"; 
    }

    if( door_control_type_send_F){door_control_type_send_F=0;
      url += "name1="; 
      url += "general*door*control_type";
      url += "&"; 
      url += "data1=";
      if( door_control_type == "null" )url +="68";
      url += door_control_type; 
      url += "&"; 
    }

    Serial.println(url);

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client,url )) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          
          String payload = http.getString();

          Serial.println("HTTP_DATA=");
          Serial.println(payload);
          Serial.println("----------");

          DeserializationError error = deserializeJson(doc, payload);
          //serializeJson(doc, Serial);

          Serial.println("JSON_DATA=");
          read_json();
          Serial.println("------end_json----"); 

        }
      } 
      else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.println("[HTTP] Unable to connect");
    }
  }

  delay(500);



}
