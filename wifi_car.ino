#include "ESP8266WiFi.h"
#include <ESP8266WebServer.h>
#include "WiFiUdp.h"
int connection=2;
int device_check=0;
WiFiUDP udp; 
ESP8266WebServer server(80);
bool forward = LOW;
bool left=LOW;
bool right=LOW;
bool backward=LOW;
char packetval[256];
int red_led=D8;
int green_led=D7,brown_left_led=D0;
int brown_right_led=D6;
#define UDP_PORT 8888
#define IN_1 D3 
#define IN_2 D5 
#define IN_3 D1 
#define IN_4 D2 
String *listConnectedDevices() {
  String *hex_val=new String[12];
  struct station_info *station_list = wifi_softap_get_station_info();
  while (station_list != NULL) {
    for (int i = 0; i < 6; i++) {
       hex_val[i].concat(String(station_list->bssid[i], HEX));
      if (i < 5){
        hex_val[i].concat(":");
      }
    }
    Serial.println();
    station_list = STAILQ_NEXT(station_list, next);
  }
  wifi_softap_free_station_info();
  return hex_val;
}
String *define_mac(){
  String mac_vall[]={"your another NodeMcu's Mac"};
  String *mac_val2=new String[12];
  for (int k=0;k<6;k++){
    mac_val2[k].concat(mac_vall[k]);
    if (k<5){
      mac_val2[k].concat(":");
    }
  }
  return mac_val2;
}
void handle_OnConnect() {
  forward = LOW;
  left=LOW;
  right=LOW;
  backward=LOW;
  server.send(200, "text/html", updateWebpage(forward,left,right,backward)); 
}

void forward_on() {
   forward = HIGH;
  server.send(200, "text/html", updateWebpage(forward,left,right,backward)); 
}

void forward_off() {
  forward = LOW;
  server.send(200, "text/html", updateWebpage(forward,left,right,backward)); 
}
void left_on() {
   left=HIGH;
  server.send(200, "text/html", updateWebpage(forward,left,right,backward)); 
}
void left_off() {
  left=LOW;
  server.send(200, "text/html", updateWebpage(forward,left,right,backward)); 
}
void right_on() {
   right=HIGH;
  server.send(200, "text/html", updateWebpage(forward,left,right,backward)); 
}
void right_off() {
  right=LOW;
  server.send(200, "text/html", updateWebpage(forward,left,right,backward)); 
}
void backward_on() {
  backward=HIGH;
  server.send(200, "text/html", updateWebpage(forward,left,right,backward)); 
}

