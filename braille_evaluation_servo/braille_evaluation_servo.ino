#include <ArduinoSTL.h>
#include <vector>
#include <Servo.h>

#include "braille_dictionaries.h"

// global variables
int first_pin = 22; // right-hand side pins of Arduino MEGA, 22 for cell 1

int first_pin_negative = 34; // right-hand side pins of Arduino MEGA, 34 for cell 1

int n_dots = 6; // 6-dot braille
int n_cells = 1; // 1 or 2

int timer_dot = 200; // ms for single dot
int timer_cell = 200 * n_dots ; // ms for single cell of n_dots
int timer_display = 1000 * n_cells; // ms for display of n_cells


const byte servoPins[] = {8, 9, 10, 11, 12, 13}; // {8, 9, 10, 11, 12, 13}

int pos = 0;
byte servoPos[] = {0, 0, 0, 0, 0, 0}; //leave 0
const byte servoAttPos[] = {1, 1, 1, 1, 1, 1}; //probably leave 90
const byte servoMinPos[] = {0, 0, 0, 0, 0, 0};
const byte servoMaxPos[] = {4, 4, 4, 4, 4, 4};
const byte servoInterval[] = {250, 250, 250, 250, 250, 250}; //larger numbers are slower, 250 hardly notice, 10 is quick
int servoIncrement[] = {-1, -1, -1, -1, -1, -1}; //probably leave -1 -1, it starts off "going down" from the attach pos
unsigned long servoPrevMillis[] = {0, 0, 0, 0, 0, 0}; //leave 0 0 

const byte numberOfServos = sizeof(servoPins)/sizeof(servoPins[0]);
Servo servo[numberOfServos];


// function declarations

String process_text_to_braille(String text);

String space_out_symbols_punctuation(String text);
String space_out_alphanumeric(String text_sym_spaced);

String convert_numeric_character(String brailled_text_num_word);
String convert_symbols_punctuation(String brailled_text_num);
String convert_capital(String brailled_text_sym);
String convert_lowercase_grade1(String brailled_text_caps);

String correct_spacing(String brailled_text_spaced);

void display_braille(String brailled_text);

String to_lowercase(String str);
std::vector<String> split_string(const String& str);

// main code

void setup() {

    Serial.begin(115200);
    while (!Serial) {
        ; // Wait for the serial port to connect. Needed for native USB port only
    }

    for (byte i = 0; i < numberOfServos; i++)
    {

        Serial.print("Attaching servo "); Serial.print(i + 1);
        Serial.print(" to pin "); Serial.print(servoPins[i]);
        Serial.println("");
        Serial.println("");
        servoPos[i] = servoAttPos[i];
        servo[i].write(servoPos[i]);
        servo[i].attach(servoPins[i]);

    }


}

void loop() {

    String brailled_text = "";
    String text = "";

    // Check if the serial port is connected
    if (Serial) {
        // Check if data is available on the serial port
        if (Serial.available() > 0) {
            // Read the input text from the serial monitor
            text = Serial.readStringUntil('\n');
            text.trim(); // Remove any leading or trailing whitespace

            // Process
            brailled_text = process_text_to_braille(text);

            // Output

            // keep looping the input until a new serial input is received
            while ((Serial.available() == 0)) {
                Serial.println("Input Text:");
                Serial.println(text);
                Serial.println("");
                Serial.println("Braille Conversion:");
                Serial.println("");
                display_braille(brailled_text);
            }

            // // or outside the while loop to run once and return to default text if no further serial buffer
            // Serial.println("Input Text:");
            // Serial.println(text);
            // Serial.println("");
            // Serial.println("Braille Conversion:");
            // Serial.println("");
            // display_braille(brailled_text);

        } else {

        // Default input text when there is no serial input at all
        text = F("The quick brown fox jumps over a lazy dog.");

        // Process
        brailled_text = process_text_to_braille(text);

        // Output
        Serial.println("Input Text:");
        Serial.println(text);
        Serial.println("");
        Serial.println("Braille Conversion:");
        Serial.println("");
        display_braille(brailled_text);

        }
    }

}

// functions

String process_text_to_braille(String text) {
    String brailled_text = "";

    // Space out symbols and punctuation
    String text_sym_spaced = space_out_symbols_punctuation(text);

    // Space out alphanumeric characters
    String text_alphanumeric_spaced = space_out_alphanumeric(text_sym_spaced);

    // Convert numeric characters
    String brailled_text_num = convert_numeric_character(text_alphanumeric_spaced);

    // Convert symbols and punctuation
    String brailled_text_sym = convert_symbols_punctuation(brailled_text_num);

    // Convert capital letters
    String brailled_text_caps = convert_capital(brailled_text_sym);

    // Convert lowercase letters
    String brailled_text_spaced = convert_lowercase_grade1(brailled_text_caps);

    // Correct spacing
    brailled_text = correct_spacing(brailled_text_spaced);

    return brailled_text;
}

String space_out_symbols_punctuation(String text) {

    // Serial.println(text);

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

    // Serial.println(text_sym_spaced);

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

    // Serial.println(text_alphanumeric_spaced);

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

    // Serial.println(brailled_text_num);

    return brailled_text_num;
}

