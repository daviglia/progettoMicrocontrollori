#include "IRremote.h" 
#include <SoftwareSerial.h>
IRsend irsend; //pin 3
int freq_ir = 38; 

int FOTORESITORE= A0; 

int SENSOREMOVIMENTO=2; 

int rxWIFI=8;
int txWIFI=9; 
SoftwareSerial esp8266(rxWIFI, txWIFI);

unsigned int accendi[67] = {9200,4400, 600,500, 600,550, 550,600, 550,550, 600,500, 600,550, 600,500, 650,500, 550,1700, 600,1650, 550,1650, 550,1700, 600,1650, 550,1650, 550,1700, 650,1600, 600,500, 600,550, 550,550, 600,500, 650,500, 550,600, 550,1650, 550,600, 550,1650, 550,1700, 600,1650, 600,1600, 600,1650, 600,1650, 600,500, 650,1600, 600};
unsigned int piu[67] = {9200,4400, 600,500, 650,500, 550,600, 600,500, 600,550, 550,550, 600,550, 600,500, 550,1700, 600,1650, 600,1650, 550,1650, 650,1600, 600,1650, 550,1700, 600,1650, 550,550, 600,550, 550,1650, 600,1650, 600,1650, 550,600, 550,1650, 550,600, 600,1600, 600,1650, 600,550, 550,550, 600,550, 600,1650, 600,500, 600,1650, 600};
unsigned int meno[67] = {9150,4400, 600,550, 600,500, 550,600, 550,550, 600,550, 550,550, 600,500, 650,500, 550,1700, 600,1650, 550,1650, 550,1700, 600,1650, 550,1650, 550,1700, 600,1650, 550,1650, 550,600, 550,1650, 550,1700, 600,1650, 600,500, 600,1650, 600,500, 600,550, 550,1650, 600,550, 550,550, 600,550, 600,1650, 550,550, 600,1650, 550};
unsigned int verde[67] ={9100,4450, 550,550, 600,500, 600,550, 600,500, 600,550, 550,600, 550,550, 600,500, 550,1700, 600,1650, 600,1650, 550,1650, 600,1650, 600,1650, 550,1650, 600,1650, 600,1650, 550,550, 600,550, 600,1650, 550,1650, 550,600, 550,1650, 550,600, 600,500, 600,1650, 600,1650, 550,550, 600,500, 600,1650, 600,550, 600,1600, 600};
unsigned int rosso[67] ={9200,4400, 600,550, 600,500, 550,600, 600,500, 650,500, 550,600, 600,500, 600,550, 550,1700, 600,1650, 550,1650, 550,1700, 600,1650, 600,1650, 550,1650, 600,1650, 600,550, 600,500, 550,600, 600,1600, 600,1650, 600,550, 550,1700, 600,500, 550,1700, 600,1650, 600,1600, 600,550, 600,500, 650,1650, 550,550, 600,1650, 600};
unsigned int blu[67] = {9100,4400, 600,500, 650,500, 550,600, 550,550, 600,500, 550,600, 600,500, 600,550, 550,1650, 650,1650, 550,1650, 550,1700, 600,1650, 550,1650, 550,1700, 600,1650, 550,1650, 550,600, 550,1650, 550,600, 600,500, 600,550, 550,1650, 600,550, 550,550, 600,1650, 550,600, 550,1650, 550,1700, 600,1600, 600,550, 600,1600, 600}; 
unsigned int bianco[67] = {9200,4400, 600,550, 600,500, 600,550, 600,500, 600,550, 550,550, 600,550, 600,500, 550,1700, 600,1650, 600,1600, 600,1650, 600,1650, 600,1650, 550,1650, 600,1650, 600,500, 650,500, 550,1700, 600,500, 550,600, 600,500, 600,1650, 600,550, 600,1650, 550,1650, 550,600, 550,1650, 550,1700, 600,1650, 600,500, 600,1650, 600};  // Protocol=NEC Data=0xFF22DD

boolean eStataSpentaLuce=false;
boolean autoAccensione=false; 

boolean movimento=false; 

int cmd;

void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);
  Serial.print("SETUP");
}

void loop() {
   
   controllaLuce();
   if(controllaMovimento()){
      if(!movimento){
        if(!autoAccensione && !eStataSpentaLuce && luceSpenta()){
        irsend.sendRaw(accendi, 67, freq_ir);
        autoAccensione=true; 
         Serial.println("accendo sto coso");
        delay(1000);
        movimento=true;
       
      }
     }
   }
   else{
    if(movimento)
      movimento=false; 
   }
   leggiServer();
}

void leggiServer(){
   Serial.print(esp8266.available());
  while (esp8266.available() > 0) {
    //inserisco il valore ricevuto nella variabile cmd
     Serial.print("accessibile");
    cmd = esp8266.read();
    Serial.print("letto");
    //controlla il comando ricevuto e accendi e spegni l'uscita corrispondente
    if(cmd == '1'){
       irsend.sendRaw(accendi, 67, freq_ir); 
       Serial.print("accendo");
       delay(1000); 
    } else if(cmd == '2'){
      irsend.sendRaw(accendi, 67, freq_ir); 
      delay(1000); 
    }
    else if(cmd == '3'){
      irsend.sendRaw(piu, 67, freq_ir); 
      delay(1000); 
    }
     else if(cmd == '4'){
      irsend.sendRaw(meno, 67, freq_ir); 
      delay(1000); 
    }
     else if(cmd == '5'){
      irsend.sendRaw(rosso, 67, freq_ir); 
      delay(1000); 
    }
     else if(cmd == '6'){
      irsend.sendRaw(blu, 67, freq_ir); 
      delay(1000); 
    }
     else if(cmd == '7'){
      irsend.sendRaw(verde, 67, freq_ir); 
      delay(1000); 
    }
    else if(cmd == '8'){
      irsend.sendRaw(bianco, 67, freq_ir); 
      delay(1000); 
    }
       
       
    }
}

boolean controllaMovimento(){
  Serial.print("movimento "); 
  Serial.println(digitalRead(SENSOREMOVIMENTO));
  if(digitalRead(SENSOREMOVIMENTO) == HIGH){
    digitalWrite(SENSOREMOVIMENTO,LOW);
    return true;
  }
  else 
    return false; 
}
void controllaLuce(){
  Serial.println(analogRead(FOTORESITORE));
  delay(100);
  if(autoAccensione){
    if(eStataSpentaLuce){ //caso in cui si è accesa da sola, l'ho spenta o ora ho riacceso una luce 
      if(analogRead(FOTORESITORE)>20){
        eStataSpentaLuce=false; 
        autoAccensione=false;
        Serial.println("caso in cui si è accesa da sola, l'ho spenta o ora ho riacceso una luce");   
      }
    }
    else{
      if(analogRead(FOTORESITORE)<20){ 
        eStataSpentaLuce=true; 
        Serial.println("è stata spenta la luce"); 
      }
    }
  }
}
boolean luceSpenta(){
  if(analogRead(FOTORESITORE)<20){
    return true;
  }
  return false; 
}
