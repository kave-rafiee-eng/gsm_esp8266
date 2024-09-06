
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

#include <ArduinoJson.h>

ESP8266WiFiMulti WiFiMulti;

//JsonDocument doc;
DynamicJsonDocument doc(1000);

char i=0;

bool advance_read_F=0;
bool advance_send_F=0;
bool advance_serial_F=0;

char advance_json_name_w1[50];
char advance_json_data_w1[50];

char advance_json_name_r1[50];
char advance_json_data_r1[50];

char travel_time[10];
char door_control_type[10];

char temp[200];
int temp_i=0;

char travel_time_send_F;
char door_control_type_send_F;

String uart_data;

void setup() {

  Serial.begin(9600);
  // Serial.setDebugOutput(true);

  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("kave", "123456789");
}



void loop() {

  if ((WiFiMulti.run() == WL_CONNECTED) && (advance_send_F ||  advance_read_F || advance_serial_F)) {

    WiFiClient client;

    HTTPClient http;

    String url = "http://www.ravis-gsm.ir/GSM_RAVIS/gsm_connection.php?serial=100&";

    if( advance_send_F){advance_send_F=0;
      url += "name1=";
      url += advance_json_name_w1;
      url += "&"; 
      url += "data1=";
      url += advance_json_data_w1; 
      url += "&"; 
    }

    Serial.println(url);

    //Serial.print("[HTTP] begin...\n");
    if (http.begin(client,url )) {  // HTTP

      //Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
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
      }

      http.end();

      advance_send_F=0;
      advance_read_F=0;
      advance_serial_F=0;

    } else {
      Serial.println("[HTTP] Unable to connect");
    }
  }
  else{

    if ((WiFiMulti.run() == WL_CONNECTED) ){}
    else Serial.println("WIFI....");
    
  }

//{"name_w1":"advance_settin*general*travel_time","data_w1":10,}

//{"name_r1":"advance_settin*general*travel_time","data_r1":10,}
//{"name_r1":"-","data_r1":1,}
//{"name_w1":"advance_settin*general*travel_time","data_w1":10,"name_r1":"advance_settin*general*travel_time","data_r1":10,}

  
  /*i++;

  if( i>5 ){ i=0;
    advance_serial_F=1;
    //advance_serial_F=1;
  }*/

  while( Serial.available() == 0 ){}
  delay(100);
  Serial.println(".");

  if ( Serial.available() > 0 ){ 

    while( Serial.available() > 0 ){

      char data=0;
      data = Serial.read();
      //if( data = '}'){
        temp[temp_i] = data;
        temp_i++;
      //}

    }

    temp[temp_i] = '\n';

    /*for(i=0; i<40; i++ ){

      Serial.write(temp[i]);
    }*/
    //Serial.println(temp);
    //uart_data += Serial.readString();

    //uart_data.toCharArray(temp, uart_data.length()+1);
    //strncpy(temp, uart_data, sizeof temp); 

    if( strstr(temp,"}") - (char *)&temp[0] > 0  ){

      advance_serial_F=1;
      //Serial.println(temp);

      deserializeJson(doc, temp);
      read_json_advance();

      uart_data.remove(0, uart_data.length()+1);

    }

    memset( temp ,0,200);
    temp_i=0;
    
  }

  /*if( advance_send_F == 1 ){ advance_send_F=0;
    Serial.println("advance_send_F ->");
    Serial.print("advance_name_w1 = ");
    Serial.println( advance_json_name_w1);
    Serial.print("advance_data_w1 = ");
    Serial.println( advance_json_data_w1);
    Serial.println("--------------");
    Serial.println(" ");
    Serial.println(" ");
    Serial.println(" ");
  }

  if( advance_read_F == 1 ){ advance_read_F=0;
    Serial.println("advance_read_F ->");
    Serial.print("advance_name_r1 = ");
    Serial.println( advance_json_name_r1);
    Serial.print("advance_data_r1 = ");
    Serial.println( advance_json_data_r1);
    Serial.println("--------------");
    Serial.println(" ");
    Serial.println(" ");
    Serial.println(" ");
  }*/

}
