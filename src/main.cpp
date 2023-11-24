#include <Arduino.h>
#include "bluetooth.h"
#include "manette.h"
#include "affichage.h"

#define PARAMETRES 0
#define SYNCHRONISATION 1
#define EN_JEU 2
#define SYNCHRONISATION2 3
#define EN_JEU2 4

int mode = PARAMETRES;
int difficulte = 0;
int joueur = 0;
int pointage0 = 0;
int pointage1 = 0;
char message = '!';
int rec = 0;
long nextMillis = 0;

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
  switch (mode)
  {
  case PARAMETRES:
  
    if (nextMillis <= millis())
    {
    nextMillis = millis() + 400;

    if (bVert() == HIGH) difficulte = ((difficulte + 1) % 3);

    if (bNoir() == LOW) joueur = 0;
    else joueur = 1;

    writeJoueur((joueur));
    writeDiff(difficulte);
    

    if (bRouge() == LOW)
    {
      switch (difficulte)
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

      mode = SYNCHRONISATION;
    }

    }//bt envoie les données
    message = '!';
  break;
  
  case SYNCHRONISATION:
    if (message == 'n') 
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
    break;
    }
      
  case EN_JEU:
    if (message == 'r') 
    {
      pointage0 += difficulte + 1;
      writePoints(0, pointage0);
    }
    if (message == 'n' && joueur == 0) { mode = PARAMETRES; }
    else { mode = EN_JEU2; }
    message = '!';
  break;
    
  case SYNCHRONISATION2:
    if (message == 'n') { startChrono(); mode = EN_JEU2; }
    message = '!';
  break;

  case EN_JEU2:
  if (message == 'r') 
    {
      pointage1 += difficulte + 1;
      writePoints(1, pointage1);
    }
  if (message == 'n') mode = PARAMETRES;
    message = '!';
  break;
  }
}