/* 
 *  Patrick - The Robot
 *  Version: 1.0
 *  Author: Alex Bordei
 *  http://alexbordei.com/patrick-the-robot
*/

//Icluding libraries
#include <Servo.h>

//Defining servos
Servo headServo;
#define headServoPin 9

// Defining motors

//Left
#define M_LF 2
#define M_LB 4

//Right
#define M_RF 5
#define M_RB 3

// Sensors
#define trigPin 7
#define echoPin 6

// Other globals
long minimumDistance = 20;

void setup() {
  
  //Initializing servos
  headServo.attach(headServoPin);
  headServo.write(70);

  //Initializing sensors OUTPUTS
  pinMode(trigPin, OUTPUT);

  //Initializing sensors INPUT
  pinMode(echoPin, INPUT);

  // Initializing motors OUTPUTS
  pinMode(M_LF, OUTPUT);
  pinMode(M_LB, OUTPUT);
  pinMode(M_RF, OUTPUT);
  pinMode(M_RB, OUTPUT);
  
}

void loop() {
  
    if (getDistance() > minimumDistance){
      moveRobot(0);
      }
      else{
        motorsOFF();
        delay(500);
        int lookDirection = random(0, 2);
        if (look(lookDirection) > minimumDistance){
            moveRobot(lookDirection + 2);
            delay(random(500, 1000));
          }
        }
}

long getDistance(){
  long duration, distance;
    
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

    return distance;
  }

void motorsOFF(){
  digitalWrite(M_LF, LOW);
  digitalWrite(M_LB, LOW);
  digitalWrite(M_RF, LOW);
  digitalWrite(M_RB, LOW);
  }

long look(int way){
  switch(way){
      case 0:
        headServo.write(random(120, 180)); //Look left
        delay(1000);
        break;
      case 1:
        headServo.write(random(0, 60)); //look right
        delay(1000);
        break;
    }
    headServo.write(70);
    return getDistance();
}
void moveRobot(int direction){
  motorsOFF();
  switch(direction){
    case 0: //Move front
      digitalWrite(M_LF, HIGH);
      digitalWrite(M_RF, HIGH);
      break;
    case 1: //Move back
      digitalWrite(M_LB, HIGH);
      digitalWrite(M_RB, HIGH);
      break;
    case 2: //Turn left
      digitalWrite(M_LB, HIGH);
      digitalWrite(M_RF, HIGH);
      break;
    case 3: //Turn right
      digitalWrite(M_LF, HIGH);
      digitalWrite(M_RB, HIGH);
      break;
    }
  }
