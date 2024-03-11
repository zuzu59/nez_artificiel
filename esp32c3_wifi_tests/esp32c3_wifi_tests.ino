// Création d'un petit nez artificiel lowcost pour sentir plus de trucs intéressants ;-)
// Graphe tout simplement sur le serial plotter tool de l'Arduino IDE
// zf240226.1918
//
// Sources:
// https://github.com/Seeed-Studio/Seeed_Arduino_MultiGas/blob/master/examples/demo_background/demo_background.ino
// https://github.com/Testato/SoftwareWire/blob/master/examples/Small_example/Small_example.ino


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

static uint8_t recv_cmd[8] = {};

void setup() {
    USBSerial.begin(19200);
    delay(3000);  //le temps de passer sur la Serial Monitor ;-)
    USBSerial.println("\n\n\n\nCa commence !\n");
    delay(2000);  //le temps de passer sur la Serial Monitor ;-)

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
    delay(1000);
}



