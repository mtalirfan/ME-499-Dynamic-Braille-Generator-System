
// global variables

int n_dots = 6; // 6 dot braille cell
int n_cells = 2; // 1 or 2

int first_pin = 22; // right-hand side pins of Arduino MEGA

int first_pin_negative = 34;

int timer = 500; // ms for dot switch

void setup() {

  for (int pin = first_pin; pin < (first_pin + n_dots * n_cells); pin++) {
    pinMode(pin, OUTPUT);
  }

  for (int pin = first_pin_negative; pin < (first_pin_negative + n_dots * n_cells); pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  Serial.begin(9600);

}

void loop() {

    digitalWrite(first_pin, HIGH);
    delay(timer);

    digitalWrite(first_pin, LOW);
    delay(timer);

    digitalWrite(first_pin_negative, HIGH);
    delay(timer);

    digitalWrite(first_pin_negative, LOW);
    delay(timer);

}
