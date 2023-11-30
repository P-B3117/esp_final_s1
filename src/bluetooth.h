/********
Fichier: bluetooth.h
Auteurs: 
Alexis Lechasseur
Charles Poulin-Bergevin
Raphael Richard
Vincent Taylor
Xavier Robidoux
Anis Bouabid
Jordan Klaus Kodjio Kousso 
Date: 30 Novembre 2023
Description: fonction bluetooth du esp de la manette
********/
#pragma once
//ne pas mettre vos librairies ici mettez les dans le .cpp sinon on vas avoir des conflits de librairies

void bluetoothInit();
char bluetoothLoop();
void bluetoothSend(char message);