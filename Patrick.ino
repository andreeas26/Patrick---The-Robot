/*
    Patrick - The Robot
    Version: 1.0
    Author: Alex Bordei
    http://alexbordei.com/patrick-the-robot
*/

//Icluding libraries
#include <Servo.h>
#include <SoftwareSerial.h>

//Defining servos
Servo headServo;
#define headServoPin 9

// Defining motors

//Left
#define M_LF 4
#define M_LB 5

//Right
#define M_RF 3
#define M_RB 2

// Sensors
#define trigPin 7
#define echoPin 6

// the actual values for "fast" and "slow" depend on the motor
#define PWM_SPEED 130 //Defining motor speeds

// Calibrating motors
#define M_L_Calib 0
#define M_R_Calib 120

//Calibrating radar motor
#define radarMotor -8

//Other defines
#define BAUD_RATE 115200


SoftwareSerial ESP8266(10, 11);

// Other globals
long minimumDistance = 20;
int startTime = 2000;
boolean commandReceived = false;
boolean autoMode = false;

void setup() {

  //Initializing servos
  headServo.attach(headServoPin);
  headServo.write(90 + radarMotor);

  //Initializing sensors OUTPUTS
  pinMode(trigPin, OUTPUT);

  //Initializing sensors INPUT
  pinMode(echoPin, INPUT);

  // Initializing motors OUTPUTS
  pinMode(M_LF, OUTPUT);
  pinMode(M_LB, OUTPUT);
  pinMode(M_RF, OUTPUT);
  pinMode(M_RB, OUTPUT);

  Serial.begin(BAUD_RATE);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  ESP8266.begin(BAUD_RATE);

  delay(startTime);

}
//wifi.setmode(wifi.STATION)
//wifi.sta.config("Alex Bordei", "nimicMaigreu")
//print(wifi.sta.getip())

void loop() {

  if (Serial.available() > 0) {
    ESP8266.print(Serial.read());
  }
  if (ESP8266.available() > 0) {
    processCommand(ESP8266.read());
  }


  if (autoMode) {
    if (getDistance() > minimumDistance) {
      moveRobot(0);
      delay(100);
    }
    else {
      motorsOFF();
      delay(500);
      int lookDirection = random(0, 2);
      if (look(lookDirection) > minimumDistance) {
        moveRobot(lookDirection + 2);
        delay(random(200, 500));
      }
    }
  }
}

long getDistance() {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  return distance;
}

void motorsOFF() {
  digitalWrite(M_LF, LOW);
  digitalWrite(M_LB, LOW);
  digitalWrite(M_RF, LOW);
  digitalWrite(M_RB, LOW);
}

long look(int way) {
  switch (way) {
    case 0:
      headServo.write(random(120 + radarMotor, 180 + radarMotor)); //Look left
      delay(1000);
      break;
    case 1:
      headServo.write(random(0, 60 + radarMotor)); //look right
      delay(1000);
      break;
  }
  headServo.write(70);
  return getDistance();
}
void moveRobot(int direction) {
  motorsOFF();
  switch (direction) {
    case 0: //Move front
      analogWrite(M_LF, PWM_SPEED + M_L_Calib);
      analogWrite(M_RF, PWM_SPEED + M_R_Calib);
      break;
    case 1: //Move back
      analogWrite(M_LB, PWM_SPEED + M_L_Calib);
      analogWrite(M_RB, PWM_SPEED + M_R_Calib);
      break;
    case 2: //Turn left
      analogWrite(M_LB, PWM_SPEED + M_L_Calib);
      analogWrite(M_RF, PWM_SPEED + M_R_Calib);
      break;
    case 3: //Turn right
      analogWrite(M_LF, PWM_SPEED + M_L_Calib);
      analogWrite(M_RB, PWM_SPEED + M_R_Calib);
      break;
  }
}

void processCommand(char command)
{
  if (command == 49)
  {
    if (commandReceived == false) {
      autoMode = false;
      moveRobot(0);
      commandReceived = true;
      delay(100);
      motorsOFF();

    }
  }
  else if (command == 50)
  {
    if (commandReceived == false) {
      autoMode = false;
      moveRobot(1);
      commandReceived = true;
      delay(100);
      motorsOFF();
    }
  }
  else if (command == 52)
  {
    if (commandReceived == false) {
      autoMode = false;
      moveRobot(2);
      commandReceived = true;
      delay(100);
      motorsOFF();
    }
  }
  else if (command == 51)
  {
    if (commandReceived == false) {
      autoMode = false;
      moveRobot(3);
      commandReceived = true;
      delay(100);
      motorsOFF();
    }
  }
  else  if (command == 53)
  {
    if (commandReceived == false) {
      autoMode = true;
      commandReceived = true;
      delay(100);
      motorsOFF();
    }
  }
  else  if (command == 54)
  {
    if (commandReceived == false) {
      autoMode = false;
      commandReceived = true;
      delay(100);
      motorsOFF();
    }
  }

  commandReceived = false;
}