void backward_off() {
  backward=LOW;
  server.send(200, "text/html", updateWebpage(forward,left,right,backward)); 
}
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
void server_handle(){
    server.on("/", handle_OnConnect);
  server.on("/forwardon", forward_on);
  server.on("/forwardoff", forward_off);
  server.on("/lefton",left_on);
  server.on("/leftoff",left_off);
   server.on("/righton",right_on);
  server.on("/rightoff",right_off);
    server.on("/backwardon", backward_on);
  server.on("/backwardoff", backward_off);
  server.onNotFound(handle_NotFound);
}
String updateWebpage(uint8_t forward,uint8_t left,uint8_t right,uint8_t backward){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>WiFi Control Car</title>\n";
  ptr +="<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{background-color: black;margin-top: 50px;} h1 {color: MediumSeaGreen;margin: 50px auto 30px;} h3 {color:red;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 6px;}\n";
  ptr +=".button_indication {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 6px;}\n";
  ptr +=".button-up-on {background-color: #3498db;}\n";
  ptr +=".button-up-on:active {background-color: #3498db;}\n";
  ptr +=".button-up-off {background-color: #34495e;margin-top: -50px;}\n";
  ptr +=".button-up-off:active {background-color: #2c3e50;margin-top: -50px;}\n";
  ptr +=".button-left-on {background-color: #3498db;float:right;}\n";
  ptr +=".button-left-on:active {background-color: #3498db;float:right;}\n";
  ptr +=".button-left-off {background-color: #34495e;}\n";
  ptr +=".button-left-off:active {background-color: #2c3e50;}\n";
  ptr +=".button-right-on {background-color: #3498db;float:left;}\n";
  ptr +=".button-right-on:active {background-color: #3498db;float:left;}\n";
  ptr +=".button-right-off {background-color: #34495e;}\n";
  ptr +=".button-right-off:active {background-color: #2c3e50;}\n";
  ptr +=".button-down-on {background-color: #3498db;margin-top:120px}\n";
  ptr +=".button-down-on:active {background-color: #3498db;margin-top:120px}\n";
  ptr +=".button-down-off {background-color: #34495e;margin-top:160px;}\n";
  ptr +=".button-down-off:active {background-color: #2c3e50;margin-top:160px}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 50px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Welcome To My WiFi CAR</h1>\n";
  ptr +="<h3>Using Station(STA) Mode</h3>\n";
   if(forward){
    ptr +="<a class=\"button button-up-off\" href=\"/forwardoff\">F:OFF</a>\n";
   }
   else{
      ptr +="<a class=\"button button-up-on\" href=\"/forwardon\">F:ON</a>\n";
    }
 if(left){
   ptr +="<p><br/></p><a class=\"button_indication button-left-off\" href=\"/leftoff\">L:OFF</a>\n";
   }
   else if(right){
     ptr +="<p><br/></p><a class=\"button_indication button-right-off\" href=\"/rightoff\">R:OFF</a>\n";
   }
   else{
    ptr +="<a class=\"button_indication button-left-on\" href=\"/righton\">R:ON</a>\n";
    ptr +="<a class=\"button_indication button-right-on\" href=\"/lefton\">L:ON</a>\n";
   }
    if(backward){
    ptr +="<a class=\"button button-down-off\" href=\"/backwardoff\">B:OFF</a>\n";
   }
   else {
      ptr +="<a class=\"button button-down-on\" href=\"/backwardon\">B:ON</a>\n";
    }
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
void setup() {
pinMode(red_led,OUTPUT);
pinMode(green_led,OUTPUT);
pinMode(brown_left_led,OUTPUT);
pinMode(brown_right_led,OUTPUT);
pinMode(IN_1,OUTPUT);
pinMode(IN_2,OUTPUT);
pinMode(IN_3,OUTPUT);
pinMode(IN_4,OUTPUT);
pinMode(LED_BUILTIN,OUTPUT);
WiFi.mode(WIFI_AP);
WiFi.softAP("WiFi Car...😎","WifiCar420@",1,false,connection);
Serial.begin(9600);
  delay(1000);
 while(WiFi.softAPgetStationNum() ==0){
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);
 }
String *orig_mac=listConnectedDevices();
String *mac_check=define_mac();
int count=0;
for(int i=0;i<8;i++){
  if(orig_mac[i].equals(mac_check[i])){
    count++;
  }
}
if (count==8){
  device_check=1;
   udp.begin(UDP_PORT);
    for(int i=0;i<3;i++){
  digitalWrite(red_led,LOW);
  delay(1000);
  digitalWrite(red_led,HIGH);
   delay(1000);
}
}
else{
  device_check=2;
  server.begin();
  server_handle();
  for(int i=0;i<3;i++){
  digitalWrite(green_led,HIGH);
  delay(1000);
  digitalWrite(green_led,LOW);
   delay(1000);
}
}
}
void stop_car(){
  digitalWrite(red_led,LOW);
  digitalWrite(brown_left_led,LOW);
digitalWrite(brown_right_led,LOW);
digitalWrite(green_led,LOW);
digitalWrite(IN_1,LOW);
digitalWrite(IN_2,LOW);
digitalWrite(IN_3,LOW);
digitalWrite(IN_4,LOW);
digitalWrite(LED_BUILTIN,LOW);
}
void forward_car(){
  digitalWrite(red_led,LOW);
  digitalWrite(brown_left_led,LOW);
digitalWrite(brown_right_led,LOW);
digitalWrite(LED_BUILTIN,LOW);
digitalWrite(green_led,HIGH);
delay(500);
digitalWrite(IN_1,HIGH);
digitalWrite(IN_2,LOW);
digitalWrite(IN_3,HIGH);
digitalWrite(IN_4,LOW);
}
void backward_car(){
  digitalWrite(green_led,LOW);
  digitalWrite(brown_left_led,LOW);
digitalWrite(brown_right_led,LOW);
digitalWrite(LED_BUILTIN,LOW);
digitalWrite(red_led,HIGH);
delay(500);
digitalWrite(IN_1,LOW);
digitalWrite(IN_2,HIGH);
digitalWrite(IN_3,LOW);
digitalWrite(IN_4,HIGH);
}
void left_car(){
  digitalWrite(red_led,LOW);
  digitalWrite(green_led,LOW);
digitalWrite(brown_right_led,LOW);
digitalWrite(LED_BUILTIN,LOW);
digitalWrite(brown_left_led,HIGH);
delay(500);
digitalWrite(IN_1,HIGH);
digitalWrite(IN_2,LOW);
digitalWrite(IN_4,LOW);
digitalWrite(IN_3,LOW);
}
void right_car(){
  digitalWrite(red_led,LOW);
  digitalWrite(brown_left_led,LOW);
digitalWrite(green_led,LOW);
digitalWrite(LED_BUILTIN,LOW);
digitalWrite(brown_right_led,HIGH);
delay(500);
digitalWrite(IN_3,HIGH);
digitalWrite(IN_2,LOW);
digitalWrite(IN_4,LOW);
digitalWrite(IN_1,LOW);
}
void clearArray(char *array_val,size_t array_size){
  memset(array_val,'\0',array_size);
}
void loop(){
if (device_check==1){
 if(udp.parsePacket()){
   int udp_packet_val=udp.read(packetval,255);
  if(udp_packet_val==7) {
    forward_car();
clearArray(packetval,sizeof(packetval));
  }
  else if(udp_packet_val==8){
    backward_car();
  clearArray(packetval,sizeof(packetval));
  }
  else if(udp_packet_val==4) {
    left_car();
    clearArray(packetval,sizeof(packetval));
  }
  else if(udp_packet_val==5){
    right_car();
    clearArray(packetval,sizeof(packetval));
  }
  else{
    stop_car();
    clearArray(packetval,sizeof(packetval));
  }
  }
 }
else{
server.handleClient();
if(forward==HIGH){
forward_car();
}
else if(left==HIGH){
left_car();
}
else if(right==HIGH){
right_car();
}
else if(backward==HIGH){
  backward_car();
}
else{
  stop_car();
}
}
}
