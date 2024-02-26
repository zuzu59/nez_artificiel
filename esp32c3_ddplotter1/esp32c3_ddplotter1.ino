// Création d'un petit nez artificiel lowcost pour sentir plus de trucs intéressants ;-)
// Graphe les senseurs sur le display du smartphone avec DumbDisplay
// zf240226.1850
//
// Sources:
// https://github.com/Seeed-Studio/Seeed_Arduino_MultiGas/blob/master/examples/demo_background/demo_background.ino
// https://github.com/trevorwslee/Arduino-DumbDisplay/blob/master/samples/esp32c3ddblink/esp32c3ddblink.ino
// https://github.com/trevorwslee/Arduino-DumbDisplay/blob/master/projects/servo/servo.ino
// https://github.com/trevorwslee/Arduino-DumbDisplay
// https://trevorwslee.github.io/ArduinoDumbDisplay/html/class_plotter_d_d_layer.html


// Sensor multichannel gas
#include <Multichannel_Gas_GMXXX.h>
// if you use the software I2C to drive the sensor, you can uncommnet the define SOFTWAREWIRE which in Multichannel_Gas_GMXXX.h.
#ifdef SOFTWAREWIRE
    #include <SoftwareWire.h>
    SoftwareWire myWire(4, 5);
    GAS_GMXXX<SoftwareWire> gas;
#else
    #include <Wire.h>
    GAS_GMXXX<TwoWire> gas;
#endif


// DumbDisplay library
#include "esp32bledumbdisplay.h"
// - use ESP32 BLE with name "ESP32C3"
// - at the same time, enable Serial connection with 115200 baud 
DumbDisplay dumbdisplay(new DDBLESerialIO("ESP32C3_NEZ", true, 115200));

PlotterDDLayer *pPlotter;
// GraphicalDDLayer *graphical;
LcdDDLayer *lcd;


void setup_DD() {
  // record the setup layer commands so that DumbDisplay app can re-connected
  // dumbdisplay.recordLayerSetupCommands();

  // create a plotter layer that shows the angle, and for more fun, sin and cos of the angle
  pPlotter = dumbdisplay.createPlotterLayer(1000, 500);
  pPlotter->padding(10);
  pPlotter->opacity(100);
  // pPlotter->opacity(25);
  pPlotter->noBackgroundColor();
  // pPlotter->backgroundColor("red");
  pPlotter->label("Sensor multichannel");


  // // create a graphical [LCD] layer
  // graphical = dumbdisplay.createGraphicalLayer(1500, 200);
  // graphical->backgroundColor("lightgray");
  // graphical->setTextColor("blue");
  // // graphical->setTextFont();
  // graphical->setTextSize(50);
  // // graphical->println("REGULAR:");

  // create a LCD layers with x rows of y characters
  lcd = dumbdisplay.createLcdLayer(20, 2);
    // set LCD colors and print out something
  lcd->pixelColor("black");
  lcd->bgPixelColor("lightgray");
  lcd->backgroundColor("lightgray");
  // lcd->print("hello world");  
  // lcd->setCursor(0, 1);
  // lcd->print("how are you?");

  // "auto pin" the layers vertically
  dumbdisplay.configAutoPin(DD_AP_VERT);


  
  } 

// will be called last in the loop block
void loop_DDPostProcess() {
  // give DumbDisplay library a change to do it's work
  DDYield();
}



static uint8_t recv_cmd[8] = {};

void setup() {
    USBSerial.begin(19200);
    delay(3000);  //le temps de passer sur la Serial Monitor ;-)
    USBSerial.println("\n\n\n\nCa commence !\n");
    delay(2000);  //le temps de passer sur la Serial Monitor ;-)
    
    setup_DD();
    // loop_DDPostProcess();

    Wire.begin(4, 5);     // J'ai branché mon sensor sur les pins 4 et 5 de mon esp32c3 !
    // If you have changed the I2C address of gas sensor, you must to be specify the address of I2C.
    //The default addrss is 0x08;
    gas.begin(Wire, 0x08); // use the hardware I2C
    //gas.begin(MyWire, 0x08); // use the software I2C
    //gas.setAddress(0x64); change thee I2C address
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
    USBSerial.print("NO2:"); 
    USBSerial.print(NO2); 
    USBSerial.print(",");
    // USBSerial.print(gas.calcVol(val)); 
    // USBSerial.println("V");

    C2H5OH = gas.measure_C2H5OH(); 
    USBSerial.print("C2H5OH:"); 
    USBSerial.print(C2H5OH); 
    USBSerial.print(",");
    // USBSerial.print(gas.calcVol(val)); 
    // USBSerial.println("V");

    VOC = gas.measure_VOC(); 
    USBSerial.print("VOC:"); 
    USBSerial.print(VOC); 
    USBSerial.print(",");
    // USBSerial.print(gas.calcVol(val)); 
    // USBSerial.println("V");

    CO = gas.measure_CO(); 
    USBSerial.print("CO:"); 
    USBSerial.print(CO); 
    USBSerial.print(",");
    // USBSerial.print(gas.calcVol(val)); 
    // USBSerial.println("V");

    USBSerial.println("");

    pPlotter->set("NO2", NO2, "C2H5OH", C2H5OH, "VOC", VOC, "CO", CO);

    // graphical->clear();
    // graphical->setCursor(0, 0);

    zString = "NO2:" + String(NO2) + "  EtOH:" + String(C2H5OH)      ;
    lcd->setCursor(0, 0);
    lcd->print(zString);

    zString = "VOC:" + String(VOC) + "  CO:" + String(CO)      ;
    lcd->setCursor(0, 1);
    lcd->print(zString);





    // graphical->println(zString);




    // loop_DDPostProcess();

    delay(300);
}



