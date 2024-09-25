#include <ESP8266WiFi.h>

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

/****** WiFi Connection Details *******/
const char* ssid = "kave";
const char* password = "123456789";

/******* MQTT Broker Connection Details *******/
/* hive mq
const char* mqtt_server = "52769f07854f438f863fc8ef379b9b79.s1.eu.hivemq.cloud";
const char* mqtt_username = "ravis";
const char* mqtt_password = "25482548Mo";
const int mqtt_port =8883;*/
//0005.0306.0260.035
//IPAddress mqtt_server(5,198,176,233);
IPAddress mqtt_server(5, 198, 176, 233);

#define MQTT_HOST  "5.198.176.233"
#define MQTT_PORT  1883

const char* mqtt_username = "";
const char* mqtt_password = "";
const int mqtt_port =8080;

/**** Secure WiFi Connectivity Initialisation *****/
WiFiClientSecure espClient;

/**** MQTT Client Initialisation Using WiFi Connection *****/
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

/************* Connect to WiFi ***********/
void setup_wifi() {
  delay(10);
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("\nWiFi connected\nIP address: ");
  Serial.println(WiFi.localIP());
}

/************* Connect to MQTT Broker ***********/
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";   // Create a random client ID
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");

      client.subscribe("led_state");   // subscribe the topics here

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");   // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

  /***** Call back Method for Receiving MQTT messages and Switching LED ****/

void callback(char* topic, byte* payload, unsigned int length) {
  String incommingMessage = "";
  for (int i = 0; i < length; i++) incommingMessage+=(char)payload[i];

  Serial.println("Message arrived ["+String(topic)+"]"+incommingMessage);

  //--- check the incomming message
  /*  if( strcmp(topic,"led_state") == 0){
     if (incommingMessage.equals("1")) digitalWrite(led, HIGH);   // Turn the LED on
     else digitalWrite(led, LOW);  // Turn the LED off
    }*/

}

/**** Method for Publishing MQTT Messages **********/
void publishMessage(const char* topic, String payload , boolean retained){
  if (client.publish(topic, payload.c_str(), true))
      Serial.println("Message publised ["+String(topic)+"]: "+payload);
}

/**** Application Initialisation Function******/
void setup() {


  Serial.begin(9600);
  while (!Serial) delay(1);
  setup_wifi();

    //espClient.setInsecure();

  //client.setServer(mqtt_server, mqtt_port);
   client.setServer(mqtt_server, MQTT_PORT);
  client.setCallback(callback);
}

bool status=0;

/******** Main Function *************/
void loop() {

  if (!client.connected()) reconnect(); // check if client is connected
  client.loop();

//read DHT11 temperature and humidity reading
  status = 1 - status;



  char temp[100];
  char mqtt_message[100];
  char temp_i=0;

  if ( Serial.available() > 0 ){ 

    memset( temp ,0,100);

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

    Serial.print("DATA = ");
    Serial.println(temp);

    DynamicJsonDocument doc(1024);

    /*if( status == 1 )doc["btn"] = "set";
    else doc["btn"] = "clear";*/
    doc["btn"] = temp;

    char mqtt_message[128];
    serializeJson(doc, mqtt_message);

    publishMessage("esp8266_data", mqtt_message, true);

  }

}
