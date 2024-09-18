
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

#include <ArduinoJson.h>

ESP8266WiFiMulti WiFiMulti;

//JsonDocument doc;
DynamicJsonDocument doc(1000);

char i=0;

bool connection_test_F=0;
bool advance_serial_F=0;
bool advance_url_F=0;
bool send_to_server_F=0;


char advance_json_serial[50];
char advance_json_url[50];

char temp[200];
int temp_i=0;

char travel_time_send_F;
char door_control_type_send_F;


void setup() {

  Serial.begin(9600);
  // Serial.setDebugOutput(true);

  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("kave", "123456789");
}



void loop() {

  if ((WiFiMulti.run() == WL_CONNECTED) && ( send_to_server_F )) {

    WiFiClient client;

    HTTPClient http;

    String url_http = "http://www.ravis-gsm.ir/GSM_RAVIS/gsm_connection.php?";

    if( advance_serial_F){ advance_serial_F=0;
      url_http += "serial=";
      url_http += advance_json_serial;
      url_http += "&"; 
    }

    if( advance_url_F){ advance_url_F=0;
      url_http += advance_json_url;
      url_http += "&"; 
    }

    if( connection_test_F){ connection_test_F=0;
      url_http += "connection_test=?";
      url_http += "&"; 
    }

    Serial.println(url_http);

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client,url_http )) {  // HTTP

      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        //Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          
          String payload = http.getString();

          //Serial.println("HTTP_DATA=");
          Serial.println(payload);
          //Serial.println("----------");

          //DeserializationError error = deserializeJson(doc, payload);
          //serializeJson(doc, Serial);

        }
      } 
      else {
        //Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        Serial.println("{\"error\":\"http_code\",}");
      }

      http.end();

      advance_serial_F=0;
      connection_test_F=0;
      advance_url_F=0;
      send_to_server_F=0;

    } else {
      Serial.println("{\"error\":\"http_begin\",}");
    }
  }
  else{

    if ((WiFiMulti.run() == WL_CONNECTED) ){}
    else Serial.println("{\"error\":\"wifi\",}");
    
  }



  while( Serial.available() == 0 ){}
  delay(10);
  Serial.println("*");

  if ( Serial.available() > 0 ){ 

    while( 1 ){
      while( Serial.available() > 0 ){

        char data=0;
        data = Serial.read();

        temp[temp_i] = data;
        temp_i++;

      }
      delay(10);
      if( Serial.available() == 0 )break;
    }

    temp[temp_i] = '\n';

    //Serial.println(temp);
    Serial.println("#");

    if( strstr(temp,"}") - (char *)&temp[0] > 0  ){

      Serial.println("ESP_GET_JSON");

      deserializeJson(doc, temp);
      read_json_advance();

    }

    memset( temp ,0,200);
    temp_i=0;
  }

}
