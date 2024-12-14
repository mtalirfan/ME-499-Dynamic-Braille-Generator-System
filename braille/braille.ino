#include <Arduino.h>
#include <ArduinoSTL.h>
#include <string>
#include <map>

#include "braille_dictionaries.h"

int first_pin = 22; // right-hand side pins of Arduino MEGA

int timer = 200; // ms for dot switch

int n_dots = 6;
int n_cells = 1; // 0 to 5

int br[7] = {0, 0, 0, 0, 0, 0, 0}; // index 0 unused


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

    // Simulate a delay as in sleep(timer) in Python
    delay(timer); // Adjust timer as necessary
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

void setup() {

  // Populate alphanumeric dictionary with alphanumneric values, as in python code
  String alphanumeric_string = "‎1234567890abcdefghijklmnopqrstuvxyz‎‎‎‎wABCDEFGHIJKLMNOPQRSTUVXYZ‎‎‎‎W";
  // indices 0, 36, 37, 38, 39, 66, 67, 68, 69 unused

  std::vector<char> alphanumeric_list(alphanumeric_string.begin(), alphanumeric_string.end());

  for (int i = 0; i < alphanumeric_list.size(); i++) {
    String alphanumeric_code = "";
    if (isupper(alphanumeric_list[i])) {
        alphanumeric_code += "000001 ";  // originally capitals were intended to be used from those populated in dictionary, now they are being converted to lowercase during processing
    } else if (islower(alphanumeric_list[i])) {
        // do nothing
    } else if (isdigit(alphanumeric_list[i])) {
        // do nothing
    }

    String str_to_append = "";
    switch (i % 10) {
        case 1:
            str_to_append = "10";
            if (i == 21 || i == 51 || i == 31 || i == 61) {
                str_to_append += "1";
            } else {
                str_to_append += "0";
            }
            str_to_append += "00";
            if (i == 31 || i == 61) {
                str_to_append += "1 ";
            } else {
                str_to_append += "0 ";
            }
            alphanumeric_code += str_to_append;
            break;
        case 2:
            str_to_append = "11";
            if (i == 22 || i == 52 || i == 32 || i == 62) {
                str_to_append += "1";
            } else {
                str_to_append += "0";
            }
            str_to_append += "00";
            if (i == 32 || i == 62) {
                str_to_append += "1 ";
            } else {
                str_to_append += "0 ";
            }
            alphanumeric_code += str_to_append;
            break;
        case 3:
            str_to_append = "10";
            if (i == 23 || i == 53 || i == 33 || i == 63) {
                str_to_append += "1";
            } else {
                str_to_append += "0";
            }
            str_to_append += "10";
            if (i == 33 || i == 63) {
                str_to_append += "1 ";
            } else {
                str_to_append += "0 ";
            }
            alphanumeric_code += str_to_append;
            break;
        case 4:
            str_to_append = "10";
            if (i == 24 || i == 54 || i == 34 || i == 64) {
                str_to_append += "1";
            } else {
                str_to_append += "0";
            }
            str_to_append += "11";
            if (i == 34 || i == 64) {
                str_to_append += "1 ";
            } else {
                str_to_append += "0 ";
            }
            alphanumeric_code += str_to_append;
            break;
        case 5:
            str_to_append = "10";
            if (i == 25 || i == 55 || i == 35 || i == 65) {
                str_to_append += "1";
            } else {
                str_to_append += "0";
            }
            str_to_append += "01";
            if (i == 35 || i == 65) {
                str_to_append += "1 ";
            } else {
                str_to_append += "0 ";
            }
            alphanumeric_code += str_to_append;
            break;
        case 6:
            str_to_append = "11";
            if (i == 26 || i == 56 || i == 36 || i == 66) {
                str_to_append += "1";
            } else {
                str_to_append += "0";
            }
            str_to_append += "10";
            if (i == 36 || i == 66) {
                str_to_append += "1 ";
            } else {
                str_to_append += "0 ";
            }
            alphanumeric_code += str_to_append;
            break;
        case 7:
            str_to_append = "11";
            if (i == 27 || i == 57 || i == 37 || i == 67) {
                str_to_append += "1";
            } else {
                str_to_append += "0";
            }
            str_to_append += "11";
            if (i == 37 || i == 67) {
                str_to_append += "1 ";
            } else {
                str_to_append += "0 ";
            }
            alphanumeric_code += str_to_append;
            break;
        case 8:
            str_to_append = "11";
            if (i == 28 || i == 58 || i == 38 || i == 68) {
                str_to_append += "1";
            } else {
                str_to_append += "0";
            }
            str_to_append += "01";
            if (i == 38 || i == 68) {
                str_to_append += "1 ";
            } else {
                str_to_append += "0 ";
            }
            alphanumeric_code += str_to_append;
            break;
        case 9:
            str_to_append = "01";
            if (i == 29 || i == 59 || i == 39 || i == 69) {
                str_to_append += "1";
            } else {
                str_to_append += "0";
            }
            str_to_append += "10";
            if (i == 39 || i == 69) {
                str_to_append += "1 ";
            } else {
                str_to_append += "0 ";
            }
            alphanumeric_code += str_to_append;
            break;
        case 0:
            str_to_append = "01";
            if (i == 30 || i == 60) {
                str_to_append += "1";
            } else {
                str_to_append += "0";
            }
            str_to_append += "11";
            if (i == 40 || i == 70) {
                str_to_append += "1 ";
            } else {
                str_to_append += "0 ";
            }
            alphanumeric_code += str_to_append;
            break;
    }

    alphanumeric[String(alphanumeric_list[i])] = alphanumeric_code;
  }

  alphanumeric.erase(alphanumeric.find("\u200e"));

  Serial.begin(9600);

  for (int pin = first_pin; pin <= (first_pin + n_dots * n_cells); pin++) {
    pinMode(pin, OUTPUT);
  }

  String brailled_text = "100000 101000 110000";

  display_braille(brailled_text);

}

void loop() {

  // for (int pin = 22; pin <= (22 + 6 * n_cells); pin++) {
  //   digitalWrite(pin, HIGH);
  //   delay(timer);
  // }


  // display the final braille string

//   for (int pin = first_pin; pin <= (first_pin + n_dots * n_cells); pin++) {
//     int dot_number = ((pin - first_pin) % n_dots) + 1;
//     if (br[dot_number] == 1) {
//       digitalWrite(pin, HIGH);
//       delay(timer);

//         if (dot_number == 6) {
//         br[1] = 1;
//         } else {
//         br[dot_number + 1] = 1;
//         }

//     } else {
//       digitalWrite(pin, LOW);
//       delay(timer);
//     }

//   }

}
