#include <SoftwareSerial.h>
#include <Esplora.h>//librairie de la manette

SoftwareSerial BTSerie(3, 11); // HC-12 TX Pin, HC-12 RX Pin //sorties manette: 11 pour Tinkerkit outB, 3 pour TinkeKit outA 
String joystick;

int previousLed=0, ledButton=0, led=0;
int previousX = -1, X;
int previousY = -1, Y;
int previousMode,mode=1;
int bouton1=1,bouton4=1,bouton3=1;

int temp=0;

void setup()
{
  Serial.begin(9600);
  BTSerie.begin(9600);
  Serial.println(F("----- TEST EMISSION JOYSTICK -------"));
  delay(500);
}

int lireModeButton(){//renvoi quel bouton est appuyé, 0 si aucun n'est appuyé
  bouton1=Esplora.readButton(SWITCH_1);//0 si appuyé
  bouton4=Esplora.readButton(SWITCH_4);
  bouton3=Esplora.readButton(SWITCH_3);
  if(bouton1==0){return 1;}
  if(bouton4==0){return 2;}
  if(bouton3==0){return 3;}
  return 0;
  
}

void loop(){
  X = map(Esplora.readJoystickX(), -512, 512, 0, 255);
  Y = map(Esplora.readJoystickY(), -512, 512, 0, 255);
  ledButton = Esplora.readButton(SWITCH_LEFT); //0 si appuyé, 1 sinon
  if(ledButton == 0){
    while(ledButton==0){ledButton = Esplora.readButton(SWITCH_LEFT);}//on attend que le bouton soit relaché
    led=not led;}//si le bouton est relaché, on change la valeur des led (allumé 1 ou éteintes 0)

  temp=lireModeButton();//garde en mémoire le mode choisi pour éviter un changement (relachement du bouton) entre le if et l'assignation de mode
  if(temp>0){mode=temp;}
  
  if (X != previousX || Y!= previousY || led!= previousLed || mode != previousMode) {//on n'envoie rien si rien ne change
    BTSerie.println("X"+String(X)+"Y"+String(Y)+"L"+String(led)+"M"+String(mode)+"F"); 
    Serial.println("X"+String(X)+"Y"+String(Y)+"L"+String(led)+"M"+String(mode)+"F");
    previousX = X;
    previousY = Y;
    previousLed=led;
    previousMode=mode;
    delay(5);//le delay permet de laisser le temps au recepteur de lire les données, 5 semble suffisant PAS SÛR 
  }
}
