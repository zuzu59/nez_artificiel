// Juste un test pour voir comment se connecter en WIFI avec un esp32-c3
// et au passage Graphe tout simplement sur le serial plotter tool de l'Arduino IDE
// zf240311.1546
//
// Sources:
// https://github.com/Seeed-Studio/Seeed_Arduino_MultiGas/blob/master/examples/demo_background/demo_background.ino
// https://github.com/Testato/SoftwareWire/blob/master/examples/Small_example/Small_example.ino


// WIFI
#include <WiFi.h>
#include "secrets.h"

// Senseur de gaz
#include <Wire.h>
#include <Multichannel_Gas_GMXXX.h>
GAS_GMXXX<TwoWire> gas;


static void ConnectWiFi() {
    USBSerial.printf("WIFI_SSID: %s\nWIFI_PASSWORD: %s\n", WIFI_SSID, WIFI_PASSWORD);
    // WiFi.mode(WIFI_STA); //Optional
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    //********* cette partie est pour le Lolin esp32-c3 mini V1 !
    //https://github.com/espressif/arduino-esp32/issues/6430.  voir à la fin la raison
    WiFi.setTxPower(WIFI_POWER_8_5dBm);
    int txPower = WiFi.getTxPower();
    USBSerial.print("TX power: ");
    USBSerial.println(txPower);
    //*********
    // WiFi.setSleep(false);
    USBSerial.println("\nConnecting");
    while(WiFi.status() != WL_CONNECTED){
        USBSerial.print(".");
        delay(100);
    }
    USBSerial.println("\nConnected to the WiFi network");
    USBSerial.print("Local ESP32 IP: ");
    USBSerial.println(WiFi.localIP());
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
    USBSerial.setDebugOutput(true);       //pour voir les messages de debug sur la console série !

    delay(3000);  //le temps de passer sur la Serial Monitor ;-)
    USBSerial.println("\n\n\n\nCa commence !\n");
    delay(2000);  //le temps de passer sur la Serial Monitor ;-)

    USBSerial.println("\n\nConnect WIFI !\n");
    ConnectWiFi();

    USBSerial.println("\n\nSetting gaz sensor !\n");
    Setting_Gaz_Sensor();
}

void loop() {
    int NO2 = gas.measure_NO2();
    int C2H5OH = gas.measure_C2H5OH(); 
    int VOC = gas.measure_VOC(); 
    int CO = gas.measure_CO(); 

    // Plot sur le serial plotter de l'Arduino IDE
    // USBSerial.printf("NO2:%d,C2H5OH:%d,VOC:%d,CO:%d\n", NO2, C2H5OH, VOC, CO);
    delay(1000);
}



