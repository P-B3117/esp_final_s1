#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"
#include <FastLED.h>
#include "affichage.h"

//config not changed here, only in ESP32-HUB75-MatrixPanel-I2S-DMA.h

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

MatrixPanel_I2S_DMA *dma_display = nullptr;

// Module configuration
HUB75_I2S_CFG mxconfig(
	PANEL_RES_X,   // module width
	PANEL_RES_Y,   // module height
	PANEL_CHAIN   // Chain length
);

void printCursorPosition()
{
  Serial.print(dma_display->getCursorX());
  Serial.print("    ");
  Serial.println(dma_display->getCursorY());
}

void displayWrite(int x, int y, String value, uint16_t color)
{
  dma_display->fillRect(x, y, value.length() * 6, 8, myBLACK);
  dma_display->setCursor(x, y);
  dma_display->setTextColor(color);
  dma_display->print(value);
}
void displayWrite(int x, int y, char value, uint16_t color)
{
  dma_display->fillRect(x, y, 6, 8, myBLACK);
  dma_display->setCursor(x, y);
  dma_display->setTextColor(color);
  dma_display->print(value);
}

void writeJoueur(int num)
{
  //if (num == 0) num = 48;
  displayWrite(43, 10, char(num), myGREEN);
}

void writeDiff(int joueur, char dif)
{
  dif = (toupper(dif));
  displayWrite(0 + joueur*12, 10, dif, myWHITE);
}

void writePoints(int num)
{
  //if (num == 0) num = 48;
  displayWrite(15, 30, char(num),myGREEN);
}

void resetPoints()
{
  displayWrite(15, 30, '0',myGREEN);
}

void writeBest(int num)
{
  //if (num == 0) num = '0';
  displayWrite(49, 30, (char)num, myGREEN);
}

void resetBest()
{
  displayWrite(49, 30, '0', myGREEN);
}

struct {
  long endTime;
  long currentTime;
  long lastTime;
  bool isON = false;
} chrono;

void resetChrono()
{
  chrono.isON = false;
  displayWrite(12, 50, '0', myGREEN);
}

void updateChrono()
{
  if (!chrono.isON) return;
  if (chrono.endTime < millis()) { chrono.isON = false; return; }
  chrono.currentTime = ((chrono.endTime - millis())/1000);
  if (chrono.currentTime < chrono.lastTime && chrono.currentTime >= 10) displayWrite(12, 50, String(chrono.currentTime), myGREEN);
  else if (chrono.currentTime < chrono.lastTime) displayWrite(12, 50, '0' + String(chrono.currentTime), myGREEN);
  chrono.lastTime = chrono.currentTime;
}

void startChrono(long sec)
{
  chrono.isON = true;
  chrono.endTime = millis() + sec*1000;
  displayWrite(12, 50, char(chrono.endTime - millis()), myGREEN);
}

void writeTitles()
{
  displayWrite(0,0,"NIV", myRED);
  displayWrite(28,0,"Joueur", myBLUE);
  displayWrite(0,10,"X-X", myYELLOW);
  displayWrite(0,20,"Points", myCYAN);
  displayWrite(43,20,"Rec", myMAGENTA);
  displayWrite(0,40,"Chrono", myTURQUOISE);
}

void writeBaseScreen()
{
  dma_display->clearScreen();
  writeTitles();
  writeJoueur(1);
  resetPoints();
  resetBest();
  resetChrono();

}

void affichageInit()
{
  
 /************** DISPLAY **************/
  Serial.println("**************** Starting Display ****************");
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->setLatBlanking(2);
  dma_display->begin();
  dma_display->setBrightness8(255); //0-255
  FastLED.delay(4);

  dma_display->fillScreenRGB888(128,0,0);
  delay(1000);
  dma_display->fillScreenRGB888(0,0,128);
  delay(1000);
  dma_display->clearScreen();  
  delay(1000);

  writeBaseScreen();

  Serial.println("**************** Display Ready ****************");
}