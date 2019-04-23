#include <Servo.h>
float distance;
Servo myservo;
int pos = 0;
int distanceThreshold = 50;
int cm = 0;
int inches = 0;
long r;
int minimi = 25;
int motor = 11;
int speed = 30;
void setup()  
{
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  myservo.attach(4);
  pinMode(12, OUTPUT);
  pinMode(8, OUTPUT);
  for (pos = 0; pos <= 90; pos += 1){
    myservo.write(pos);
    delay(15);
  }
  
}
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void loop(){
  analogWrite(motor, speed);
  Serial.print("start ");
  cm = 0.01723 * readUltrasonicDistance(10, 13);
  Serial.print(cm);
  Serial.print("cm \n");
  if (cm < distanceThreshold && cm > minimi) {
    r = random(1, 100);
    Serial.print(r);
    Serial.print(" on r");
    if (r < 75) {
      for (pos = 90; pos >= 45; pos -= 1){
        myservo.write(pos);
        delay(15);
        }
        while (cm < distanceThreshold || cm > 500){
          digitalWrite(12, HIGH);
          delay(500);
          digitalWrite(12, LOW);
          delay(500);
          cm = 0.01723 * readUltrasonicDistance(10, 13);
        }
        for (pos = 45; pos <= 90; pos += 1){
          myservo.write(pos);
          delay(15);
        }
    }
    else if (r >= 75) {
      for (pos = 90; pos <= 135; pos += 1){
        myservo.write(pos);
        delay(15);
      }
      while (cm < distanceThreshold || cm > 500){
        digitalWrite(8, HIGH);
        delay(500);
        digitalWrite(8, LOW);
        delay(500);
        cm = 0.01723 * readUltrasonicDistance(10, 13);
      }
      for (pos = 135; pos >= 90; pos -= 1){
        myservo.write(pos);
      delay(15);
      }
    }
  }
}
