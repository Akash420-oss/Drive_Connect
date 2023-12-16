#include "ESP8266WiFi.h"
#include "WiFiUdp.h"
WiFiUDP udp;
int forward_button=D0,backward_button=D1;
int left_button=D2,right_button=D3;
int stop_button=D4;
#define GREEN_LED D5
#define RED_LED D6
#define LEFT_LED D7
#define RIGHT_LED D8
void setup(){
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  WiFi.begin("WiFi Car...😎","WifiCar420@");
while(WiFi.status()!=WL_CONNECTED){
  delay(1000);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN,LOW);
}
udp.begin(4210);
pinMode(forward_button,INPUT);
pinMode(backward_button,INPUT);
pinMode(left_button,INPUT);
pinMode(right_button,INPUT);
pinMode(stop_button,INPUT);
pinMode(GREEN_LED,OUTPUT);
pinMode(RED_LED,OUTPUT);
pinMode(LEFT_LED,OUTPUT);
pinMode(RIGHT_LED,OUTPUT);
}
void forward_car(){
    digitalWrite(LED_BUILTIN,LOW);
    digitalWrite(RED_LED,LOW);
      digitalWrite(LEFT_LED,LOW);
  digitalWrite(RIGHT_LED,LOW);
  udp.beginPacket("192.168.4.1",8888);
  udp.write("forward");
  udp.endPacket();
  digitalWrite(GREEN_LED,HIGH);
}
void backward_car(){
    digitalWrite(LED_BUILTIN,LOW);
    digitalWrite(GREEN_LED,LOW);
      digitalWrite(LEFT_LED,LOW);
  digitalWrite(RIGHT_LED,LOW);
  udp.beginPacket("192.168.4.1",8888);
  udp.write("backward");
  udp.endPacket();
  digitalWrite(RED_LED,HIGH);
}
void move_left(){
    digitalWrite(LED_BUILTIN,LOW);
    digitalWrite(RED_LED,LOW);
      digitalWrite(GREEN_LED,LOW);
  digitalWrite(RIGHT_LED,LOW);
  udp.beginPacket("192.168.4.1",8888);
  udp.write("left");
  udp.endPacket();
  digitalWrite(LEFT_LED,HIGH);
}
void move_right(){
    digitalWrite(LED_BUILTIN,LOW);
    digitalWrite(RED_LED,LOW);
      digitalWrite(LEFT_LED,LOW);
  digitalWrite(GREEN_LED,LOW);
  udp.beginPacket("192.168.4.1",8888);
  udp.write("right");
  udp.endPacket();
  digitalWrite(RIGHT_LED,HIGH);
}
void stop_car(){
    digitalWrite(GREEN_LED,LOW);
    digitalWrite(RED_LED,LOW);
      digitalWrite(LEFT_LED,LOW);
  digitalWrite(RIGHT_LED,LOW);
  udp.beginPacket("192.168.4.1",8888);
  udp.write("stopyyyyyy");
  udp.endPacket();
  digitalWrite(LED_BUILTIN,HIGH);
}
void loop(){
   int forward_state=digitalRead(forward_button);
  int backward_state=digitalRead(backward_button);
  int left_state=digitalRead(left_button);
  int right_state=digitalRead(right_button);
//  int stop_state=digitalRead(stop_button);
  if(forward_state==HIGH){
forward_car();
}
else{
  stop_car();
}
  if(backward_state==HIGH){
backward_car();
}
else{
  stop_car();
}
  else if(left_state==LOW){
move_left();
}
  else if(right_state==LOW){
move_right();
}
  else if(stop_state==LOW){
stop_car();
}
delay(1000);
Serial.println(forward_state);
Serial.println(backward_state);
Serial.println(left_state);
Serial.println(right_state);
Serial.println(stop_state);
}
