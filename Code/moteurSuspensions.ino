int ENB=10;
int IN3=5;
int IN4=4;
int sec=10;//Temps pendant lequel le moteur tournera
unsigned long timer;
int statut=0; //0 correspond à la position basse de la voiture, 1 la position haute

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
  // si 995 ms se sont écoulées - ajouter une seconde à la variable sec
  if (millis() - timer > 995) {
      timer = millis();
      sec = sec - 1;}
  Serial.print(sec);
  if(sec > 0){
    if(statut==0){//Si la voiture est en position basse, on visse
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      analogWrite(ENB,200);
    }
    else{//Si elle est en position haute, on dévise
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      digitalWrite(ENB,200);
    }
  }
  else{
    statut=1;
    analogWrite(ENB,0);
  }
}

  

  
  
