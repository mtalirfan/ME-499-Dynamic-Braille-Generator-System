#include <Arduino.h>
#include <ArduinoSTL.h>
#include <string>

#include "braille_dictionaries.h"

// global variables
int first_pin = 22; // right-hand side pins of Arduino MEGA, 22 for cell 1, 46 for cell 5

int n_dots = 6; // 6-dot braille
int n_cells = 4; // 0 to 5

int timer_dot = 0; // ms for single dot
int timer_cell = 100; // ms for single cell of n_dots
int timer_display = 4000; // ms for display of n_cells

// function declarations
void display_braille(String brailled_text);

void setup() {

    Serial.begin(9600);

    for (int pin = first_pin; pin < (first_pin + n_dots * n_cells); pin++) {
        pinMode(pin, OUTPUT);
    }

}

String brailled_text = "110010 100010 111000 111000 101010 000000 000001 000111 010111";


void loop() {

    display_braille(brailled_text);

}

// functions
void display_braille(String brailled_text) {
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

    String cell = "";

    // Display brailled list
    for (int i = 0; i <= floor(brailled_list_length / n_cells); i++) {
        for (int j = 0; j < n_cells; j++) {

            if ((i * n_cells + j) >= brailled_list_length) {
              cell = "000000"; // remainder at the final n_cells loop
            } else {
              cell = brailled_list[i * n_cells + j];
            }

            // Get unicode character
            if (unicode.find(cell) != unicode.end()) {
                braille_unicode += unicode[cell];
                braille_unicode_spaced += String("  ") + unicode[cell] + String("  ");
            }

            // Build braille text lines
            braille_text_1 += String(" ") + cell.charAt(0) + String(" ") + cell.charAt(3) + String(" ");
            braille_text_2 += String(" ") + cell.charAt(1) + String(" ") + cell.charAt(4) + String(" ");
            braille_text_3 += String(" ") + cell.charAt(2) + String(" ") + cell.charAt(5) + String(" ");

            // Set pins to display braille cell on LEDs
            for (int k = 0; k < n_dots; k++) {
                digitalWrite(first_pin + j * n_dots + k, cell.charAt(k) - '0');
                delay(timer_dot);
            }
            delay(timer_cell);
        }
        delay(timer_display);
    }

    // CELL-BY-CELL LOOP
    // // loop count must be a multiple of n_cells
    // for (int i = 0; i < (brailled_list_length + ( n_cells - (brailled_list_length % n_cells) ) ) ; i++) {

    //     if (i >= (brailled_list_length) ) {
    //       cell = "000000"; // remainder at the final n_cells loop
    //     } else {
    //       cell = brailled_list[i];
    //     }

    //     // Get unicode character
    //     if (unicode.find(cell) != unicode.end()) {
    //         braille_unicode += unicode[cell];
    //         braille_unicode_spaced += String("  ") + unicode[cell] + String("  ");
    //     }

    //     // Build braille text lines
    //     braille_text_1 += String(" ") + cell.charAt(0) + String(" ") + cell.charAt(3) + String(" ");
    //     braille_text_2 += String(" ") + cell.charAt(1) + String(" ") + cell.charAt(4) + String(" ");
    //     braille_text_3 += String(" ") + cell.charAt(2) + String(" ") + cell.charAt(5) + String(" ");

    //     // Set pins to display braille cell on LEDs
    //     for (int j = 0; j < n_dots; j++) {
    //         digitalWrite(first_pin + (i % n_cells) * n_dots + j, cell.charAt(j) - '0');
    //     }

    //     delay(timer);
    // }

    // Printing the braille text
    Serial.println(brailled_text);
    Serial.println(braille_text_1);
    Serial.println(braille_text_2);
    Serial.println(braille_text_3);
    Serial.println(braille_unicode_spaced);
    Serial.println("");
    Serial.println(braille_unicode);
}