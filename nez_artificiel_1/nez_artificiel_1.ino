// Création d'un petit nez artificiel lowcost pour sentir plus de trucs intéressants ;-)
// zf240225.1545
//
// Sources:
// https://github.com/Seeed-Studio/Seeed_Arduino_MultiGas/blob/master/examples/demo_background/demo_background.ino
// https://github.com/Testato/SoftwareWire/blob/master/examples/Small_example/Small_example.ino


/*
    Multichannel_gas_sensor_V2.0.ino
    Description: A terminal for Seeed Grove Multichannel gas sensor V2.0.
    2019 Copyright (c) Seeed Technology Inc.  All right reserved.
    Author: Hongtai Liu(lht856@foxmail.com)
    2019-9-29

    The MIT License (MIT)
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.1  USA
*/

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

    // val = gas.getGM102B(); USBSerial.print("GM102B: "); USBSerial.print(val); USBSerial.print("  =  ");
    // USBSerial.print(gas.calcVol(val)); USBSerial.println("V");
    // val = gas.getGM302B(); USBSerial.print("GM302B: "); USBSerial.print(val); USBSerial.print("  =  ");
    // USBSerial.print(gas.calcVol(val)); USBSerial.println("V");
    // val = gas.getGM502B(); USBSerial.print("GM502B: "); USBSerial.print(val); USBSerial.print("  =  ");
    // USBSerial.print(gas.calcVol(val)); USBSerial.println("V");
    // val = gas.getGM702B(); USBSerial.print("GM702B: "); USBSerial.print(val); USBSerial.print("  =  ");
    // USBSerial.print(gas.calcVol(val)); USBSerial.println("V");

    // USBSerial.println("");


    val = gas.measure_NO2(); 
    USBSerial.print("NO2:"); 
    USBSerial.print(val); 
    USBSerial.print(",");
    // USBSerial.print(gas.calcVol(val)); 
    // USBSerial.println("V");

    val = gas.measure_C2H5OH(); 
    USBSerial.print("C2H5OH:"); 
    USBSerial.print(val); 
    USBSerial.print(",");
    // USBSerial.print(gas.calcVol(val)); 
    // USBSerial.println("V");

    val = gas.measure_VOC(); 
    USBSerial.print("VOC:"); 
    USBSerial.print(val); 
    USBSerial.print(",");
    // USBSerial.print(gas.calcVol(val)); 
    // USBSerial.println("V");

    val = gas.measure_CO(); 
    USBSerial.print("CO:"); 
    USBSerial.print(val); 
    USBSerial.print(",");
    // USBSerial.print(gas.calcVol(val)); 
    // USBSerial.println("V");

    USBSerial.println("");
    delay(2000);
}



