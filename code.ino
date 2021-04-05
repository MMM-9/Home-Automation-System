//Include Libraries
#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

//Define Pin No. for Relay

//SSID & Password
#define WLAN_SSID       ""
#define WLAN_PASS       ""

//Server Authentication
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  
#define AIO_USERNAME    ""
#define AIO_KEY         ""

//Create Client Objects
WiFiClient client;

//MQTT Object
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

//Get a subscribe for Light
Adafruit_MQTT_Subscribe Light = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/<pin>");

//Check Connection
void MQTT_connect()
{

}

void setup() {
  Serial.begin(115200);

  
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  //Subscribe to Light
  mqtt.subscribe(&Light);
}

void loop() 
{
  //Check Connection
  
  Adafruit_MQTT_Subscribe *subscription;

  //Read all the subscriptions in loop
  
}