String convert_symbols_punctuation(String brailled_text_num) {

    std::vector<String> text_list_num = split_string(brailled_text_num);

    String brailled_text_sym = "";
    for (int i = 0; i < text_list_num.size(); i++) {
        if (punctuation.find(text_list_num[i]) != punctuation.end()) {
            brailled_text_sym += punctuation[text_list_num[i]];
        } else {
            brailled_text_sym += text_list_num[i] + " ";
        }
    }

    // Serial.println(brailled_text_sym);

    return brailled_text_sym;
}

String convert_capital(String brailled_text_sym) {
    // Treat capitals next, add 000001 before and convert to lower, will do shorthand conversion later
    std::vector<String> text_list_sym = split_string(brailled_text_sym);

    // Treat capitals next, add 000001 before and convert to lower, will do shorthand conversion later
    String brailled_text_caps_word = "";
    for (auto& word : text_list_sym) {
        if (word.length() > 1 && isUpperCase(word[0]) && isUpperCase(word[1]) && word.length() != 1) {
            brailled_text_caps_word += " 000001 000001 " + to_lowercase(word);
        } else {
            brailled_text_caps_word += " " + word + " ";
        }
    }

    std::vector<String> text_list_caps_word = split_string(brailled_text_caps_word);

    // Character by character, better option is doing list item by list item first then char by char
    String brailled_text_caps = "";
    for (int i = 0; i < brailled_text_caps_word.length(); i++) {
        if (isUpperCase(brailled_text_caps_word[i])) {
            brailled_text_caps += " 000001 " + String((char)tolower(brailled_text_caps_word[i]));
        } else {
            brailled_text_caps += brailled_text_caps_word[i];
        }
    }

    // Serial.println(brailled_text_caps);

    return brailled_text_caps;
}

String convert_lowercase_grade1(String brailled_text_caps) {

    String brailled_text_spaced = "";
    for (int i = 0; i < brailled_text_caps.length(); i++) {
        if (isalpha(brailled_text_caps.charAt(i))) {
            brailled_text_spaced += alphanumeric[String(brailled_text_caps.charAt(i))];
        } else if (isdigit(brailled_text_caps[i]) || brailled_text_caps[i] == ' ') {
            brailled_text_spaced += brailled_text_caps.charAt(i);
        } else {
          brailled_text_spaced += " ";
        }
    }

    // Serial.println(brailled_text_spaced);

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

    // Serial.println(brailled_text);

    return brailled_text;
}


void display_braille(String brailled_text) {
    // Splitting the brailled_text into a list
    String brailled_list[200]; // Assuming a maximum of 200 elements
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
    String braille_text_1 = F("");
    String braille_text_2 = F("");
    String braille_text_3 = F("");
    // String braille_unicode_spaced = "";

    String braille_unicode = F("");


    // Printing the braille text
    // Serial.println(brailled_text);
    // Serial.println(braille_unicode_spaced);
    // Serial.println(F(""));


    String cell = "";

    // Display brailled list
    for (int i = 0; i <= floor(brailled_list_length / n_cells); i++) {
        for (int j = 0; j < n_cells; j++) {

            if ((i * n_cells + j) >= brailled_list_length) {
              cell = "000000"; // remainder at the final n_cells loop
            } else {
              cell = brailled_list[i * n_cells + j];
            }

            // // Get unicode character
            // if (unicode.find(cell) != unicode.end()) {
            //     braille_unicode += unicode[cell];
            //     // braille_unicode_spaced += String("  ") + unicode[cell] + String("  ");
            // }


            // // Build braille text lines
            // braille_text_1 += String(" ") + cell.charAt(0) + String(" ") + cell.charAt(3) + String(" ");
            // braille_text_2 += String(" ") + cell.charAt(1) + String(" ") + cell.charAt(4) + String(" ");
            // braille_text_3 += String(" ") + cell.charAt(2) + String(" ") + cell.charAt(5) + String(" ");

            // // Serial.println(braille_unicode);
            // Serial.println(braille_text_1);
            // Serial.println(braille_text_2);
            // Serial.println(braille_text_3);
            // Serial.println("");
            // Serial.println("");

            // Set pins to display braille cell on Servos
            for (byte i = 0; i < numberOfServos; i++) {
                if (cell.charAt(i) == '1') {
                    servo[i].write(servoMaxPos[i]); //move the servo
                    // delay(timer_dot);
                } else {
                    servo[i].write(servoMinPos[i]);
                }
            }

            delay(timer_cell);
        }

        delay(timer_display);

        // for all cells
        for (int j = 0; j < n_cells; j++) {
            // reset all dots
            for (byte i = 0; i < numberOfServos; i++)
            {
                servoPos[i] = servoAttPos[i];
                servo[i].write(servoPos[i]);
            }
        }

    }

}


// Helper functions

// Function to convert to lowercase
String to_lowercase(String str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

// Function to split a string by space and return a vector of strings
std::vector<String> split_string(const String& str) {
    std::vector<String> result;
    int start = 0;
    int end = str.indexOf(' ');

    while (end != -1) {
        result.push_back(str.substring(start, end));
        start = end + 1;
        end = str.indexOf(' ', start);
    }

    if (start < str.length()) {
        result.push_back(str.substring(start));
    }

    return result;
}