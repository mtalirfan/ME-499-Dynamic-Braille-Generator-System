#include <Servo.h>

int n_dots = 6; // 6 dot braille cell
int n_cells = 1; // 1 or 2

const byte servoPins[] = {8, 9, 10, 11, 12, 13}; // {8, 9, 10, 11, 12, 13};

int pos = 0;
byte servoPos[] = {0, 0, 0, 0, 0, 0}; //leave 0
const byte servoAttPos[] = {0, 0, 0, 0, 0, 0};
const byte servoMinPos[] = {0, 0, 0, 0, 0, 0};
const byte servoMaxPos[] = {4, 4, 4, 4, 4, 4};
const byte servoInterval[] = {100, 100, 100, 100, 100, 100}; //larger numbers are slower, 250 hardly notice, 10 is quick
int servoIncrement[] = {-1, -1, -1, -1, -1, -1}; //probably leave -1 -1, it starts off "going down" from the attach pos
unsigned long servoPrevMillis[] = {0, 0, 0, 0, 0, 0}; //leave 0 0

const byte numberOfServos = sizeof(servoPins)/sizeof(servoPins[0]);
Servo servo[numberOfServos];

void setup() {

  Serial.begin(9600);

  for (byte i = 0; i < numberOfServos; i++)
  {

    Serial.print("Attaching servo "); Serial.print(i + 1);
    Serial.print(" to pin "); Serial.print(servoPins[i]);
    servoPos[i] = servoAttPos[i];
    servo[i].write(servoPos[i]);
    servo[i].attach(servoPins[i]);


  }

}

void loop() {
  doServos();
}


void doServos()
{
  for (byte i = 0; i < numberOfServos; i++)
  {

    for (pos = servoMinPos[i]; pos <= servoMaxPos[i]; pos += 1) {
      servo[i].write(pos); //move the servo
      delay(150);
    }

    delay(1000);

    for (pos = servoMaxPos[i]; pos >= servoMinPos[i]; pos -= 1) {
      servo[i].write(pos); //move the servo
      delay(150);                       // waits 15ms for the servo to reach the position
    }
  } //for over the servos
} //doServos


