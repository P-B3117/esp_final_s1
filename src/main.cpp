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
char message = '!';
int rec = 0;

void setup() { //ne pas toucher au setup, ce que vous voulez mettre dans le setup mettez le dans votre fonction init
  Serial.begin(9600);
  //manetteInit();
  affichageInit();
  //bluetoothInit();
}

void loop() {}

/*
void loop() {
  updateChrono();
  message = bluetoothLoop();

  switch (mode)
  {
  case PARAMETRES:
    if (bVert()) difficulte1 = ((difficulte1 + 1) % 3);

    if (bNoir()) joueur = 0;
    else joueur = 1;

    writeJoueur(joueur + 1);
    writeDiff(joueur, difficulte1);

    if (bRouge())
    {
      switch (difficulte1)
      {
      case 0:
        if (joueur == 1) bluetoothSend('0');
        else bluetoothSend('3');
        break;
      
      case 1:
        if (joueur == 1) bluetoothSend('1');
        else bluetoothSend('4');
        break;

        
      case 2:
        if (joueur == 1) bluetoothSend('2');
        else bluetoothSend('5');
        break;
      }
    }//bt envoie les données
  break;
  
  case SYNCHRONISATION:
    if (message == 'n') 
    { 
      switch (difficulte1)
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
       mode = EN_JEU; 
      }
    break;
    }
      
  case EN_JEU:
    if (message == 'r') 
    {
      pointage[0] += difficulte1+1;
      writePoints(0, pointage[0]);
    }
    if (message == 'n' && joueur == 1) mode = PARAMETRES;
    else { mode = EN_JEU2; }
  break;
    
  case SYNCHRONISATION2:
    if (message == 'n') { startChrono(); mode = EN_JEU2; }
  break;

  case EN_JEU2:
  if (message == 'r') 
    {
      pointage[0] += difficulte1+1;
      writePoints(1, pointage[1]);
    }
  if (message == 'n') mode = PARAMETRES;
  break;
  }
}
*/