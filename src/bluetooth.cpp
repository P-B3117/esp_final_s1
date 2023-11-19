//Par Raphael Richard
//Connection Bluetooth entre ESP32 et cellulaire

//Librairies --------------------------------------------------------------------------------------------
#include "BluetoothSerial.h"

//Definition --------------------------------------------------------------------------------------------
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


#define LED_STATE_BLUE 2 // Indique si le bluetooth est connecté

//Constante ---------------------------------------------------------------------------------------------

//#define USE_PIN // Uncomment this to use PIN during pairing. The pin is specified on the line below
//const char *pin = "1234"; // Change this to more secure PIN.

//Nom du esp32
//String nomDuEsp32 = "ESP32 a Raph";
String nomDuEsp32 = "ESP32 a alex";

BluetoothSerial SerialBT;

//adresse mac du HC-05
uint8_t mac_address[] = {0xB8, 0xD6, 0x1A, 0x41, 0xFF, 0xC2};


void bluetoothInit() {
  SerialBT.begin("ESP32 Manette",true); //Bluetooth device name
 // SerialBT.connect(mac_address);//a enlever pour connecter cell
  pinMode(LED_STATE_BLUE, OUTPUT);
  
  
  
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", nomDuEsp32.c_str());
  //Serial.printf("The device with name \"%s\" and MAC address %s is started.\nNow you can pair it with Bluetooth!\n", nomDuEsp32.c_str(), SerialBT.getMacString()); // Use this after the MAC method is implemented
  
  //#ifdef USE_PIN
    //SerialBT.setPin(pin);
    //Serial.println("Using PIN");
  //#endif
}

char bluetoothLoop() {

  // gestion de connection bluetooth
      if (SerialBT.hasClient()==true)
        digitalWrite(LED_STATE_BLUE, HIGH);
      else if (SerialBT.hasClient()!=true){
        SerialBT.connect(mac_address);
        Serial.print("non");
      }

  if (SerialBT.available()) {
    return (SerialBT.read()); //pour lire un message recu
  }

  return '!';
}

void bluetoothSend(char message)
{
    if (Serial.available()) {
    Serial.println("wow");
    if (message != NULL) SerialBT.println(message);
    //SerialBT.write(message); // pour envoyer un message
    //SerialBT.println("hello"); // pour envoyer un message automatiquement peux aussi etre une variable
    }
}