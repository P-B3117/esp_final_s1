#include <Arduino.h>
#include "bluetooth.h"
#include "manette.h"
#include "affichage.h"

#define PARAMETRES 0
#define SYNCHRONISATION 1
#define EN_JEU 2
#define SYNCHRONISATION2 3
#define EN_JEU2 4
#define NEXT 110
#define REUSSI 114

int mode = PARAMETRES;
int difficulte = 0;
int joueur = 0;
int pointage0 = 0;
int pointage1 = 0;
char message = '!';
int rec = 0;
long nextMillis = 0;
bool rougePushed = true;

void setup() { //ne pas toucher au setup, ce que vous voulez mettre dans le setup mettez le dans votre fonction init
  affichageInit();
  manetteInit();
  bluetoothInit();
  //startChrono();
}

/*
void loop()
{
  message = bluetoothLoop();
  if (message != '!') writePoints(1,rand()%99);
}
*/


void loop() {
  updateChrono();
  message = bluetoothLoop();
  //writeEtape(String(NEXT));
  switch (mode)
  {
  case PARAMETRES:
    writeEtape("PAR");
    writeBest(rec);
    if (message != '!') writeEtape(String(message));
    if (nextMillis <= millis())
    {
    nextMillis = millis() + 400;

    if (bVert() == HIGH) difficulte = ((difficulte + 1) % 3);

    if (bNoir() == LOW) joueur = 0;
    else joueur = 1;

    writeJoueur((joueur));
    writeDiff(difficulte);
    

    if (bRouge() == LOW && !rougePushed)
    {
      switch (difficulte)
      {
      case 0:
        if (joueur == 1) bluetoothSend('3');
        else bluetoothSend('0');
        break;
      
      case 1:
        if (joueur == 1) bluetoothSend('4');
        else bluetoothSend('1');
        break;

        
      case 2:
        if (joueur == 1) bluetoothSend('5');
        else bluetoothSend('2');
        break;
      }
      mode = SYNCHRONISATION;
      rougePushed = true;
    }
    else if (bRouge() == HIGH && rougePushed) rougePushed = false;

    }//bt envoie les données
    message = '!';
  break;
  
  case SYNCHRONISATION:
    writeEtape("SY ");
    //if (message != '!') writeEtape(String(message));
    if (message == NEXT) 
    { 
      switch (difficulte)
      {
      case 0:
        startChrono(30);
        break;
      
      case 1:
        startChrono(20);
        break;

      case 2:
        startChrono(15);
        break;
      }
    mode = EN_JEU;
    message = '!';
    }
    break;
      
  case EN_JEU:
    writeEtape("EJ ");
    if (message == REUSSI) 
    {
      pointage0 += difficulte + 1;
      if (pointage0 > rec) rec = pointage0;
      writeBest(rec);
      writePoints(0, pointage0);
    }
    if (message == NEXT) 
    { 
      if (joueur == 0) { 
   
       writeBaseScreen();
       mode = PARAMETRES;
       pointage0 = 0;
       pointage1 = 0;
       }
      else { mode = SYNCHRONISATION2; } 
    }
    
    message = '!';
  break;
    
  case SYNCHRONISATION2:
  resetChrono();
  writeEtape("SY2");
    if (message != '!') writeEtape(String(message));
    if (message == NEXT) {
      switch (difficulte)
      {
      case 0:
        startChrono(30);
        break;
      
      case 1:
        startChrono(20);
        break;

      case 2:
        startChrono(40);
        break;
      }
       mode = EN_JEU2; }
    message = '!';
  break;

  case EN_JEU2:
    writeEtape("EJ2");
    if (message != '!') writeEtape(String(message));
  if (message == REUSSI) 
    {
      pointage1 += difficulte + 1;
      writePoints(1, pointage1);
      if (pointage1 > rec) rec = pointage1;
      writeBest(rec);
    }
  if (message == NEXT) 
  {
    writeBaseScreen();
    mode = PARAMETRES;
    pointage0 = 0;
    pointage1 = 0;
  }
    message = '!';
  break;
  }
}