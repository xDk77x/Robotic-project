#include<Servo.h>
#include<NewPing.h>


int servo1 = 12;
int distance = 0;
int Rdistance = 0;
int Ldistance = 0;
int leftBackward = 8;
int leftForward = 7;
int rightForward = 4;
int rightBackward = 2;
int workingLed = 13;

NewPing dist(3, A1, 300); //trig, echo, dist max
Servo servo;

void setup() {
  pinMode(leftBackward, OUTPUT);
  pinMode(leftForward, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);
  pinMode(workingLed, OUTPUT);
  digitalWrite(workingLed, HIGH);
  servo.attach(servo1);
  servo.write(115);
  delay(1000);
  servo.write(65);
  delay(500);
  servo.write(160);
  delay(500);
  servo.write(115);
  Serial.begin(9600);
}

void loop() {

    distance =  MeasureDistance();
    Serial.println(distance);



    if (distance >= 40 && distance <= 250) {
      Forward();
    }
    else if (distance < 40) {
      Stop();
      delay(50);
      Backward();
      delay(1000);
      Stop();
      delay(50);
      Rdistance = LookRight();
      delay(200);
      Ldistance = LookLeft();
      delay(200);

      if (Rdistance >= Ldistance) {
        TurnRight();
        Stop();
      }
      else if (Ldistance >= Rdistance) {
        TurnLeft();
        Stop();
      }
    }

}


int MeasureDistance() {
  delay(10);
  int distanceCM = dist.ping_cm();
  if (distanceCM <= 0 || distanceCM >= 350) {
    distanceCM = 350;
  }
  return distanceCM;
}

int LookRight() {
  servo.write(60);
  delay(400);
  int distance = MeasureDistance();
  return distance;

}

int LookLeft() {
  servo.write(165);
  delay(400);
  int distance = MeasureDistance();
  delay(50);
  servo.write(115);
  return distance;
}



void Forward() {
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);
}

void Backward() {
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, HIGH);
}

void TurnLeft() {
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);
  delay(300);
}

void TurnRight() {
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, HIGH);
  delay(300);
}

void Stop() {
  digitalWrite(leftForward, 0);
  digitalWrite(leftBackward, 0);
  digitalWrite(rightForward, 0);
  digitalWrite(rightBackward, 0);
}