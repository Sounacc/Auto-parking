
#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 
#include <Adafruit_MotorShield.h>
#define TRIG_PIN A0 
#define ECHO_PIN1 A1
#define ECHO_PIN2 A2
#define ECHO_PIN3 A3
#define ECHO_PIN4 A4 
#define MAX_DISTANCE 200 
#define MAX_SPEED 180 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

NewPing sonar1(TRIG_PIN, ECHO_PIN1, MAX_DISTANCE);
//NewPing sonar2(TRIG_PIN,ECHO_PIN2,MAX_DISTANCE);
//NewPing sonar3(TRIG_PIN,ECHO_PIN3,MAX_DISTANCE);
//NewPing sonar4(TRIG_PIN,ECHO_PIN4,MAX_DISTANCE);   

AF_DCMotor motor1(1); 
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
Servo myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;
int flag=0;

void setup() {
  Serial.begin(9600);
  myservo.attach(10);  
  myservo.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}
void loop() {
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 
 if(distance<=25&&flag==0)
 {
  moveStop();
  delay(100);
  /*moveBackward();
  delay(300);*/
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);
  if(distanceR<=20 && distanceL<=20 && distance<=24){
    moveStop();
    flag=1;
  }
  else if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else if (flag==0)
 {
  moveForward();
 }
 else{;}
 distance = readPing();
}



int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar1.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
/*int readPing2() { 
  delay(70);
  int cm = sonar2.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
int readPing3() { 
  delay(70);
  int cm = sonar3.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
int readPing4() { 
  delay(70);
  int cm = sonar4.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}*/
void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  } 
  
void moveForward2(){
  if(!goesForward)
  {
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);
  
  for(speedSet=0;speedSet<40;speedSet+=2)
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}
}
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);     
   for (speedSet = 0; speedSet < 80; speedSet +=2) //speed up the motor
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);  
  for (speedSet = 0; speedSet < 80; speedSet +=2) //speed up the motor
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}  

void turnRight() {
  motor1.run(FORWARD);
  motor4.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);     
  delay(630);
  /*motor1.run(FORWARD);      
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);*/      
} 
 
void turnLeft() {
  motor1.run(BACKWARD);     
  motor4.run(BACKWARD);  
  motor2.run(FORWARD);
  motor3.run(FORWARD);   
  delay(630);
  /*motor1.run(FORWARD);     
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);*/
}  
