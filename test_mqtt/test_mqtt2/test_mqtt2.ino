
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


const char* ssid = "kave";
const char* password = "123456789";
const char* mqtt_server =  "84.47.232.10";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

DynamicJsonDocument doc(1000);


int serial_device=0;
bool serial_get=0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    if( Serial.available() > 0 ) { 
      while( 1 ){
        while( Serial.available() > 0 ){
          Serial.read();
        }
        if( Serial.available() == 0 )break;
        delay(10);
      } 
      Serial.println("{\"error\":\"wifi\",}");
    }
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();


}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    //Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    
    String clientId = "ESP8266Client-";
  
    clientId += String(random(0xffff), HEX);

    Serial.print(clientId+"/");
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe

      char str[100];
      sprintf(str,"server/%d",serial_device);
      client.subscribe(str);


    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying

      int timer=0;
      while(1){

        if( Serial.available() > 0 ) { 
          while( 1 ){
            while( Serial.available() > 0 ){
              Serial.read();
            }
            if( Serial.available() == 0 )break;
            delay(10);
          } 
          if( WiFi.status() == WL_CONNECTED) { Serial.println("{\"error\":\"mqtt\",}"); }
          else { Serial.println("{\"error\":\"wifi\",}"); }
        }    
        delay(10);

        timer++;
        if( timer >= 300 ){ timer=0; break; }

      }
      

    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}


void loop() {

  if( serial_get == 1 ){

    if (!client.connected()) {
      reconnect();
    }
    client.loop();
  }

  
  while (WiFi.status() != WL_CONNECTED) {
    if( Serial.available() > 0 ) { 
      while( 1 ){
        while( Serial.available() > 0 ){
          Serial.read();
        }
        if( Serial.available() == 0 )break;
        delay(10);
      } 
      Serial.println("{\"error\":\"wifi\",}");
    }
  }


  char temp[300];
  char mqtt_message[300];
  char temp_i=0;

  if ( Serial.available() > 0 ){ 

    memset( temp ,0,300);

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

    if( strstr(temp,"}") - (char *)&temp[0] > 0  ){

      Serial.println("ESP_GET_JSON");

      deserializeJson(doc, temp);
      String serial = doc["serial"];
      char temp_serial[50];

      if( serial == "null"){}
      else { 
        //serial.toCharArray(temp_serial, serial.length()+1);
        //strncpy(advance_json_serial, temp_serial, sizeof advance_json_serial);   

       serial_device = serial.toInt();
       serial_get = 1;

       Serial.println("serial_get---");

      }

    }

    //Serial.print("DATA = ");
    //Serial.println(temp);

    if( serial_get == 1 ){ client.publish("gsm", temp); 
      Serial.println("{\"@empty\":\"1\",}");
    }
    else{  Serial.println("{\"@empty\":\"1\",\"@mass\":\"serial_not_init\"}"); }


    
  }
}

//{serial:"100",}
