#include <ArduinoSTL.h>
#include <vector>

#include "braille_dictionaries.h"

// global variables
int first_pin = 22; // right-hand side pins of Arduino MEGA, 22 for cell 1, 46 for cell 5

int n_dots = 6; // 6-dot braille
int n_cells = 4; // 0 to 5

int timer_dot = 0; // ms for single dot
int timer_cell = 100; // ms for single cell of n_dots
int timer_display = 1000; // ms for display of n_cells

// function declarations
String space_out_symbols_punctuation(String text);
String space_out_alphanumeric(String text_sym_spaced);

String convert_numeric_character(String brailled_text_num_word);
String convert_symbols_punctuation(String brailled_text_num);
String convert_capital(String brailled_text_sym);

String convert_lowercase_grade1(String brailled_text_caps);
String correct_spacing(String brailled_text_spaced);

void display_braille(String brailled_text);


void setup() {

    Serial.begin(115200);

    for (int pin = first_pin; pin < (first_pin + n_dots * n_cells); pin++) {
        pinMode(pin, OUTPUT);
    }

    String text = F("\"Hello World!\" 12345");

    // Process
    String text_sym_spaced = space_out_symbols_punctuation(text);
    String text_alphanumeric_spaced = space_out_alphanumeric(text_sym_spaced);

    String brailled_text_num = convert_numeric_character(text_alphanumeric_spaced);
    String brailled_text_sym = convert_symbols_punctuation(brailled_text_num);
    String brailled_text_caps = convert_capital(brailled_text_sym);

    String brailled_text_spaced = convert_lowercase_grade1(brailled_text_caps);
    String brailled_text = correct_spacing(brailled_text_spaced);

    display_braille(brailled_text);
}

void loop() {

    // String brailled_text = F("110010 100010 111000 111000 101010 000000 000001 000111 010111 110010 100010 111000 110010 100010 111000 111000 111000 101010 000000 000001 000111 010111 110010 100010 111000 110010 100010 111000 111000 111000 101010 000000 000001 000111 010111 110010 100010 111000 110010 100010 111000 111000 111000 101010 000000 000001 000111 010111 110010 100010 111000 110010 100010 111000");
    // display_braille(brailled_text);

}

// functions

String space_out_symbols_punctuation(String text) {

    Serial.println(text);

    String text_sym_spaced = "";
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == ' ') {
            text_sym_spaced += " ‎ ";
        } else if (punctuation.find(String(text[i])) != punctuation.end()) {
            text_sym_spaced += " " + String(text[i]) + " ";
        } else {
            text_sym_spaced += String(text[i]);
        }
    }

    // Opening and Closing Quotations do not display in Serial Monitor and won't convert
    // // count all double quotations to replace for opening and closing
    // int quotation_count = 0;
    // for (int i = 0; i < text_sym_spaced.length(); i++) {
    //     if (text_sym_spaced[i] == '"') {
    //         quotation_count++;
    //     }
    // }

    // // Replace nth substrings of "foo" to be replaced
    // for (int n = quotation_count; n >= 2; n -= 2) {
    //     int nthOccur = 0;
    //     for (int i = 0; i < text_sym_spaced.length(); i++) {
    //         if (text_sym_spaced[i] == '"') {
    //             nthOccur++;
    //             if (nthOccur == n) {
    //                 text_sym_spaced[i] = '”';
    //             } else if (nthOccur == n - 1) {
    //                 text_sym_spaced[i] = '"';
    //             }
    //         }
    //     }
    // }

    // for (int i = 0; i < text_sym_spaced.length(); i++) {
    //     if (text_sym_spaced[i] == '"') {
    //         text_sym_spaced[i] = '“';
    //     }
    // }


    Serial.println(text_sym_spaced);

    return text_sym_spaced;
}

String space_out_alphanumeric(String text_sym_spaced) {
    String text_alphanumeric_spaced = "";
    for (int i = 0; i < text_sym_spaced.length(); i++) {
        if (i < (text_sym_spaced.length() - 1)) {
            if ((isdigit(text_sym_spaced[i]) && isalpha(text_sym_spaced[i + 1])) || 
                (isalpha(text_sym_spaced[i]) && isdigit(text_sym_spaced[i + 1]))) {
                text_alphanumeric_spaced += String(text_sym_spaced[i]) + " ";
            } else {
                text_alphanumeric_spaced += String(text_sym_spaced[i]);
            }
        } else {
            text_alphanumeric_spaced += String(text_sym_spaced[i]);
        }
    }

    Serial.println(text_alphanumeric_spaced);

    return text_alphanumeric_spaced;
}

// TODO: Numeric Word and Character functions

