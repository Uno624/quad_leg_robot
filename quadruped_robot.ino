#include <Servo.h>

#define centorS1 90
#define centorS2 85
#define centorS3 85
#define centorS4 90
#define centorS5 95
#define centorS6 85
#define centorS7 90
#define centorS8 80

#define standupS1 40
#define standupS2 140
#define standupS3 30
#define standupS4 140
#define standupS5 50
#define standupS6 100
#define standupS7 70
#define standupS8 100

Servo servos[8];
int pins[8] = {2,3,4,5,6,7,8,9};
int current[8] = {centorS1,centorS2,centorS3,centorS4,centorS5,centorS6,centorS7,centorS8};
int centerS[8] = {centorS1,centorS2,centorS3,centorS4,centorS5,centorS6,centorS7,centorS8};
int standupS[8] = {standupS1,standupS2,standupS3,standupS4,standupS5,standupS6,standupS7,standupS8};


String input = "";

void setup() {
  Serial.begin(115200);

  for(int i = 0; i < 8; i++) {
    servos[i].attach(pins[i]);
    servos[i].write(centerS[i]);
  }
  delay(2500);
  Serial.println("Ready. Use: S<index> <angle>");
}
unsigned long previousMillis = 0;
const long interval = 10; // 1 second
void loop() {
   unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= interval){
   //updateServos();
    previousMillis = currentMillis;}


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
  if(cmd.startsWith("standup")){
    standup();
  }
}

void standup (){
    for(int i = 0; i < 8; i++) {
    servos[i].attach(pins[i]);
    servos[i].write(standupS[i]); // ตั้งกลางก่อน
  }
}

bool updateServos(){
  bool done = true;

  for(int i=7; i>=0; i--){
    if(current[i] < standupS[i]){
      current[i]++;
      done = false;
    }
    else if(current[i] > standupS[i]){
      current[i]--;
      done = false;
    }

    servos[i].write(current[i]);
  }

  return done;
}