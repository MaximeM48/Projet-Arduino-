#include <Servo.h>
#include <SoftwareSerial.h>
Servo servo1;
Servo servo2;
//SoftwareSerial Serial(1, 0); // HC-12 TX Pin, HC-12 RX Pin
int tension_num=0;//variable pour le servomoteur direction
unsigned int lecture_echo=0;//varialble pour capteur
float lecture_echo_f=0;//varialble pour capteur
const int trig=6;//trig du capteur
const int echo=4;//echo du capteur
const int ENA=9;//variable pour moteur voiture
const int IN1=7;//variable pour moteur voiture
const int IN2=8;//variable pour moteur voiture
const int ENB=10;//variable pour moteur voiture
const int IN3=12;//variable pour moteur voiture
const int IN4=13;//variable pour moteur voiture
int sec=5;//Temps pendant lequel le moteur tournera(en demi-secondes
int sec2=2;
int valManettePos=0;//variable pour moteur voiture
char msg;//variable pour la manette
int x=-1;//variable pour la manette
int y=-1;//variable pour la manette
int led=0;//variable pour la manette
int mode=1;//variable pour la manette
int infos[4]= {127,129,0,1};//variable pour la manette
const int e=1;
unsigned long timer;
int statut=1; //1 correspond à la position basse de la voiture, 0 la position haute
int statut2=0; //0 correspond à l'aileron plat, 1 correspond à l'aileron incliné
int ledAvant=2;//pin phares avants
int ledArriere=3;//pin phares arrières

void setup() {
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  digitalWrite(ENA,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  timer=millis();
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  digitalWrite(ENB,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(ledAvant,OUTPUT);
  pinMode(ledArriere,OUTPUT);
  digitalWrite(ledAvant,HIGH);
  digitalWrite(ledArriere,HIGH);
  timer=millis();
  servo1.attach(5);
  servo2.attach(11);
  Serial.begin(9600);
  delay(500);
}

void loop() {
  ecouter();
  if(infos[2]==1){
    digitalWrite(ledAvant,HIGH);
  }
  else{
    digitalWrite(ledAvant,LOW);
  }
  
  if(infos[3]==1){
    servoAileron(0);
    if(statut!=1){
      moteurSuspensions();
    }
  }
  else if(infos[3]==2){
    servoAileron(0);
    if(statut!=0){
      moteurSuspensions();
    }
  }
  else{
    servoAileron(1);
    if(statut!=0){
      moteurSuspensions();
    }
  }
  servoDirection(infos[0]);
  if (capteur(6,4)==1){
    if(infos[1]<129+e){
      moteurVoiture(infos[1]);
    }
    else{
      moteurVoiture(129);
    }
  }
  else{
    moteurVoiture(infos[1]);
  }
  analogWrite(ledArriere,infos[1]);//les feux de freinages s'allument progressivement de façon inversement proportionnelle de la vitesse
} //fin du main

//fonctions
int capteur(int a,int b){
  digitalWrite(a,HIGH);
  delayMicroseconds(10);
  digitalWrite(a,LOW);
  lecture_echo=pulseIn(b,HIGH);
  lecture_echo_f=float(lecture_echo);
  if(lecture_echo_f*0.017<=10){
    return 1;
  }
  else{
    return 0;
  } 
}

void moteurVoiture(int valeur){
  if(valeur>129+e){
    valManettePos=map(valeur,129,254,0,255);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    analogWrite(ENB,valManettePos);
  }
  else if(valeur<129-e){
    valManettePos=map(valeur,129,0,0,255);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    analogWrite(ENB,valManettePos);
  }
  else{
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    analogWrite(ENB,0);
  }
}

void moteurSuspensions(){
  int sec=5;//Temps pendant lequel le moteur tournera(en demi-secondes)
  int sec2=2;
  if(statut==1){
    while(sec>0){
      if (millis() - timer > 500) {
          timer = millis();
          sec = sec - 1;}
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      analogWrite(ENA,255);
    }
  }
  else{
    while(sec2>0){
      if (millis() - timer > 500) {
          timer = millis();
          sec2 = sec2 - 1;}
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(ENA,255);
    }
  }
  if(statut==0){
    statut=1;
  }
  else{
    statut=0;
  }
}

int servoDirection(int valeur){
  tension_num=map(valeur,0,254,0,180);
  servo1.write(tension_num);
  if (tension_num>90){
    return 0;
  }
  else{
    return 1;
  }
}

void servoAileron(int valeur){
  if(valeur==0){
    servo2.write(90);
    statut2=0;
  }
  if(valeur==1){
    servo2.write(160);
    statut2=1;
  }
}

void ecouter(){
  while(Serial.available()){
    msg=Serial.read();
    if(msg=='X'){
      while(not Serial.available()){}//on attend d'avoir qq chose à lire
      msg=Serial.read();
      while(msg!='Y'){//tant que l'on atteint pas Y, on rempli la variable x
        if(x==-1){//si c'est le premier digit, x vaut ce digit
          x=msg-'0';}
        else{
          x=x*10+(msg-'0');}//sinon on rajoute le digit à la suite
        while(not Serial.available()){}//on attend d'avoir qq chose à lire
        msg=Serial.read();
      }
      
      while(not Serial.available()){}//on attend d'avoir qq chose à lire
      msg=Serial.read();
      
      while(msg!='L'){//tant que l'on atteint pas L, on rempli la variable y
        if(y==-1){
          y=msg-'0';}
        else{
          y=y*10+(msg-'0');}
        while(not Serial.available()){}//on attend d'avoir qq chose à lire 
        msg=Serial.read(); 
      }
      
      while(not Serial.available()){}//on attend d'avoir qq chose à lire
      msg=Serial.read();//on lit L
      led=msg-'0';
      
      while(not Serial.available()){}//on attend d'avoir qq chose à lire 
      msg=Serial.read();//on lit M
            
      while(not Serial.available()){}//on attend d'avoir qq chose à lire
      msg=Serial.read();//on lit la valeur du mode
      mode=msg-'0';
      while(not Serial.available()){}//on attend d'avoir qq chose à lire 
      msg=Serial.read();//on lit F
      //forme du message: XxxxYxxxLxMxF
      infos[0]=x; infos[1]=y; infos[2]=led; infos[3]=mode;
      x=-1; y=-1;
    }   
  }
}
