// Affiche simplement le graphe du senseur de gaz multiple (les 4 senseurs)
// c'est un très bon exemple de comment afficher plusieurs valeurs (4x valeurs) sur le graphe
// zf240305.1815
//
// ATTENTION: il ne faut PAS utiliser la lib 1.0.0 qui se trouve sur le site de Seed Studio
// mais la version 1.1.0 qui sur trouve sur Github:
// https://github.com/Seeed-Studio/Seeed_Arduino_Linechart

// IMPORTANT: si le WIO est briqué, il suffit simpllement de faire un bouble reset rapidement juste après le power on !

// Sources: 
// https://wiki.seeedstudio.com/Wio-Terminal-Displaying-Gyro/
// https://github.com/Seeed-Studio/Seeed_Arduino_MultiGas/blob/master/examples/demo_background/demo_background.ino
// https://github.com/Testato/SoftwareWire/blob/master/examples/Small_example/Small_example.ino


#include"LIS3DHTR.h" //include the accelerator library h        ttps://github.com/Seeed-Studio/Seeed_Arduino_LIS3DHTR
#include"seeed_line_chart.h" //include the line chart library   https://github.com/Seeed-Studio/Seeed_Arduino_Linechart
#include <Multichannel_Gas_GMXXX.h>

// if you use the software I2C to drive the sensor, you can uncommnet the define SOFTWAREWIRE which in Multichannel_Gas_GMXXX.h.
// #ifdef SOFTWAREWIRE
//     #include <SoftwareWire.h>
//     SoftwareWire myWire(4, 5); clock bcm2, data bcm3
//     GAS_GMXXX<SoftwareWire> gas;
// #else
    #include <Wire.h>
    GAS_GMXXX<TwoWire> gas;
// #endif

TFT_eSPI tft;
LIS3DHTR<TwoWire>  lis;

#define MAX_SIZE 50 //maximum size of data
doubles accelerator_readings[4];
TFT_eSprite spr = TFT_eSprite(&tft);  // Sprite

void setup() {
    Serial.begin(115200);
    // delay(3000);  //le temps de passer sur la Serial Monitor ;-)
    Serial.println("\n\n\n\nCa commence !\n");
    // delay(2000);  //le temps de passer sur la Serial Monitor ;-)

    Wire.begin(BCM2, BCM3);     // J'ai branché mon sensor sur les pins BCM2 (clock) et BCM3 (data) du port GROVE (celui de gauche) de mon WIO !
    // If you have changed the I2C address of gas sensor, you must to be specify the address of I2C.
    //The default addrss is 0x08;
    gas.begin(Wire, 0x08); // use the hardware I2C
    //gas.begin(MyWire, 0x08); // use the software I2C
    //gas.setAddress(0x64); change thee I2C address    
    
    tft.begin();
    tft.setRotation(3);
    spr.createSprite(TFT_HEIGHT,TFT_WIDTH);
    spr.setRotation(3);

    lis.begin(Wire1);
    lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ);
    lis.setFullScaleRange(LIS3DHTR_RANGE_2G);

}

void loop() {
    int NO2 = 0;
    int C2H5OH = 0;
    int VOC = 0;
    int CO = 0;

    NO2 = gas.measure_NO2(); 
    Serial.print("NO2:"); 
    Serial.print(NO2); 
    Serial.print(",");
    // Serial.print(gas.calcVol(val)); 
    // Serial.println("V");

    C2H5OH = gas.measure_C2H5OH(); 
    Serial.print("C2H5OH:"); 
    Serial.print(C2H5OH); 
    Serial.print(",");
    // Serial.print(gas.calcVol(val)); 
    // Serial.println("V");

    VOC = gas.measure_VOC(); 
    Serial.print("VOC:"); 
    Serial.print(VOC); 
    Serial.print(",");
    // Serial.print(gas.calcVol(val)); 
    // Serial.println("V");

    CO = gas.measure_CO(); 
    Serial.print("CO:"); 
    Serial.print(CO); 
    Serial.print(",");
    // Serial.print(gas.calcVol(val)); 
    // Serial.println("V");

    Serial.println("");

    spr.fillSprite(TFT_WHITE);
    float x_raw = lis.getAccelerationX();
    float y_raw = lis.getAccelerationY();
    float z_raw = lis.getAccelerationZ();

    //This is used to print out on Serial Plotter, check Serial Plotter!
    Serial.print(x_raw);
    Serial.print(",");
    Serial.print(y_raw);
    Serial.print(",");
    Serial.println(z_raw);

    if (accelerator_readings[0].size() == MAX_SIZE) {
      for (uint8_t i = 0; i<3; i++){
        accelerator_readings[i].pop(); //this is used to remove the first read variable
      }
    }
    // accelerator_readings[0].push(x_raw); //read variables and store in data
    // accelerator_readings[1].push(y_raw);
    // accelerator_readings[2].push(z_raw);

    accelerator_readings[0].push(NO2); //read variables and store in data
    accelerator_readings[1].push(C2H5OH);
    accelerator_readings[2].push(VOC);
    accelerator_readings[2].push(CO);

    //Settings for the line graph title
    auto header =  text(0, 0)
                .value("Accelerator Readings")
                .align(center)
                .valign(vcenter)
                .width(spr.width())
                .thickness(2);

    header.height(header.font_height(&spr) * 2);
    header.draw(&spr); // Header height is the twice the height of the font

  //Settings for the line graph
    auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
         content
                .height(spr.height() - header.height() * 1.5) //actual height of the line chart
                .width(spr.width() - content.x() * 2) //actual width of the line chart
                .based_on(-2.0) //Starting point of y-axis, must be a float
                .show_circle(false) //drawing a cirle at each point, default is on.
                // .value({accelerator_readings[0],accelerator_readings[1], accelerator_readings[2]}) //passing through the data to line graph
                .value({accelerator_readings[0],accelerator_readings[1], accelerator_readings[2], accelerator_readings[3]}) //passing through the data to line graph
                .max_size(MAX_SIZE)          
                .color(TFT_BLUE, TFT_RED, TFT_GREEN, TFT_BLACK)
                .backgroud(TFT_WHITE)
                .draw(&spr);

    spr.pushSprite(0, 0);
    delay(500);
}