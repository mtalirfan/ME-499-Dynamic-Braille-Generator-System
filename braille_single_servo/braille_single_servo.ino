#include <Servo.h>

Servo servo1;  // create servo object to control a servo

int first_pin = 22;

int pos = 0;    // variable to store the servo position

int angle_max = 5; // max angle

int timer = 1000;

void setup() {
  servo1.attach(first_pin);  // attaches the servo on pin 22 to the servo object
}

void loop() {

  for (pos = 0; pos <= angle_max; pos += 1) {
    // in steps of 1 degree
    servo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  delay(timer);

  for (pos = angle_max; pos >= 0; pos -= 1) {
    servo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  delay(timer);

}