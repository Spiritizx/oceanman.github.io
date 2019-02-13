#include <OneWire.h>

#include <DallasTemperature.h>

#include "ThingSpeak.h"

#include "secrets.h"

#include <WiFi.h>

int databus=5;

OneWire oneWire(databus);

DallasTemperature sensors(&oneWire);

 float Celcius=0;
 
char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

void setup() {
  Serial.begin(115200);  //Initialize serial
  sensors.begin();
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
   sensors.requestTemperatures(); 
   Celcius=sensors.getTempCByIndex(0);
   delay(500);
   while(Celcius<=0){
   sensors.requestTemperatures(); 
   Celcius=sensors.getTempCByIndex(0);
   delay(500);
   }
   Serial.print(" C  ");
   Serial.println(Celcius);

  int x = ThingSpeak.writeField(myChannelNumber,2,Celcius, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  delay(15000); // Wait 15 seconds to update the channel again
  
}
