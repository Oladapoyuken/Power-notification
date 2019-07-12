#include <SoftwareSerial.h>
#define led 7
#define buz 2
#define reseter A5

SoftwareSerial GSM(10,11);

int pos = 0;
char buffer[100];
unsigned long lastActionTime = 0;

int counter =0;

void sendGSM(const char* msg, int waitMs = 500){
  GSM.println(msg);
  while(GSM.available()){
    parseATText(GSM.read());
    if(pos >50){
      pos = 0;
    }
  }
  delay(waitMs);
}

void setup() {
  GSM.begin(9600);
  Serial.begin(9600);

  pinMode(led,OUTPUT);
  pinMode(buz,OUTPUT);
  pinMode(reseter,OUTPUT);
  
  digitalWrite(buz, HIGH);
  delay(100);
  digitalWrite(buz, LOW);
  delay(100);

  delay(20000);

  
  

  //sendGSM("AT+SAPBR=3,1,\"APN\",\"internet.ng.zain.com\"");
  sendGSM("AT+SAPBR=3,1,\"APN\",\"gloflat\"");
  sendGSM("AT+SAPBR=1,1",5000);
  sendGSM("AT+HTTPINIT");
  sendGSM("AT+HTTPPARA=\"CID\",1");
  sendGSM("AT+HTTPPARA=\"URL\",\"http://lumia.qamarian.com:50001/update/sAAAA/er5957pass/1\"");
  


}



void parseATText(byte b){
  buffer[pos++] = b;
}

void blinkLed(){
  for(int i = 0; i < 2; i++){
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
  }
  if(counter > 10){
    analogWrite(reseter, 1000);
  }
}

void loop() {

//  unsigned long now = millis();
//  
//  if(now > lastActionTime + 2000){
//      sendGSM("AT+HTTPACTION=0");
//      lastActionTime = now;
//      blinkLed();
//  }
//
//    while(GSM.available()){
//      lastActionTime = now;
//      parseATText(GSM.read());
//    }

      sendGSM("AT+HTTPACTION=0");
      blinkLed();
      counter++;

      while(GSM.available()){
        parseATText(GSM.read());
         if(counter > 10){
          analogWrite(reseter, 1000);
        }
      }

      if(counter > 10){
        analogWrite(reseter, 1000);
      }
}
