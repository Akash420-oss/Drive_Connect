# Drive->🚘<-Connect
This an IoT based Project featuring Server Client. 

## Table of Contents
* [Basic Driving Information 👮🏽‍♂️](#about-project)
  * [Manufactured By](#built-with)
    * [Hardware Part](#hardware-part)
    * [Software Part](#software-part)
* [How Do I Drive This Car🤔?](#getting-started)
  * [Build The Car And Remote](#installation)
  * [Build The Software Part 😉](#code_upload)
    * [Prerequisites](#prerequisites)
    * [Inject The Code 💉](#code-software)
* [Contact](#contact)
* [Journey Never Ends 😇](#wishes)

## Basic Driving Information 👮🏽‍♂️
As i said this Project based on IoT so it has two types of Server Modes(TCP Server And UDP Server) and basically it can connect two types of Client(TCP Client And UDP Client).
Actually this car has two types of Server so it'll depend on you that which type of wifi connection you want build to this car. It has also a remote that is a Wifi Remote.
So, first power on the car then if you connect it to any wifi device like Mobile, Laptop, etc then the car will give you a Web page that's mean the Car Act as a TCP Server.
But if you do power off the car then turn on again and connect it from Wifi Remote then the Car will act as a UDP Server but in that case if you connect the car with your Mobile or Laptop probably you would be connected with your car but you will not find any Web Page. So, First when you power on the car on that time you have to choose that which type of Connection you want to Set with your car like Mobile or Wifi Remote.

### Manufactured By
This Project made with Software and Hardware also...

#### Hardware Part
* For Wifi Car
  * NodeMcu - ESP8266 Board
  * L293D - Motor Driver
  * Gear Motors with Wheels
  * Small BreadBoard
  * LED lights
  * Jumper Wires
   
* For Wifi Remote
  * NodeMcu - ESP8266 Board
  * Push Buttons
  * LED lights
  * Small BreadBoard
  * Jumper Wires

#### Software Part
* For Wifi Car
  * C++
  * HTML
  * CSS

* For Wifi Remote
  * C++

## How Do I Drive This Car 🤔?
1. You can drive the car by Wifi Remote or by Mobile etc...😎
2. But first we have to build Car after that we will go on a test drive...😉
3. So, let's get Started...vroom vroom vrooooooooom....

### Build The Car And Remote
In this section first we will build the car...🤩 
But i will tell you only the circuit part and the design it would be depend on you so, think... think...🤔
* For Wifi Car
  LEDs       | NodeMcu's Pins      
  ---        |      ---                 
  GREEN_LED  |  D7                       
  RED_LED    |  D8                       
  BROWN_LEFT |  D0                       
  BROWN_RIGHT|  D6                       


  L293D Motor Driver | NodeMcu's Pins
  ---                | ---
  IN_1               | D3
  IN_2               | D5
  IN_3               | D1
  IN_4               | D2

* For Wifi Remote
  LEDs      | NodeMcu's Pins
  ---       | ---
  GREEN_LED | D5
  RED_LED   | D6
  LEFT_LED  | D7
  RIGHT_LED | D8


  Push_Buttons    | NodeMcu's Pins
  ---             | ---
  FORWARD_BUTTON  | D0
  BACKWARD_BUTTON | D1
  LEFT_BUTTON     | D2
  RIGHT_BUTTON    | D3


### Build The Software Part 😉
If all circuits have done...

#### Prerequisites
1. Install Arduino IDE 
   * If you are in Windows then download from this link 👉 https://www.arduino.cc/en/software 
   * If you have Debian based linux then should run this command 👇
     ```sh
     sudo apt-get update -y && apt install arduino -y
     ```
   * If you are in Arch based linux then run this 👇
     ```sh
     sudo pacman -Syu --noconfirm && pacman -S arduino --noconfirm
     ```
2. After openning the IDE, check the "File" at the left most then check for "Preferences" after clicking search for "Additional Boards Manager URLs" on this site paste this link 👉 https://arduino.esp8266.com/stable/package_esp8266com_index.json

3. Then go to the "Tools" next go for Boards manager then search with "esp8266" after selecting the latest version of esp8266 after that install it.

#### Inject The Code 💉
1. Clone the repo
   ```sh
   git clone https://github.com/Akash420-oss/Drive_Connect.git
   ```
2. After that what are you waiting for upload the code now then we will go....🚗
   * If you want to upload it from terminal then should run this 👇
     ```sh
     sudo esptool.py --port "check your port" --chip esp8266 --baud 115200 write_flash 0x00000 your_binary_file.bin
     ```
3. Wooo-hoooo!!!!!! it was amazing...🤩 your driving licence has been passed...😍


## Contact
* Linkedin - https://www.linkedin.com/in/akash-sil-102481216/
* Mail - akashsil420@duck.com

## Journey Never Ends 😇
* I hope you would be a better driver in your future...😇
* Don't drink & drive...otherwise you have to pay some money to Police...😝
* But when it comes to as a racer then must you have to be a crazy person...🤪
* Again don't consume alcohol while driving...because it will kill you but not only you but also those who depend on you like your family...😔
