#include <Servo.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 11
int walk = 0;
bool left = 0;
bool right = 0;
bool backward = 0;
bool standupbro = 0;

Servo servos[8];
int pins[8] = {2,3,4,5,6,7,8,9};
int centerS[8] = {90,85,85,90,80,85,90,80};
int current[8] =  {90,85,85,90,80,85,90,80};
int limdrang[2][8] = {{90,85,85,90,80,50,90,80},
                      {0,85,85,90,80,85,90,80}};

int standupS[8] = {10,170,0,170,85,85,85,80};

int forwardStep1[8] = {20,170,0,170 ,50,85,85,80};
int forwardStep2[8] = {10,170,10,170 ,50,120,120,80};
int forwardStep3[8] = {10,170,0,150 ,85,120,120,120};
int forwardStep4[8] = {10,150,0,170 ,85,60,60,120};
int forwardStep5[8] = {10,170,0,170 ,85,120,60,80};

int backwardStep6[8] = {20,170,10,170 ,80,55,85,80};
int backwardStep5[8] = {20,170,10,150 ,80,120,120,130};
int backwardStep4[8] = {10,150,0,150 ,120,120,120,130};
int backwardStep3[8] = {10,150,0,170 ,120,55,50,80};
int backwardStep2[8] = {10,170,0,170 ,80,55,50,80};
int backwardStep1[8] = {10,170,20,170 ,80,85,120,80};

int turnrightStep1[8] = {10,170,0,170 ,85,85,85,80};
int turnrightStep2[8] = {10,160,0,160 ,85,50,85,50};
int turnrightStep3[8] = {20,170,10,170 ,30,50,30,50};
int turnrightStep4[8] = {10,170,0,170 ,30,85,30,80};

int turnleftStep1[8] = {20,170,10,170 ,85,85,85,80};
int turnleftStep2[8] = {10,170,0,170 ,85,50,85,50};
int turnleftStep3[8] = {10,170,0,170 ,30,50,30,50};
int turnleftStep4[8] = {10,160,0,160 ,30,85,30,80};



bool done = true;

String input = "";

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  for(int i = 0; i < 8; i++) {
    servos[i].attach(pins[i]);
    servos[i].write(centerS[i]);
  }
  delay(2500);
}
unsigned long previousMillis = 0;
const long interval = 100; 
int state = 0, stateturnleft = 0, stateturnright = 0,  stateturnbackward = 0;
int statewalkcount = 0;

