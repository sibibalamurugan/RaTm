#include <ESP8266WiFi.h>
#include <MemoryFree.h>
#include <EEPROM.h>
#define PIN_LED 13
String inString;
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define WLAN_SSID "Kurangu Kuppa"
#define WLAN_PASS "vandumurugan"
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883 // use 8883 for SSL
#define AIO_USERNAME "sibiranza"
#define AIO_KEY "aio_bJJW25x4mGdQvxlh44oFD3eXUH6v"
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT,
AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt,
AIO_USERNAME "/feeds/purchase");
void MQTT_connect();
void setup() {
 Serial.begin(115200);
 delay(10);
 Serial.println(F("Adafruit MQTT demo"));
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
 Serial.println("IP address: "); Serial.println(WiFi.localIP());
}
uint32_t x=0;
void loop() {
 MQTT_connect();
char at[30]={"lamoo"};
int n;
int a=0;
while(a==0){
 while (Serial.available()) {
 char inChar = Serial.read();
 Serial.write(inChar);
 inString += inChar;
 if (inChar == ']') {
 n = inString.length();
 char char_array[n + 1];
 strcpy(char_array, inString.c_str());
 strcpy(at,char_array);
 a=1;
 inString = "";
 }
 }
}
 Serial.print(F("\nSending photocell val "));
 Serial.print(x);
 Serial.print("...");
 if (! photocell.publish(at)) {
 Serial.println(F("Failed"));
 } else {
 Serial.println(F("OK!"));
 }
delay(3000);
}
void MQTT_connect() {
 int8_t ret;
 if (mqtt.connected()) {
 return;
 }
 Serial.print("Connecting to MQTT... ");
 uint8_t retries = 3;
 while ((ret = mqtt.connect()) != 0) {
 Serial.println(mqtt.connectErrorString(ret));
 Serial.println("Retrying MQTT connection in 5 seconds...");
 mqtt.disconnect();
 delay(5000); // wait 5 seconds
 retries--;
 if (retries == 0) {
 while (1);
 }
 }
 Serial.println("MQTT Connected!");
}
