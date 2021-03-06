#include <Blynk.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "R4bwtpz69X07yvjOOwijRTKvNYl7NcXJ";
char ssid[] = "msiTEST";
char pass[] = "msiTEST1234";

//~~~~ pin definition starts ~~~~~~~~~~
//ldr
int ldr = A0;
int ldrStat;

//sl03 + ir03Stat = 0;
int sl01 = D0;
int ir01 = D5;

//sl04 + ir04
int sl02 = D1;
int ir02 = D6;

// define pwm value for each condition - use digitalWrite(x,LOW) for off
int dim = 102;
int full = 225;

WidgetLED ir1(V5);
WidgetLED ir2(V6);
//~~~~~~~~~~~~~ pin definition ends ~~~~~~~~~~~~

void setup(){
  Serial.begin(115200); // Initialisation of serial communication
  Blynk.begin(auth, ssid, pass);
  Blynk.syncAll();

  //variables and pins initialisation
  pinMode(ldr, INPUT);
  
  pinMode(sl01, OUTPUT);
  pinMode(ir01, INPUT);

  pinMode(sl02, OUTPUT);
  pinMode(ir02, INPUT);
}

void loop(){
  ldrStat = analogRead(ldr);
  Blynk.virtualWrite(V3,ldrStat);

  if (ldrStat <= 700){
    analogWrite (sl01, dim);
    analogWrite (sl02, dim);

    Blynk.virtualWrite(V0, 40);
    Blynk.virtualWrite(V1, 40);

    ir1.off();
    ir2.off();

      if(analogRead(ir01) < 300){
        analogWrite(sl01, full);
        delay(1000);

        Blynk.virtualWrite(V0, 100);
        ir1.on();
      } else {
        analogWrite(sl01,dim);

        Blynk.virtualWrite(V0,40);
        ir1.off();
      }
      
      if(analogRead(ir02) < 300){
        analogWrite(sl02, full);
        delay(1000);

        Blynk.virtualWrite(V1, 100);
        ir2.on();
      } else {
        analogWrite(sl02,dim);

        Blynk.virtualWrite(V1,40);
        ir2.off();
      }
  } else {
    digitalWrite(sl01,LOW);
    digitalWrite(sl02,LOW);

    Blynk.virtualWrite(V0,0);
    Blynk.virtualWrite(V1,0);
    ir1.off();
    ir2.off();
  }
  Blynk.run();
}
