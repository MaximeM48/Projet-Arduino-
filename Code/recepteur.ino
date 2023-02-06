#include <SoftwareSerial.h>

SoftwareSerial BTSerie(3, 2); // HC-12 TX Pin, HC-12 RX Pin

char msg;
int x=-1;
int y=-1;
int led=0;
int mode=1;
int infos[4]= {129,129,0,1};

void setup() {
  Serial.begin(9600);
  BTSerie.begin(9600);
  Serial.println("----- TEST RECEPTION JOYSTICK -------");
  delay(500);
}

void ecouter(){
  while(BTSerie.available()){
    msg=BTSerie.read();
    if(msg=='X'){
      while(not BTSerie.available()){}//on attend d'avoir qq chose à lire
      msg=BTSerie.read();
      while(msg!='Y'){//tant que l'on atteint pas Y, on rempli la variable x
        if(x==-1){//si c'est le premier digit, x vaut ce digit
          x=msg-'0';}
        else{
          x=x*10+(msg-'0');}//sinon on rajoute le digit à la suite
        while(not BTSerie.available()){}//on attend d'avoir qq chose à lire
        msg=BTSerie.read();
      }
      
      while(not BTSerie.available()){}//on attend d'avoir qq chose à lire
      msg=BTSerie.read();
      
      while(msg!='L'){//tant que l'on atteint pas L, on rempli la variable y
        if(y==-1){
          y=msg-'0';}
        else{
          y=y*10+(msg-'0');}
        while(not BTSerie.available()){}//on attend d'avoir qq chose à lire 
        msg=BTSerie.read(); 
      }
      
      while(not BTSerie.available()){}//on attend d'avoir qq chose à lire
      msg=BTSerie.read();//on lit L
      led=msg-'0';
      
      while(not BTSerie.available()){}//on attend d'avoir qq chose à lire 
      msg=BTSerie.read();//on lit M
            
      while(not BTSerie.available()){}//on attend d'avoir qq chose à lire
      msg=BTSerie.read();//on lit la valeur du mode
      mode=msg-'0';
      while(not BTSerie.available()){}//on attend d'avoir qq chose à lire 
      msg=BTSerie.read();//on lit F
      //forme du message: XxxxYxxxLxMxF
      infos[0]=x; infos[1]=y; infos[2]=led; infos[3]=mode;
      x=-1; y=-1;
    }   
  }
}

void loop(){
  ecouter();
  Serial.println("X="+String(infos[0])+"Y="+String(infos[1])+"led="+String(infos[2])+"mode="+String(infos[3]));
    }
