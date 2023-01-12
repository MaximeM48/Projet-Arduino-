int ENA=9;
int IN1=7;
int IN2=6;
int valManette=0;
int valManettePos=0;


void setup() {
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  digitalWrite(ENA,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  Serial.begin(9600);
}

void loop() {
  if(valManette<=0){
    valManettePos=(-1)*valManette;
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    analogWrite(ENA,valManettePos);
  }
  else{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    analogWrite(ENA,valManette);
  }
  Serial.println(digitalRead(ENA));//Récupère l'état de ENA, HIGH ou LOW
}
