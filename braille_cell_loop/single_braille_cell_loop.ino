
int timer = 100; 

int n_cells = 1; // 0 to 5

void setup() {

    Serial.begin(9600);

    for (int pin = 22; pin <= (22 + 6 * n_cells); pin++) {
      pinMode(pin, OUTPUT);
    }

}

void loop() {

  for (int pin = 22; pin <= (22 + 6 * n_cells); pin++) {
    digitalWrite(pin, HIGH);
    delay(timer);
  }

  for (int pin = 22; pin <= (22 + 6 * n_cells); pin++) {
    digitalWrite(pin, LOW);
    delay(timer);
  }

}
