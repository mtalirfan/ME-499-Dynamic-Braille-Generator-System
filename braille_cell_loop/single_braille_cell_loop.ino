
// global variables
int first_pin = 22; // right-hand side pins of Arduino MEGA

int timer = 100; // ms for dot switch

int n_dots = 6;
int n_cells = 1; // 0 to 5

void setup() {

  for (int pin = first_pin; pin <= (first_pin + n_dots * n_cells); pin++) {
    pinMode(pin, OUTPUT);
  }
  Serial.begin(9600);

}

void loop() {

  for (int pin = first_pin; pin <= (first_pin + n_dots * n_cells); pin++) {
    digitalWrite(pin, HIGH);
    delay(timer);
  }

  for (int pin = first_pin; pin <= (first_pin + n_dots * n_cells); pin++) {
    digitalWrite(pin, LOW);
    delay(timer);
  }

}
