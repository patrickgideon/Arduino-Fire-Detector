#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "Token"; //token dari email
char ssid[] = "ssid"; //nama wifi
char pass[] = "passssssssss"; //password
BlynkTimer timer;
#define ONE_WIRE_BUS D8
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
const int ir = D5;
const int mq = D6;
const int lm35 = A0;
const int relay1 = D1;
const int relay2 = D2;
const int relay3 = D3;
const int relay4 = D4;
float tempC;
float suhu,suhu1;
int api;
int asap = 0;
WidgetLCD lcd(V1);
void sendSensor(){
  suhu = analogRead(lm35);
  suhu1 = (suhu*(3.3/1024)*100)-2; // calibrate your sensor
 tempC = sensors.getTempCByIndex(0);
}
void setup() {
  lcd.clear();
 Serial.begin(9600);
 sensors.begin();
 Blynk.begin(auth,ssid,pass);
pinMode(ir,INPUT);
pinMode(mq,INPUT);
pinMode(lm35,INPUT);
pinMode(relay1,OUTPUT);
pinMode(relay2,OUTPUT);
pinMode(relay3,OUTPUT);
pinMode(relay4,OUTPUT);
timer.setInterval(1000L,sendSensor);
}

void loop() {
  Serial.println(analogRead(lm35));
  Blynk.run();
  timer.run();
  api = digitalRead(ir);
  asap = digitalRead(mq);
  if(api == LOW){
    digitalWrite(relay1,LOW);
    digitalWrite(relay2,LOW);
    digitalWrite(relay3,LOW);
    lcd.print(0,0,"Ada Kebakaran!!!");
    Blynk.virtualWrite(V2,45.75);
  }
  else{
    digitalWrite(relay1,HIGH);
    digitalWrite(relay2,HIGH);
    digitalWrite(relay3,HIGH);
    lcd.print(0,0,"Aman            ");
    Blynk.virtualWrite(V2,32.5);
 }
 if( asap == LOW){
  digitalWrite(relay4,LOW);
  lcd.print(0,1,"Ada Asap!!!   ");
}
else{
  digitalWrite(relay4,HIGH);
  lcd.print(0,1,"Tidak ada Asap");
}
}
