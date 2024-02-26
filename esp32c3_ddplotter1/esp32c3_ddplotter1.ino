// Création d'un petit nez artificiel lowcost pour sentir plus de trucs intéressants ;-)
// Graphe les senseurs sur le display du smartphone avec DumbDisplay
// zf240226.1929
//
// Sources:
// https://github.com/Seeed-Studio/Seeed_Arduino_MultiGas/blob/master/examples/demo_background/demo_background.ino
// https://github.com/trevorwslee/Arduino-DumbDisplay/blob/master/samples/esp32c3ddblink/esp32c3ddblink.ino
// https://github.com/trevorwslee/Arduino-DumbDisplay/blob/master/projects/servo/servo.ino
// https://github.com/trevorwslee/Arduino-DumbDisplay
// https://trevorwslee.github.io/ArduinoDumbDisplay/html/class_plotter_d_d_layer.html


// Sensor multichannel gas
#include <Multichannel_Gas_GMXXX.h>
#include <Wire.h>
GAS_GMXXX<TwoWire> gas;


// DumbDisplay library
#include "esp32bledumbdisplay.h"
// - use ESP32 BLE with name "ESP32C3"
// - at the same time, enable Serial connection with 115200 baud 
DumbDisplay dumbdisplay(new DDBLESerialIO("ESP32C3_NEZ", true, 115200));
PlotterDDLayer *pPlotter;
LcdDDLayer *lcd;


void setup_DD() {
  // create a plotter layer that shows the angle, and for more fun, sin and cos of the angle
  pPlotter = dumbdisplay.createPlotterLayer(1000, 1000);
  pPlotter->padding(10);
  pPlotter->opacity(100);
  // pPlotter->opacity(25);
  pPlotter->noBackgroundColor();
  // pPlotter->backgroundColor("red");
  pPlotter->label("Sensor multichannel");

  // create a LCD layers with x rows of y characters
  lcd = dumbdisplay.createLcdLayer(20, 2);
    // set LCD colors and print out something
  lcd->pixelColor("black");
  lcd->bgPixelColor("lightgray");
  lcd->backgroundColor("lightgray");

  // "auto pin" the layers vertically
  dumbdisplay.configAutoPin(DD_AP_VERT);
  } 


void setup() {
    USBSerial.begin(19200);
    delay(3000);  //le temps de passer sur la Serial Monitor ;-)
    USBSerial.println("\n\n\n\nCa commence !\n");
    setup_DD();   //configure DumbDisplay
    Wire.begin(4, 5);     // J'ai branché mon sensor sur les pins 4 et 5 de mon esp32c3 !
    gas.begin(Wire, 0x08);
    USBSerial.println("C'est parti !\n");

}


void loop() {
    uint8_t len = 0;
    uint8_t addr = 0;
    uint8_t i;
    uint32_t val = 0;
    int NO2 = 0;
    int C2H5OH = 0;
    int VOC = 0;
    int CO = 0;
    String zString = "";

    NO2 = gas.measure_NO2(); 
    C2H5OH = gas.measure_C2H5OH(); 
    VOC = gas.measure_VOC(); 
    CO = gas.measure_CO(); 

    pPlotter->set("NO2", NO2, "C2H5OH", C2H5OH, "VOC", VOC, "CO", CO);

    zString = "NO2:" + String(NO2) + "  EtOH:" + String(C2H5OH) + "    "    ;
    lcd->setCursor(0, 0);
    lcd->print(zString);
    zString = "VOC:" + String(VOC) + "  CO:" + String(CO) + "    "          ;
    lcd->setCursor(0, 1);
    lcd->print(zString);

    delay(100);
}

