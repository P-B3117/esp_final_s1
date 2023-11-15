#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"

/*--------------------- MATRIX GPIO CONFIG  -------------------------*/
#define R1_PIN 25
#define G1_PIN 26
#define B1_PIN 27
#define R2_PIN 14
#define G2_PIN 12
#define B2_PIN 13
#define A_PIN 23
#define B_PIN 19        // Changed from library default
#define C_PIN 5
#define D_PIN 17
#define E_PIN 32
#define LAT_PIN 4
#define OE_PIN 15
#define CLK_PIN 16


/*--------------------- MATRIX PANEL CONFIG -------------------------*/
#define PANEL_RES_X 64      // Number of pixels wide of each INDIVIDUAL panel module. 
#define PANEL_RES_Y 64     // Number of pixels tall of each INDIVIDUAL panel module.
#define PANEL_CHAIN 1      // Total number of panels chained one to another
 
/*
//Another way of creating config structure
//Custom pin mapping for all pins
HUB75_I2S_CFG::i2s_pins _pins={R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN};
HUB75_I2S_CFG mxconfig(
						64,   // width
						64,   // height
						 4,   // chain length
					 _pins,   // pin mapping
  HUB75_I2S_CFG::FM6126A      // driver chip
);

*/
MatrixPanel_I2S_DMA *dma_display = nullptr;

// Module configuration
HUB75_I2S_CFG mxconfig(
	PANEL_RES_X,   // module width
	PANEL_RES_Y,   // module height
	PANEL_CHAIN   // Chain length
);


//mxconfig.gpio.e = -1; // Assign a pin if you have a 64x64 panel
//mxconfig.clkphase = false; // Change this if you have issues with ghosting.
//mxconfig.driver = HUB75_I2S_CFG::FM6126A; // Change this according to your pane.



#include <FastLED.h>

/* -------------------------- Some variables -------------------------- */
unsigned long fps = 0, fps_timer; // fps (this is NOT a matrix refresh rate!)
unsigned int default_fps = 30, pattern_fps = 30;  // default fps limit (this is not a matrix refresh counter!)
unsigned long ms_animation_max_duration = 20000;  // 20 seconds
unsigned long last_frame=0, ms_previous=0;

void setup()
{
 /************** SERIAL **************/
  Serial.begin(9600);
  delay(250);
  
 /************** DISPLAY **************/
  Serial.println("...Starting Display");
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->setLatBlanking(3);
  dma_display->begin();
  dma_display->setBrightness8(255); //0-255

  dma_display->fillScreenRGB888(128,0,0);
  delay(1000);
  dma_display->fillScreenRGB888(0,0,128);
  delay(1000);
  dma_display->clearScreen();  
  delay(1000);  
  Serial.println("**************** Starting Aurora Effects Demo ****************");

  FastLED.delay(2);
  delay(1000);

  for(int x = 0; x < PANEL_RES_X; x++) {
    for(int y = 0; y < PANEL_RES_Y; y++) {
      dma_display->drawPixelRGB888(x,y,(x+y)%256,(x+y)%256,(x+y)%256);
      
      Serial.print(0);
      /*
      Serial.print(x);
      Serial.print("  ");
      Serial.print("  ");
      Serial.println((x+y)%256);
      */
    }
    Serial.print("\n");
  }
  delay(1000);
  Serial.println("insane");
  dma_display->clearScreen();
  Serial.println("wow");
  delay(1000);

  for(int x = 0; x < PANEL_RES_X; x++) {
    for(int y = 0; y < PANEL_RES_Y; y++) {
      dma_display->drawPixel(x,y,(x+y)%256);
      /*
      Serial.print(x);
      Serial.print("  ");
      Serial.print(y);
      Serial.print("  ");
      Serial.println((x+y)%256);
      */
    }
  }
  delay(1000);
  dma_display->clearScreen();
  dma_display->print("Dif");
  dma_display->writeLine(0,0,64,7,128);
}

int16_t v = 126;

void loop()
{
  

}
