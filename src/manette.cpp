/********
Fichier: manette.cpp 
Auteurs: 
Alexis Lechasseur
Charles Poulin-Bergevin
Raphael Richard
Vincent Taylor
Xavier Robidoux
Anis Bouabid
Jordan Klaus Kodjio Kousso 
Date: 30 Novembre 2023
Description: code de la manette
********/
#include "manette.h"
#include <Arduino.h>
#define VERT 36
#define NOIR 34
#define ROUGE 35

#define LED_STATE_BLUE 2

void manetteInit() //Équivalent de la fonction setup()
{
    //Lecture de la valeur des trois boutons
    pinMode(VERT, INPUT_PULLDOWN);
    pinMode(NOIR, INPUT_PULLDOWN);
    pinMode(ROUGE, INPUT_PULLDOWN);
    pinMode(LED_STATE_BLUE, OUTPUT);
    
}
 
char boucle()
    {
    int etatVert;
    int etatNoir;
    int etatRouge;
    int niveau = 0;
    etatVert = digitalRead(VERT);
    etatNoir = digitalRead(NOIR);
    etatRouge = digitalRead(ROUGE);
        //Stockage de la lecture des trois boutons

    //Configuration du niveau du bouton vert
    if (etatVert == LOW)
    {
        niveau = niveau + 0;
    }
    if (etatVert == HIGH)
    {
        niveau = niveau + 1;
    }
    if (niveau > 3)
    {
        niveau = 1;
    }
        
        if (etatRouge == LOW) //Robot en Marche
            {
            if (etatNoir == HIGH) //Mode Multijoueur
                {
                    if (niveau == 1) //Mode Multijoueur, Niv 1
                        {
                            //Serial.println("Multijoueur. Niveau 1");
                            return'3';
                        }
                    if (niveau == 2) //Mode Multijoueur, Niv 2
                        {
                            //Serial.println("Multijoueur. Niveau 2");
                            return'4'; 
                        }
                    if (niveau == 3) //Mode Multijoueur, Niv 3
                        {
                            //Serial.println("Multijoueur. Niveau 3");
                            return'5';  
                        }
                }
            
            if (etatNoir == LOW) //Mode Solo
                {
                      if (niveau == 1) //Mode Solo, Niv 1
                        {
                            //Serial.println("Mode Solo. Niveau 1");
                            return'0'; 
                        }
                    if (niveau == 2) //Mode Solo, Niv 2
                        {
                            //Serial.println("Mode Solo. Niveau 2");
                            return'1';  
                        }
                    if (niveau == 3) //Mode Solo, Niv 3
                        {
                            //Serial.println("Mode Solo. Niveau 3");
                            return'2'; 
                        }  
                }
            }
            return'A';
}












bool bVert()
{
    return digitalRead(VERT);
}

bool bNoir()
{
    return digitalRead(NOIR);
}

bool bRouge()
{
    if (digitalRead(ROUGE)  == HIGH) digitalWrite(LED_STATE_BLUE, HIGH);
    else digitalWrite(LED_STATE_BLUE, LOW);
    return digitalRead(ROUGE);
}
//Serial.begin(9600); //Débit de lectures de données
//pinMode(pin, INPUT); Configure le mode d'une pin en tant que entrée (INPUT) ou sortie (OUTPUT)
//digitalWrite(pin, HIGH);       // Configure l'état d'une pin en spécifiant son numéro et son état (HIGH ou LOW)
//digitalRead(pin) ; Lit l'état d'une pin (HIGH ou LOW) en retournant une valeur (HIGH ou LOW)
//Serial.println("Le bouton est appuyé."); Sert à afficher sur la console des données ou des phrases
// État : HIGH ou LOW
// Mode : INPUT ou OUTPUT
// pin1 =
// pin2 = 
// pin3 = 