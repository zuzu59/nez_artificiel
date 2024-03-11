// Juste un test pour voir comment envoyer des choses sur un 
// brocker MQTT compatible Home Assistant avec un esp32-c3
// et au passage graphe le senseur de gaz tout simplement 
// sur le serial plotter tool de l'Arduino IDE
// zf240311.1907
//
// Installation:
// Pour MQTT, il faut installer la lib:
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
#define DEVICE_NAME     "gazMulti"
#define SENSOR_NAME1     "NO2"
#define SENSOR_NAME2     "C2H5OH"
#define SENSOR_NAME3     "VOC"
#define SENSOR_NAME4     "CO"

#define PUBLISH_INTERVAL  1000 // how often image should be published to HA (milliseconds)

WiFiClient client;
HADevice device(DEVICE_NAME);                // c'est le IDS du device, il doit être unique !
HAMqtt mqtt(client, device);
unsigned long lastUpdateAt = 0;

// You should define your own ID.
HASensorNumber Sensor1(SENSOR_NAME1);           // c'est le nom du sensor sur MQTT !
HASensorNumber Sensor2(SENSOR_NAME2);           // c'est le nom du sensor sur MQTT !
HASensorNumber Sensor3(SENSOR_NAME3);           // c'est le nom du sensor sur MQTT !
HASensorNumber Sensor4(SENSOR_NAME4);           // c'est le nom du sensor sur MQTT !


// Senseur de gaz
#include <Wire.h>
#include <Multichannel_Gas_GMXXX.h>
GAS_GMXXX<TwoWire> gas;


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

    Sensor3.setIcon("mdi:smoke-detector-variant");
    Sensor3.setName(SENSOR_NAME3);           // c'est le nom du sensor sur Home Assistant !
    Sensor3.setUnitOfMeasurement("ppm");

    Sensor4.setIcon("mdi:smoke-detector-variant");
    Sensor4.setName(SENSOR_NAME4);           // c'est le nom du sensor sur Home Assistant !
    Sensor4.setUnitOfMeasurement("ppm");

    mqtt.begin(BROKER_ADDR, BROKER_USERNAME, BROKER_PASSWORD);
    USBSerial.println("MQTT connected");
}




static void Setting_Gaz_Sensor() {
    Wire.begin(4, 5);     // J'ai branché mon sensor sur les pins 4 et 5 de mon esp32c3 !
    // If you have changed the I2C address of gas sensor, you must to be specify the address of I2C.
    //The default addrss is 0x08;
    gas.begin(Wire, 0x08); // use the hardware I2C
    //gas.begin(MyWire, 0x08); // use the software I2C
    //gas.setAddress(0x64); change thee I2C address
}

void setup() {
    USBSerial.begin(19200);
    delay(3000);  //le temps de passer sur la Serial Monitor ;-)
    USBSerial.println("\n\n\n\nCa commence !\n");
    delay(2000);  //le temps de passer sur la Serial Monitor ;-)

    USBSerial.println("\n\nConnect WIFI !\n");
    ConnectWiFi();

    USBSerial.println("\n\nConnect MQTT !\n");
    ConnectMQTT();

    USBSerial.println("\n\nSetting gaz sensor !\n");
    Setting_Gaz_Sensor();
}

void loop() {
    unsigned long NO2 = gas.measure_NO2();
    unsigned long C2H5OH = gas.measure_C2H5OH(); 
    unsigned long VOC = gas.measure_VOC(); 
    unsigned long CO = gas.measure_CO(); 

    mqtt.loop();

    // unsigned long uptimeValue = millis() / 1000;
    // zSensor1.setValue(uptimeValue);

    Sensor1.setValue(NO2);
    Sensor2.setValue(C2H5OH);
    Sensor3.setValue(VOC);
    Sensor4.setValue(CO);

    // Plot sur le serial plotter de l'Arduino IDE
    USBSerial.printf("NO2:%d,C2H5OH:%d,VOC:%d,CO:%d\n", NO2, C2H5OH, VOC, CO);
    delay(PUBLISH_INTERVAL);
}

