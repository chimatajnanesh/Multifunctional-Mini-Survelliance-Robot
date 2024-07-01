 #include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>
DHT dht(D7, DHT11);
WiFiClient client;
long myChannelNumber = 2338402;
const char myWriteAPIKey[] = "HEPO9MCLBNXAEVQP";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("IQOO", "123456789");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  dht.begin();
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float se = analogRead(A0);
  delay(1000);
  ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  delay(20);
  ThingSpeak.writeField(myChannelNumber, 3, se, myWriteAPIKey);
  delay(20);
  Serial.println("Temperature : " +(String) t);
  Serial.println("Humidity : " +(String) h);
  Serial.println("GAS value : " +(String) se); 
}
