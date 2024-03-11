// Juste un test pour voir comment se connecter en WIFI avec un esp32-c3
// et au passage Graphe tout simplement sur le serial plotter tool de l'Arduino IDE
// zf240311.1431
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
    // USBSerial.println(WIFI_SSID);
    // USBSerial.print("WIFI_PASSWORD: ");
    // USBSerial.println(WIFI_PASSWORD);
    WiFi.mode(WIFI_STA); //Optional
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    USBSerial.println("\nConnecting");
    while(WiFi.status() != WL_CONNECTED){
        USBSerial.print(".");
        delay(100);
    }
    USBSerial.println("\nConnected to the WiFi network");
    USBSerial.print("Local ESP32 IP: ");
    USBSerial.println(WiFi.localIP());
}



void setup() {
    USBSerial.begin(19200);
    delay(3000);  //le temps de passer sur la Serial Monitor ;-)
    USBSerial.println("\n\n\n\nCa commence !\n");
    delay(2000);  //le temps de passer sur la Serial Monitor ;-)

    ConnectWiFi();





    // Wire.begin(4, 5);     // J'ai branché mon sensor sur les pins 4 et 5 de mon esp32c3 !
    // // If you have changed the I2C address of gas sensor, you must to be specify the address of I2C.
    // //The default addrss is 0x08;
    // gas.begin(Wire, 0x08); // use the hardware I2C
    // //gas.begin(MyWire, 0x08); // use the software I2C
    // //gas.setAddress(0x64); change thee I2C address
}

void loop() {
    int NO2 = 0;
    int C2H5OH = 0;
    int VOC = 0;
    int CO = 0;

    // NO2 = gas.measure_NO2(); 
    // USBSerial.print("NO2:"); 
    // USBSerial.print(NO2); 
    // USBSerial.print(",");
    // // USBSerial.print(gas.calcVol(val)); 
    // // USBSerial.println("V");

    // C2H5OH = gas.measure_C2H5OH(); 
    // USBSerial.print("C2H5OH:"); 
    // USBSerial.print(C2H5OH); 
    // USBSerial.print(",");
    // // USBSerial.print(gas.calcVol(val)); 
    // // USBSerial.println("V");

    // VOC = gas.measure_VOC(); 
    // USBSerial.print("VOC:"); 
    // USBSerial.print(VOC); 
    // USBSerial.print(",");
    // // USBSerial.print(gas.calcVol(val)); 
    // // USBSerial.println("V");

    // CO = gas.measure_CO(); 
    // USBSerial.print("CO:"); 
    // USBSerial.print(CO); 
    // USBSerial.print(",");
    // // USBSerial.print(gas.calcVol(val)); 
    // // USBSerial.println("V");

    // // USBSerial.println("");
    delay(1000);
}



