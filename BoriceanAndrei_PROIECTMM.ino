


#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 50
#define MAX_SPEED 190
#define MAX_SPEED_OFFSET 20 //de sters 

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
Servo myservo;   

boolean goesForward=false;
int distance = 20;
int speedSet = 0;

void setup() {

  myservo.attach(10);  //se selecteaza pin-ul pe care e servom
  myservo.write(115);  //se scrie unghiul la care este setat sa fie (in fata)
  delay(2000); //delay sa astepte 2 secunde dupa pornire
  distance = readPing(); //citeste distanta din ultrasonic
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

 if(distance<=15) //initial parametrii se seteaza cu 0, daca e mai mic decat 15, a detectat un obiect in fata sa
 {
  moveStop(); //se opreste
  delay(100);
  moveBackward(); //da cu spatele dupa 0.3 sec
  delay(300);
  moveStop();
  delay(200);
  distanceR = lookRight(); //verifica daca are in partea stanga/dreapta mai mult loc 
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL) //daca in dreapta are mai mult loc, face dreapta and so on
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
 }
 distance = readPing(); //daca distanta este egala merge inainte
}

int lookRight() //de schimbat
{
    myservo.write(50); //se pozitioneaza servoul la 50 de grade ca sa se citeasca
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); //se readuce in pozitia initiala
    return distance;
}

int lookLeft() //de schimbat
{
    myservo.write(190); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}

int readPing() { //folosim functia sonar.ping.cm ca sa aflam distanta
  delay(50);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 150;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true; //facem sa mearga inainte
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
     
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) //incrementam asa ca datorita delayului de 5 se misca ok, daca incrementam cu 1 cu delayul de 5 era mult mai slow
   {
    motor1.setSpeed(speedSet);// dam viteza la motoare
    motor2.setSpeed(speedSet);
 
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) 
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
  
    delay(5);
  }
  

void turnRight() {    ////de shcimbat
  motor1.run(FORWARD);  //fctile folosite pt algoritmul de ocolire a obiectelor
  motor2.run(BACKWARD);  
  delay(500);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);
      
} 
 
void turnLeft() {
  motor1.run(BACKWARD);     
  motor2.run(FORWARD);   
  delay(500);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
 
}  
