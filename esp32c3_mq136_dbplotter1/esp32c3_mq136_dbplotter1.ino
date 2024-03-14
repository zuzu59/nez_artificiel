// Simple tests du capteur de gaz sulfite MQ-136 pour voir comment l'interfacer avec mon nez électronique
// Graphe aussi le résultat du senseur sur le display du smartphone avec DumbDisplay
// zf240314.1427
//
// Sources:
// https://github.com/trevorwslee/Arduino-DumbDisplay/blob/master/samples/esp32c3ddblink/esp32c3ddblink.ino
// https://github.com/trevorwslee/Arduino-DumbDisplay/blob/master/projects/servo/servo.ino
// https://github.com/trevorwslee/Arduino-DumbDisplay
// https://trevorwslee.github.io/ArduinoDumbDisplay/html/class_plotter_d_d_layer.html


int sensorPin1 = 0;   // select the input pin for the sensor 1
int sensorValue1 = 0;  // variable to store the value coming from the sensor 1
int sensorPin2 = 1;   // select the input pin for the sensor 2
int sensorValue2 = 0;  // variable to store the value coming from the sensor 2


// // DumbDisplay library
// #include "esp32bledumbdisplay.h"
// // - use ESP32 BLE with name "ESP32C3"
// // - at the same time, enable Serial connection with 115200 baud 
// DumbDisplay dumbdisplay(new DDBLESerialIO("ESP32C3_NEZ", true, 115200));
// PlotterDDLayer *pPlotter;
// LcdDDLayer *lcd;


// void setup_DD() {
//   // create a plotter layer that shows the angle, and for more fun, sin and cos of the angle
//   pPlotter = dumbdisplay.createPlotterLayer(1000, 1000);
//   pPlotter->padding(10);
//   pPlotter->opacity(100);
//   // pPlotter->opacity(25);
//   pPlotter->noBackgroundColor();
//   // pPlotter->backgroundColor("red");
//   pPlotter->label("Sensor multichannel");

//   // create a LCD layers with x rows of y characters
//   lcd = dumbdisplay.createLcdLayer(20, 2);
//     // set LCD colors and print out something
//   lcd->pixelColor("black");
//   lcd->bgPixelColor("lightgray");
//   lcd->backgroundColor("lightgray");

//   // "auto pin" the layers vertically
//   dumbdisplay.configAutoPin(DD_AP_VERT);
//   } 


void setup() {
    USBSerial.begin(19200);
    delay(3000);  //le temps de passer sur la Serial Monitor ;-)
    USBSerial.println("\n\n\n\nCa commence !\n");

    // setup_DD();   //configure DumbDisplay

    USBSerial.println("C'est parti !\n");

}


void loop() {

    sensorValue1 = analogRead(sensorPin1);
    sensorValue2 = analogRead(sensorPin2);

    USBSerial.printf("Sensor1:%d,sensor2:%d\n", sensorValue1, sensorValue2);



    // pPlotter->set("NO2", NO2, "C2H5OH", C2H5OH, "VOC", VOC, "CO", CO);

    // zString = "NO2:" + String(NO2) + "  EtOH:" + String(C2H5OH) + "    "    ;
    // lcd->setCursor(0, 0);
    // lcd->print(zString);
    // zString = "VOC:" + String(VOC) + "  CO:" + String(CO) + "    "          ;
    // lcd->setCursor(0, 1);
    // lcd->print(zString);

    delay(1000);
}

