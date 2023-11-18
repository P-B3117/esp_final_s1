#include "manette.h"
#include <Arduino.h>
#define VERT 33
#define NOIR 34
#define ROUGE 35

void manetteInit() //Équivalent de la fonction setup()
{
    pinMode(VERT, INPUT);
    pinMode(NOIR, INPUT);
    pinMode(ROUGE, INPUT);
}
   
   
int bVert()
{
    return digitalRead(VERT);
}

bool bNoir()
{
    return digitalRead(NOIR);
}

bool bRouge()
{
    return digitalRead(ROUGE);
}
   
  
   
void boucle()
    {
        int etatRouge;
        int etatVert;
        int j=0; //Variable servant à dectecter un changement de niveau du bouton vert
        int i=0; //Compteur du nombre de fois que le bouton vert a été appuyé
        etatVert = digitalRead(VERT);
        etatRouge = digitalRead(ROUGE); 
        if (etatRouge == HIGH)
            {
                Serial.print("Le bouton VERT est au niveau: ");
                Serial.println(etatVert);
                j = etatVert;
                
                if (i > 3) //Note si le bouton vert a été appuyé plus de 3 fois
                    {
                        i=1;  
                    }
                
                    etatVert = digitalRead(VERT);
                    if (j != etatVert)
                        {
                            i++;
                            Serial.println("Le bouton VERT a été appuyé ");
                            Serial.print(i);
                            Serial.println("Fois");

                        }
                    else 
                        {
                            Serial.println("Le bouton VERT a été appuyé ");
                            Serial.print(i);
                            Serial.println("Fois");
                        }
            }
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