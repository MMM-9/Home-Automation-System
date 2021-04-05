//Include Libraries
#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

//Define Pin No. for Relay
#define Relay D3

//SSID & Password
#define WLAN_SSID       "Mr.dHaRmIn.."
#define WLAN_PASS       "dharmin_13299"

//Server Authentication
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "prahar"
#define AIO_KEY         "b71184e7adf744998aa82d38891f38cc"

//Create Client Objects
WiFiClient client;

//MQTT Object
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

//Get a subscribe for Light
Adafruit_MQTT_Subscribe Light = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Relay");

//Check Connection
void MQTT_connect()
{
  int8_t ret;

  if (mqtt.connected())
  {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;

  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) {
      while (1)
      { 
        delay(5000);
        retries = 3;
      }
    }
  }
  Serial.println("MQTT Connected!");

}

void setup() {
  Serial.begin(115200);

  pinMode(Relay, OUTPUT);

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
  MQTT_connect();
  
  Adafruit_MQTT_Subscribe *subscription;

  //Read all the subscriptions in loop
  while ((subscription = mqtt.readSubscription(10000))) 
  {
    if (subscription == &Light) 
    {
      //Print Recieved Value
      Serial.printf("Got: ");
      Serial.println((char *)Light.lastread);

      //Read Character
      int Light_State = atoi((char *)Light.lastread);

      //Relay ON
      digitalWrite(Relay, Light_State);
    }
  }
}

