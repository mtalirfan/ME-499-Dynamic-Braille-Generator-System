#include <Arduino.h>
#include <ArduinoSTL.h>
#include <string>

#include "braille_dictionaries.h"

// global variables
int first_pin = 22; // right-hand side pins of Arduino MEGA

int timer = 1000; // ms for dot switch

int n_dots = 6;
int n_cells = 1; // 0 to 5

int br[7] = {0, 0, 0, 0, 0, 0, 0}; // index 0 unused

// function declarations
String display_braille(String brailled_text);

void setup() {

    Serial.begin(9600);

    for (int pin = first_pin; pin <= (first_pin + n_dots * n_cells); pin++) {
        pinMode(pin, OUTPUT);
    }

    String brailled_text = "100000 101100 110000 011011";

    display_braille(brailled_text);

}

void loop() {

}

// functions
String display_braille(String brailled_text) {
  // Splitting the brailled_text into a list
  String brailled_list[100]; // Assuming a maximum of 100 elements
  int brailled_list_length = 0;
  int lastIndex = 0;
  for (int i = 0; i < brailled_text.length(); i++) {
    if (brailled_text.charAt(i) == ' ') {
      brailled_list[brailled_list_length] = brailled_text.substring(lastIndex, i);
      brailled_list_length++;
      lastIndex = i + 1;
    }
  }
  brailled_list[brailled_list_length] = brailled_text.substring(lastIndex);
  brailled_list_length++;

  // Variables to store braille text
  String braille_text_1 = "";
  String braille_text_2 = "";
  String braille_text_3 = "";
  String braille_unicode_spaced = "";
  String braille_unicode = "";

  // Display brailled list
  for (int i = 0; i < brailled_list_length; i++) {
    if (unicode.find(brailled_list[i]) != unicode.end()) {
      braille_unicode += unicode[brailled_list[i]];
      braille_unicode_spaced += String("  ") + unicode[brailled_list[i]] + String("  ");
    }

    // Build braille text lines
    String br = brailled_list[i];
    braille_text_1 += String(" ") + br.charAt(0) + String(" ") + br.charAt(3) + String(" ");
    braille_text_2 += String(" ") + br.charAt(1) + String(" ") + br.charAt(4) + String(" ");
    braille_text_3 += String(" ") + br.charAt(2) + String(" ") + br.charAt(5) + String(" ");

    delay(timer);
  }

  // Printing the braille text
  Serial.println(brailled_text);

  Serial.println(braille_text_1);
  Serial.println(braille_text_2);
  Serial.println(braille_text_3);
  Serial.println(braille_unicode_spaced);
  Serial.println("");
  Serial.println(braille_unicode);
}