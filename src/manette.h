/********
Fichier: manette.h
Auteurs: 
Alexis Lechasseur
Charles Poulin-Bergevin
Raphael Richard
Vincent Taylor
Xavier Robidoux
Anis Bouabid
Jordan Klaus Kodjio Kousso 
Date: 30 Novembre 2023
Description: fonction de la manette
********/
#pragma once
//ne pas mettre vos librairies ici mettez les dans le .cpp sinon on vas avoir des conflits de librairies

void manetteInit();
// Tout ce qui va dans la fonction setup() de Arduino, va directement dans la fonction manetteInit()

char boucle ();

bool bVert();

bool bNoir();

bool bRouge();
