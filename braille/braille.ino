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

String convert_numeric_word(String text_alphanumeric_spaced);
String convert_numeric_character(String brailled_text_num_word);
String convert_symbols_punctuation(String brailled_text_num);
String convert_capital(String brailled_text_sym);

void display_braille(String brailled_text);

bool isAlpha(String str);
bool isDigit(String str);
bool hasDigit(String str);

void setup() {

    Serial.begin(115200);

    for (int pin = first_pin; pin < (first_pin + n_dots * n_cells); pin++) {
        pinMode(pin, OUTPUT);
    }

    String text = F("\"Hello World!\" 12345");

    Serial.println(text);

    // Process
    String text_sym_spaced = space_out_symbols_punctuation(text);
    String text_alphanumeric_spaced = space_out_alphanumeric(text_sym_spaced);

}

void loop() {

    // String brailled_text = F("110010 100010 111000 111000 101010 000000 000001 000111 010111 110010 100010 111000 110010 100010 111000 111000 111000 101010 000000 000001 000111 010111 110010 100010 111000 110010 100010 111000 111000 111000 101010 000000 000001 000111 010111 110010 100010 111000 110010 100010 111000 111000 111000 101010 000000 000001 000111 010111 110010 100010 111000 110010 100010 111000");
    // display_braille(brailled_text);

}

// functions

String space_out_symbols_punctuation(String text) {
    String textSymSpaced = "";
    for (int i = 0; i < text.length(); i++) {
        String ch = String(text.charAt(i));
        if (punctuation.find(ch) != punctuation.end()) {
            textSymSpaced += " " + ch + " ";
        } else if (ch == " ") {
            textSymSpaced += " ‎ ";
        } else {
            textSymSpaced += ch;
        }
    }

    // Opening and Closing Quotations do not display in Serial Monitor
    
    // // count all double quotations to replace for opening and closing
    // int quotationCount = 0;
    // for (int i = 0; i < textSymSpaced.length(); i++) {
    //     if (textSymSpaced[i] == '"') {
    //         quotationCount++;
    //     }
    // }

    // // Replace nth substrings of "foo" to be replaced
    // for (int n = quotationCount; n >= 2; n -= 2) {
    //     int nthOccur = 0;
    //     for (int i = 0; i < textSymSpaced.length(); i++) {
    //         if (textSymSpaced[i] == '"') {
    //             nthOccur++;
    //             if (nthOccur == n) {
    //                 textSymSpaced[i] = '”';
    //             } else if (nthOccur == n - 1) {
    //                 textSymSpaced[i] = '"';
    //             }
    //         }
    //     }
    // }

    // for (int i = 0; i < textSymSpaced.length(); i++) {
    //     if (textSymSpaced[i] == '"') {
    //         textSymSpaced[i] = '“';
    //     }
    // }


    Serial.println(textSymSpaced);

    return textSymSpaced;
}

String space_out_alphanumeric(String text_sym_spaced) {
    String result = "";
    for (int i = 0; i < text_sym_spaced.length(); i++) {
        if (i < (text_sym_spaced.length() - 1)) {
            if ((isDigit(text_sym_spaced.charAt(i)) && isAlpha(text_sym_spaced.charAt(i + 1))) ||
                (isAlpha(text_sym_spaced.charAt(i)) && isDigit(text_sym_spaced.charAt(i + 1)))) {
                result += String(text_sym_spaced.charAt(i)) + " ";
            } else {
                result += String(text_sym_spaced.charAt(i));
            }
        } else {
            result += String(text_sym_spaced.charAt(i));
        }
    }

    Serial.println(result);

    return result;
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
    String braille_unicode = F("");

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
    Serial.println(brailled_text);
    // Serial.println(braille_text_1);
    // Serial.println(braille_text_2);
    // Serial.println(braille_text_3);
    // Serial.println(braille_unicode_spaced);
    Serial.println(F(""));
    Serial.println(braille_unicode);
}


bool isAlpha(String str) {
    if (str.length() != 1) return false;
    char c = str.charAt(0);
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool isDigit(String str) {
    if (str.length() != 1) return false;
    char c = str.charAt(0);
    return c >= '0' && c <= '9';
}

bool hasDigit(String str) {
    for (int i = 0; i < str.length(); i++) {
        if (isDigit(str.charAt(i))) {
            return true;
        }
    }
    return false;
}
