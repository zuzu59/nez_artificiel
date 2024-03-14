// Simple test du capteur de gaz MQ-136 (H2S sulfure d'hydrogène) et le MQ137 (NH3 ammoniac) 
// pour voir comment l'interfacer avec mon nez électronique
// Envoie aussi le résultat des senseurs sur le mqtt pour home assistant
// zf240314.1905
//
// Installation:
// Pour MQTT, il faut installer la lib (home-assistant-integration):
// https://github.com/dawidchyrzynski/arduino-home-assistant
//
// Sources:
// https://github.com/Seeed-Studio/Seeed_Arduino_MultiGas/blob/master/examples/demo_background/demo_background.ino
// https://github.com/dawidchyrzynski/arduino-home-assistant/blob/main/examples/sensor-integer/sensor-integer.ino

// WIFI
#include <WiFi.h>
#include "secrets.h"

// MQTT
#include <ArduinoHA.h>
#define DEVICE_NAME     "gazMQ136_137"
#define SENSOR_NAME1     "H2S"
#define SENSOR_NAME2     "NH3"

#define PUBLISH_INTERVAL  1000 // how often image should be published to HA (milliseconds)

WiFiClient client;
HADevice device(DEVICE_NAME);                // c'est le IDS du device, il doit être unique !
HAMqtt mqtt(client, device);
unsigned long lastUpdateAt = 0;

// You should define your own ID.
HASensorNumber Sensor1(SENSOR_NAME1);           // c'est le nom du sensor sur MQTT !
HASensorNumber Sensor2(SENSOR_NAME2);           // c'est le nom du sensor sur MQTT !


static void ConnectWiFi() {
    USBSerial.printf("WIFI_SSID: %s\nWIFI_PASSWORD: %s\n", WIFI_SSID, WIFI_PASSWORD);
    WiFi.mode(WIFI_STA); //Optional
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    WiFi.setSleep(false);
    USBSerial.println("\nConnecting");
    while(WiFi.status() != WL_CONNECTED){
        USBSerial.print(".");
        delay(100);
    }
    USBSerial.println("\nConnected to the WiFi network");
    USBSerial.print("Local ESP32 IP: ");
    USBSerial.println(WiFi.localIP());
}




static void ConnectMQTT() {
   device.setName(DEVICE_NAME);                // c'est le nom du device sur Home Assistant !
    // device.setSoftwareVersion("1.0.0");
    mqtt.setDataPrefix(DEVICE_NAME);             // c'est le nom du device sur MQTT !

    Sensor1.setIcon("mdi:smoke-detector-variant");
    Sensor1.setName(SENSOR_NAME1);           // c'est le nom du sensor sur Home Assistant !
    Sensor1.setUnitOfMeasurement("ppm");

    Sensor2.setIcon("mdi:smoke-detector-variant");
    Sensor2.setName(SENSOR_NAME2);           // c'est le nom du sensor sur Home Assistant !
    Sensor2.setUnitOfMeasurement("ppm");

    mqtt.begin(BROKER_ADDR, BROKER_USERNAME, BROKER_PASSWORD);
    USBSerial.println("MQTT connected");
}




int sensorPin1 = 1;   // select the input pin for the sensor 1
int sensorValue1 = 0;  // variable to store the value coming from the sensor 1
int sensorPin2 = 3;   // select the input pin for the sensor 2
int sensorValue2 = 0;  // variable to store the value coming from the sensor 2


void setup() {
    USBSerial.begin(19200);
    delay(3000);  //le temps de passer sur la Serial Monitor ;-)
    USBSerial.println("\n\n\n\nCa commence !\n");
    delay(2000);  //le temps de passer sur la Serial Monitor ;-)

    USBSerial.println("\n\nConnect WIFI !\n");
    ConnectWiFi();

    // USBSerial.println("\n\nConnect MQTT !\n");
    // ConnectMQTT();

    USBSerial.println("C'est parti !\n");
}


void loop() {

    sensorValue1 = analogRead(sensorPin1);
    sensorValue2 = analogRead(sensorPin2);


    USBSerial.printf("sensor1:%d,sensor2:%d\n", sensorValue1, sensorValue2);





    delay(2000);
}

