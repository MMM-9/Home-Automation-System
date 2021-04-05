#include<ESP8266HTTPClient.h>
#include<ESP8266WiFi.h>

#define ldr_pin A0
#define ir_pin 3

//Access point credentials
const char* ssid = "Avengers";
const char* pwd = "prahar@156";

int ldr_data;
int ir_data;

WiFiServer server(80);    // open port 80 for server connection

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //initialise the serial communication
  delay(10);

  //connecting to wifi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to wifi ");
  Serial.println(ssid);

  WiFi.begin(ssid, pwd);

  //attempt to connect to wifi
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("."); //progress with dots until the wifi is connected
  }
  Serial.println("");

  //while connected print this
  Serial.println("Wifi connected");

  //starting the server
  server.begin();
  Serial.println("Server started.");

  //get the ip address and print it
  Serial.print("This is your ip address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  //wait for the data to be sent from client
  Serial.println("New client connection");
  while (!client.available())
  {
    delay(1);
  }

  //Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  ldr_data = analogRead(ldr_pin);
  ir_data = digitalRead(ir_pin);

  ldr_data = 586;
  ir_data = 1;

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Refresh: 5");

  HTTPClient http;
  String url = "http://192.168.43.163/IoTw/add_data.php?ldr=" + String(ldr_data) + "&ir=" + String(ir_data); //access the php file to write data
  Serial.println(url);
  http.begin(url);

  //using GET method to write to sql
  int httpCode = http.GET();
  if (httpCode > 0)
  {
    Serial.printf("[HTTP] GET...code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK)
    {
      String payload = http.getString();
      Serial.println(payload);
    }
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();

  Serial.println("Client disconnected!");
  Serial.println("");
  delay(3000);
}
