//Librairies --------------------------------------------------------------------------------------------
#include <Arduino.h>
#include "bluetooth.h"
#include "BluetoothSerial.h"
//Definition --------------------------------------------------------------------------------------------
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

//Constante ---------------------------------------------------------------------------------------------

//#define USE_PIN // Uncomment this to use PIN during pairing. The pin is specified on the line below
//const char *pin = "0079"; // Change this to more secure PIN.

//Nom du esp32
String nomDuEsp32 = "ESP32 a Raph";
BluetoothSerial SerialBT;

//adresse mac du HC-05
uint8_t mac_address[] = {0x58, 0x56, 0x00, 0x00, 0x49, 0xA0};


void bluetoothInit()
{
  Serial.begin(9600);
  SerialBT.begin("ESP32 Manette"); //Bluetooth device name
  SerialBT.connect(mac_address);  // on connecte le esp32 au hc-05
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", nomDuEsp32.c_str());
  //Serial.printf("The device with name \"%s\" and MAC address %s is started.\nNow you can pair it with Bluetooth!\n", nomDuEsp32.c_str(), SerialBT.getMacString()); // Use this after the MAC method is implemented
  #ifdef USE_PIN
    SerialBT.setPin(pin);
    Serial.println("Using PIN");
  #endif
}

void bluetoothLoop(){

  if (Serial.available()) {
    SerialBT.write(Serial.read()); // pour envoyer un message
    //SerialBT.println("hello"); // pour envoyer un message automatiquement peux aussi etre une variable

  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read()); //pour lire un message recu

  }
  delay(20);

}