void loop() {
  if (IrReceiver.decode()) {

  int protocol = IrReceiver.decodedIRData.protocol;
  int address = IrReceiver.decodedIRData.address;
  int Ircommand = IrReceiver.decodedIRData.command;

  if (protocol == 7 && address == 0xEF00) {
    if (Ircommand == 0x02) {
      moveToTarget(centerS);
      Serial.println("off");
    }
    if (Ircommand == 0x03) {
      moveToTarget(standupS);
      Serial.println("ON");
    }
    if (Ircommand == 0x05) {
     walk = 1;
    Serial.println("walking");
    }else{walk = 0;
          state = 0;}

    if (Ircommand == 0x04) {
     left = 1;
    Serial.println("left");
    }else{left = 0;
          stateturnleft = 0;}

    if (Ircommand == 0x06) {
     right = 1;
    Serial.println("right");
    }else{right = 0;
          stateturnright = 0;}

    if (Ircommand == 0x07) {
     backward = 1;
    Serial.println("backward");
    }else{backward = 0;
          stateturnbackward = 0;}
  }

  IrReceiver.resume();
}
   unsigned long currentMillis = millis();

if(currentMillis - previousMillis >= interval){

 if(walk == 1){
switch(state){
  case 0:
    Serial.println("Enter CASE 0");
    if(moveToTarget(forwardStep1)){
      state = 1;
    }
    break;
  case 1:
    Serial.println("Enter CASE 1");
    if(moveToTarget(forwardStep2)){
      state = 2;
    }
    break;
  case 2:
    Serial.println("Enter CASE 2");
    if(moveToTarget(forwardStep3)){
      state = 3;
    }
    break;
  case 3:
    Serial.println("Enter CASE 3");
    if(moveToTarget(forwardStep4)){
      state = 4;
    }
    break;
      case 4:
    Serial.println("Enter CASE 4");
    if(moveToTarget(forwardStep5)){
      state = 5;
    walk = 0;
    left = 0;
    right = 0;
    backward = 0;
    standupbro = 0;
    }
    break;
  }
 }

  if(backward == 1){
switch(stateturnbackward){
  case 0:
    Serial.println("Enter CASE 0");
    if(moveToTarget(backwardStep1)){
      stateturnbackward = 1;
    }
    break;
  case 1:
    Serial.println("Enter CASE 1");
    if(moveToTarget(backwardStep2)){
      stateturnbackward = 2;
    }
    break;
  case 2:
    Serial.println("Enter CASE 2");
    if(moveToTarget(backwardStep3)){
      stateturnbackward = 3;
    }
    break;
  case 3:
    Serial.println("Enter CASE 3");
    if(moveToTarget(backwardStep4)){
      stateturnbackward = 4;
    }
    break;
      case 4:
    Serial.println("Enter CASE 4");
    if(moveToTarget(backwardStep5)){
      stateturnbackward = 5;
    }
    break;  
      case 5:
    Serial.println("Enter CASE 5");
    if(moveToTarget(backwardStep6)){
      stateturnbackward = 1;
    }
    break;
  }
 }

  if(left == 1){
switch(stateturnleft){
  case 0:
    Serial.println("Enter CASE 0");
    if(moveToTarget(turnleftStep1)){
      stateturnleft = 1;
    }
    break;
  case 1:
    Serial.println("Enter CASE 1");
    if(moveToTarget(turnleftStep2)){
      stateturnleft = 2;
    }
    break;
  case 2:
    Serial.println("Enter CASE 2");
    if(moveToTarget(turnleftStep3)){
      stateturnleft = 3;
    }
    break;
  case 3:
    Serial.println("Enter CASE 3");
    if(moveToTarget(turnleftStep4)){
      stateturnleft = 0;
    walk = 0;
    left = 0;
    right = 0;
    backward = 0;
    standupbro = 0;
    }
    break;
  }
 }

   if(right == 1){
switch(stateturnright){
  case 0:
    Serial.println("Enter CASE 0");
    if(moveToTarget(turnrightStep1)){
      stateturnright = 1;
    }
    break;
  case 1:
    Serial.println("Enter CASE 1");
    if(moveToTarget(turnrightStep2)){
      stateturnright = 2;
    }
    break;
  case 2:
    Serial.println("Enter CASE 2");
    if(moveToTarget(turnrightStep3)){
      stateturnright = 3;
    }
    break;
  case 3:
    Serial.println("Enter CASE 3");
    if(moveToTarget(turnrightStep4)){
      stateturnright = 0;
    walk = 0;
    left = 0;
    right = 0;
    backward = 0;
    standupbro = 0;
    }
    break;
  }
 }
  previousMillis = currentMillis;
}


  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {  // รับครบ 1 บรรทัด
      processCommand(input);
      input = "";
    } else {
      input += c;
    }
  }
}

void processCommand(String cmd) {
  cmd.trim();

  if (cmd.startsWith("S")) {
    int spaceIndex = cmd.indexOf(' ');
    
    if (spaceIndex > 1) {
      int servoIndex = cmd.substring(1, spaceIndex).toInt();
      int angle = cmd.substring(spaceIndex + 1).toInt();

      if (servoIndex >= 0 && servoIndex < 8 && angle >= 0 && angle <= 180) {
        servos[servoIndex].write(angle);
        Serial.print("Servo ");
        Serial.print(servoIndex);
        Serial.print(" -> ");
        Serial.println(angle);
      } else {
        Serial.println("Invalid index or angle");
      }
    }
  }
  if(cmd.startsWith("walk")){
  walk = 1;
  }
  if(cmd.startsWith("left")){
  left = 1;
  }
}

void standup (){
    for(int i = 0; i < 8; i++) {
    servos[i].attach(pins[i]);
    servos[i].write(standupS[i]); // ตั้งกลางก่อน
  }
}

bool moveToTarget(int target[]){
  bool done = false;

  while(!done){
    done = true;

    for(int i=0;i<8;i++){
      if(current[i] < target[i]){
        current[i]++;
        done = false;
      }
      else if(current[i] > target[i]){
        current[i]--;
        done = false;
      }

      servos[i].write(current[i]);
    }

    delay(2);
  }

  return true;
}
