#include <Arduino.h>
#include "bluetooth.h"
#include "manette.h"
#include "affichage.h"

void setup() { //ne pas toucher au setup, ce que vous voulez mettre dans le setup mettez le dans votre fonction init
  Serial.begin(9600);
  manetteInit();
  affichageInit();
  bluetoothInit();
}

void loop() {

}