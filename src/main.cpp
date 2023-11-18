#include <Arduino.h>
#include "bluetooth.h"
#include "manette.h"
#include "affichage.h"

#define PARAMETRES 0
#define SYNCHRONISATION 1
#define EN_JEU 2
#define SYNCHRONISATION2 3
#define EN_JEU2 4

int mode = 0;
int difficulte1 = 0;
int difficulte2 = 0;
int joueur = 0;
int pointage[2];

void setup() { //ne pas toucher au setup, ce que vous voulez mettre dans le setup mettez le dans votre fonction init
  Serial.begin(9600);
  manetteInit();
  affichageInit();
  bluetoothInit();
}

void loop() {
  updateChrono();
  bluetoothLoop();

  switch (mode)
  {
  case PARAMETRES:
    if (bVert()) difficulte1 = ((difficulte1 + 1) % 3) +1;

    if (bNoir()) joueur = 0;
    else joueur = 1;

    if (bRouge()) ;//bt envoie les données
  break;
  
  case SYNCHRONISATION:
    if (true) { startChrono(); mode = EN_JEU; }
  break;
      
  case EN_JEU:
    if (true) 
    {
      pointage[0]++;
      writePoints(0, pointage[0]);
    }
    if (true && joueur == 1) mode = PARAMETRES;
    else { mode = EN_JEU2; }
  break;
    
  case SYNCHRONISATION2:
    if (true) { startChrono(); mode = EN_JEU2; }
  break;

  case EN_JEU2:
  if (true) 
    {
      pointage[1]++;
      writePoints(1, pointage[1]);
    }
  if (true) mode = PARAMETRES;
  break;
  }
}