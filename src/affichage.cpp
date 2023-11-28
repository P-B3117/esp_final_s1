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
  displayWrite(43, 10, String(num + 1), myGREEN);
}

void writeDiff(int dif)
{
  switch (dif)
  {
  case 0:
    displayWrite(7, 10, 'F', myGREEN);
    break;
  
  case 1:
    displayWrite(7, 10, 'M', myGREEN);
    break;
    
  case 2:
    displayWrite(7, 10, 'D', myGREEN);
    break;
  }
}

void writePoints(int j, int num)
{
  if (j == 0)
  {
    if (num >= 10) { displayWrite(4, 30, String(num),myGREEN); }
    else { displayWrite(4, 30, '0' + String(num),myGREEN); }
  }

  else {
    if (num >= 10) { displayWrite(22, 30, String(num),myGREEN); }
    else { displayWrite(22, 30, '0' + String(num),myGREEN); }
  }
}

void resetPoints()
{
  displayWrite(4, 30, "00-00",myGREEN);
}

void writeBest(int num)
{
  //if (num == 0) num = '0';
  displayWrite(49, 30, String(num), myGREEN);
}

void resetBest()
{
  displayWrite(49, 30, '0', myGREEN);
}

void resetEtape()
{
  displayWrite(43, 50, "PAR", myGREEN);
}

void writeEtape(String etape)
{
  displayWrite(43, 50, etape, myGREEN);
}

struct {
  unsigned long endTime;
  bool isON = false;
} chrono;

void resetChrono()
{
  chrono.isON = false;
  displayWrite(13, 50, "00", myGREEN);
}

void updateChrono()
{
  long currentTime = millis();
  if (!chrono.isON) return;
  if (chrono.endTime < currentTime) { chrono.isON = false; resetChrono(); return; }
  if ( (chrono.endTime - currentTime) / 1000 < 10) { displayWrite(13, 50, '0', myGREEN); displayWrite(19, 50, String((chrono.endTime - currentTime/1000), myGREEN)); }
  else displayWrite(13, 50, String((chrono.endTime - currentTime)/1000), myGREEN);
  return;
}

void startChrono(long sec)
{
  chrono.isON = true;
  chrono.endTime = millis() + sec*1000;
  //displayWrite(16, 50, char(chrono.endTime - millis()), myGREEN);
  displayWrite(13, 50, char(chrono.endTime - millis()), myGREEN);
}

void writeTitles()
{
  displayWrite(1,0,"NIV", myRED);
  displayWrite(28,0,"Joueur", myRED);
  displayWrite(7,10,"X", myGREEN);
  displayWrite(1,20,"Points", myRED);
  displayWrite(43,20,"REC", myRED);
  displayWrite(1,40,"Chrono", myRED);
  displayWrite(43, 40, "ETA", myRED);
}

void writeBaseScreen()
{
  dma_display->clearScreen();
  writeTitles();
  //writeJoueur(1);
  resetPoints();
  resetBest();
  resetChrono();
}

void affichageInit()
{
  
 /************** DISPLAY **************/
  //Serial.println("**************** Starting Display ****************");
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->setLatBlanking(0);
  dma_display->invertDisplay(true);
  dma_display->begin();
  dma_display->setBrightness8(255); //0-255
  
  //FastLED.delay(2);

  dma_display->fillScreenRGB888(128,0,0);
  delay(1000);
  dma_display->fillScreenRGB888(0,128,0);
  delay(1000);
  dma_display->clearScreen();  
  delay(1000);

  writeBaseScreen();

  //Serial.println("**************** Display Ready ****************");
}