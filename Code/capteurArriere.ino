unsigned int lecture_echo=0;
float lecture_echo_f=0;
const int trig=3;
const int echo=2;

void setup() {
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

void loop() {
  Serial.println(capteur(trig,echo));
}

int capteur(int a,int b){
  digitalWrite(a,HIGH);
  delayMicroseconds(10);
  digitalWrite(a,LOW);
  lecture_echo=pulseIn(b,HIGH);
  lecture_echo_f=float(lecture_echo);
  Serial.print(lecture_echo_f*0.017);
  Serial.println(" cm ");
  if(lecture_echo_f*0.017<=10){
    Serial.println("1");
    return 1;
  }
  else{
    Serial.println("0");
    return 0;
  } 
}
