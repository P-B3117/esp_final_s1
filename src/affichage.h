/********
Fichier: affichage.h 
Auteurs: 
Alexis Lechasseur
Charles Poulin-Bergevin
Raphael Richard
Vincent Taylor
Xavier Robidoux
Anis Bouabid
Jordan Klaus Kodjio Kousso 
Date: 30 Novembre 2023
Description: .h de l'affichage de la matrice
********/
#pragma once
#ifndef String
#include <string>
#endif

//ne pas mettre vos librairies ici mettez les dans le .cpp sinon on vas avoir des conflits de librairies

const uint16_t myGREEN = 2016;
const uint16_t myBLUE  = 31;
const uint16_t myRED  = 63488;
const uint16_t myWHITE = 65531;
const uint16_t myYELLOW = 65504;
const uint16_t myCYAN  = 2047;
const uint16_t myMAGENTA = 63519;
const uint16_t myTURQUOISE = 22429;
const uint16_t myBLACK = 0;

void writeBaseScreen();
void affichageInit();
void printCursorPosition();
void displayWrite(int x, int y, String value, uint16_t color = myWHITE);
void displayWrite(int x, int y, char value, uint16_t color = myWHITE);
void writeJoueur(int num);
void writeDiff(int dif);
void writePoints(int j, int num);
void resetPoints();
void writeBest(int num);
void resetBest();
void resetChrono();
void updateChrono();
void startChrono(long sec = 30);
void writeEtape(String etape);
void resetEtape();