String convert_numeric_character(String brailled_text_num_word) {
    String brailled_text_num = "";
    for (int i = 0; i < brailled_text_num_word.length(); i++) {
        if (isdigit(brailled_text_num_word.charAt(i))) {
            brailled_text_num += " 001111 " + alphanumeric[String(brailled_text_num_word.charAt(i))] + " ";
        } else {
            brailled_text_num += brailled_text_num_word.charAt(i);
        }
    }

    Serial.println(brailled_text_num);

    return brailled_text_num;
}

String convert_symbols_punctuation(String brailled_text_num) {
    std::vector<String> text_list_num;
    String token = "";
    for (int i = 0; i < brailled_text_num.length(); i++) {
        if (brailled_text_num[i] == ' ') {
            if (token.length() > 0) {
                text_list_num.push_back(token);
                token = "";
            }
        } else {
            token += brailled_text_num[i];
        }
    }
    if (token.length() > 0) {
        text_list_num.push_back(token);
    }

    String brailled_text_sym = "";
    for (int i = 0; i < text_list_num.size(); i++) {
        if (punctuation.find(text_list_num[i]) != punctuation.end()) {
            brailled_text_sym += punctuation[text_list_num[i]];
        } else {
            brailled_text_sym += text_list_num[i] + " ";
        }
    }

    Serial.println(brailled_text_sym);

    return brailled_text_sym;
}

// TODO: Capital Word and Character functions

String convert_capital(String brailled_text_sym) {

    String brailled_text_caps = "";
    for (int i = 0; i < brailled_text_sym.length(); i++) {
        if (isalpha(brailled_text_sym.charAt(i)) && isupper(brailled_text_sym.charAt(i))) {
            brailled_text_caps += alphanumeric[String(brailled_text_sym.charAt(i))] + " ";
        } else {
            brailled_text_caps += brailled_text_sym.charAt(i);
        }
    }

    Serial.println(brailled_text_caps);

    return brailled_text_caps;
}

String convert_lowercase_grade1(String brailled_text_caps) {

    String brailled_text_spaced = "";
    for (int i = 0; i < brailled_text_caps.length(); i++) {
        if (isalpha(brailled_text_caps.charAt(i))) {
            brailled_text_spaced += alphanumeric[String(brailled_text_caps.charAt(i))];
        } else if (isdigit(brailled_text_caps[i]) || brailled_text_caps[i] == ' ') {
            brailled_text_spaced += brailled_text_caps.charAt(i);
        }
    }

   Serial.println(brailled_text_spaced);

   return brailled_text_spaced;
}

String correct_spacing(String brailled_text_spaced) {
    std::vector<String> text_list_spaced;
    String token = "";
    for (int i = 0; i < brailled_text_spaced.length(); i++) {
        if (brailled_text_spaced[i] == ' ') {
            if (token.length() > 0) {
                text_list_spaced.push_back(token);
                token = "";
            }
        } else {
            token += brailled_text_spaced[i];
        }
    }
    if (token.length() > 0) {
        text_list_spaced.push_back(token);
    }

    String brailled_text = "";
    for (int i = 0; i < text_list_spaced.size(); i++) {
        if (i > 0) {
            brailled_text += " ";
        }
        brailled_text += text_list_spaced[i];
    }

    Serial.println(brailled_text);

    return brailled_text;
}


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
    // String braille_text_1 = F("");
    // String braille_text_2 = F("");
    // String braille_text_3 = F("");
    // String braille_unicode_spaced = "";
    // String braille_unicode = F("");

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
            // if (unicode.find(cell) != unicode.end()) {
            //     braille_unicode += unicode[cell];
            //     // braille_unicode_spaced += String("  ") + unicode[cell] + String("  ");
            // }

            // Build braille text lines
            // braille_text_1 += String(" ") + cell.charAt(0) + String(" ") + cell.charAt(3) + String(" ");
            // braille_text_2 += String(" ") + cell.charAt(1) + String(" ") + cell.charAt(4) + String(" ");
            // braille_text_3 += String(" ") + cell.charAt(2) + String(" ") + cell.charAt(5) + String(" ");

            // Set pins to display braille cell on LEDs
            for (int k = 0; k < n_dots; k++) {
                digitalWrite(first_pin + j * n_dots + k, cell.charAt(k) - '0');
                delay(timer_dot);
            }
            delay(timer_cell);
        }
        delay(timer_display);
    }

    // Printing the braille text
    // Serial.println(brailled_text);
    // Serial.println(braille_text_1);
    // Serial.println(braille_text_2);
    // Serial.println(braille_text_3);
    // Serial.println(braille_unicode_spaced);
    // Serial.println(F(""));
    // Serial.println(braille_unicode);
}
