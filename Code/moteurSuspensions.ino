int ENB=9;
int IN3=7;
int IN4=8;
int sec=3;//Temps pendant lequel le moteur tournera(en demi-secondes
unsigned long timer;
int statut=0; //1 correspond à la position basse de la voiture, 0 la position haute

void setup() {
  Serial.begin(9600);
  timer=millis();
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  digitalWrite(ENB,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void loop() {
  // si 500 ms se sont écoulées - ajouter 1 à la variable sec
  if (millis() - timer > 500) {
      timer = millis();
      sec = sec - 1;}
  Serial.print(sec);
  if(sec > 0){
    if(statut==0){//Si la voiture est en position basse, on visse
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      analogWrite(ENB,255);
    }
    else{//Si elle est en position haute, on dévise
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      digitalWrite(ENB,255);
    }
  }
  else{
    statut=1;
    analogWrite(ENB,0);
  }
}

  

  
  
