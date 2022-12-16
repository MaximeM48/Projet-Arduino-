#include <Servo.h>
Servo servo1;
int tension_num=0;

void setup() {
  servo1.attach(3);
  Serial.begin(9600);
}

void loop() {
  tension_num=analogRead(0);
  tension_num=map(tension_num,0,1023,0,180);//Convertit la valeur analogique(0-1023) en degré(0-180)
  Serial.println(tension_num);
  servo1.write(tension_num);
  delay(15);
}
