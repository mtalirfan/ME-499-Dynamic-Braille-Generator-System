#include <ArduinoSTL.h>
#include <map>

// std::map<String, String> unicode = { // 6 digit code to unicode characters, from https://unicode.org/charts/nameslist/c_2800.html
//     {"000000", "⠀"}, {"100000", "⠁"}, {"010000", "⠂"}, {"110000", "⠃"},
//     {"001000", "⠄"}, {"101000", "⠅"}, {"011000", "⠆"}, {"111000", "⠇"},
//     {"000100", "⠈"}, {"100100", "⠉"}, {"010100", "⠊"}, {"110100", "⠋"},
//     {"001100", "⠌"}, {"101100", "⠍"}, {"011100", "⠎"}, {"111100", "⠏"},
//     {"000010", "⠐"}, {"100010", "⠑"}, {"010010", "⠒"}, {"110010", "⠓"},
//     {"001010", "⠔"}, {"101010", "⠕"}, {"011010", "⠖"}, {"111010", "⠗"},
//     {"000110", "⠘"}, {"100110", "⠙"}, {"010110", "⠚"}, {"110110", "⠛"},
//     {"001110", "⠜"}, {"101110", "⠝"}, {"011110", "⠞"}, {"111110", "⠟"},
//     {"000001", "⠠"}, {"100001", "⠡"}, {"010001", "⠢"}, {"110001", "⠣"},
//     {"001001", "⠤"}, {"101001", "⠥"}, {"011001", "⠦"}, {"111001", "⠧"},
//     {"000101", "⠨"}, {"100101", "⠩"}, {"010101", "⠪"}, {"110101", "⠫"},
//     {"001101", "⠬"}, {"101101", "⠭"}, {"011101", "⠮"}, {"111101", "⠯"},
//     {"000011", "⠰"}, {"100011", "⠱"}, {"010011", "⠲"}, {"110011", "⠳"},
//     {"001011", "⠴"}, {"101011", "⠵"}, {"011011", "⠶"}, {"111011", "⠷"},
//     {"000111", "⠸"}, {"100111", "⠹"}, {"010111", "⠺"}, {"110111", "⠻"},
//     {"001111", "⠼"}, {"101111", "⠽"}, {"011111", "⠾"}, {"111111", "⠿"}
// };

std::map<String, String> alphanumeric = {
    {"1", "100000 "}, {"2", "110000 "}, {"3", "100100 "}, {"4", "100110 "}, {"5", "100010 "},
    {"6", "110100 "}, {"7", "110110 "}, {"8", "110010 "}, {"9", "010100 "}, {"0", "010110 "},

    {"a", "100000 "}, {"b", "110000 "}, {"c", "100100 "}, {"d", "100110 "}, {"e", "100010 "},
    {"f", "110100 "}, {"g", "110110 "}, {"h", "110010 "}, {"i", "010100 "}, {"j", "010110 "},

    {"k", "101000 "}, {"l", "111000 "}, {"m", "101100 "}, {"n", "101110 "}, {"o", "101010 "},
    {"p", "111100 "}, {"q", "111110 "}, {"r", "111010 "}, {"s", "011100 "}, {"t", "011110 "},

    {"u", "101001 "}, {"v", "111001 "}, {"x", "101101 "}, {"y", "101111 "}, {"z", "101011 "},
                                                                            {"w", "010111 "},

    // {"A", "000001 100000 "}, {"B", "000001 110000 "}, {"C", "000001 100100 "}, {"D", "000001 100110 "}, {"E", "000001 100010 "},
    // {"F", "000001 110100 "}, {"G", "000001 110110 "}, {"H", "000001 110010 "}, {"I", "000001 010100 "}, {"J", "000001 010110 "},
    // {"K", "000001 101000 "}, {"L", "000001 111000 "}, {"M", "000001 101100 "}, {"N", "000001 101110 "}, {"O", "000001 101010 "},
    // {"P", "000001 111100 "}, {"Q", "000001 111110 "}, {"R", "000001 111010 "}, {"S", "000001 011100 "}, {"T", "000001 011110 "},
    // {"U", "000001 101001 "}, {"V", "000001 111001 "}, {"X", "000001 101101 "}, {"Y", "000001 101111 "}, {"Z", "000001 101011 "},
    //                                                                                                     {"W", "000001 010111 "}

    // // NON-UEB ALPHABET FOR OTHER LANGUAGES
    // // SPANISH
    // {"á", " 111011 "},  // 000110 001100 100000 in UEB
    // {"é", " 011101 "},  // 000110 001100 100010
    // {"í", " 001100 "},  // 000110 001100 010100
    // {"ó", " 001101 "},  // 000110 001100 101010
    // {"ú", " 011111 "},  // 000110 001100 101001
    // {"ü", " 110011 "},  // 000110 010010 101001
    // {"ñ", " 110111 "},  // 000110 110111 101110
    // // FRENCH
    // {"ç", " 111101 "},
    // // {"é", " 111111 "}, // also in Spanish
    // {"à", " 111011 "},
    // {"è", " 011101 "},
    // {"î", " 100101 "},
    // {"ô", " 100111 "},
    // {"ë", " 110101 "},
    // {"ê", " 110001 "}
};

std::map<String, String> punctuation = {
    // " ": " 000000 ",
    {"‎", " 000000 "},  // convert all whitespaces to an empty unicode character, to retain braille space 000000 of the original text
    {".", " 010011 "},
    // {"…", " 010011 010011 010011 "},
    {",", " 010000 "},
    {"?", " 011001 "},
    // {"¿", " 010001 "},  // 000110 000011 011010 in UEB
    {"“", " 011001 "},
    {"”", " 001011 "},
    {":", " 010010 "},
    // {"∷", " 010010 010010 "},
    {";", " 011000 "},
    {"!", " 011010 "},
    // {"¡", " 000110 000011 011010 "},  // 011010 in Spanish Braille
    // {"_", " 000001 001001 "}, // long dash
    {"_", " 000101 001001 "},  // underscore preferred
    {"π", " 000101 111100 "},
    {"\"", " 000001 011011 "},
    // {"‘", " 000001 011001 "},
    // {"’", " 000001 001011 "},
    {"'", " 001000 "},  // single quotation
    // {"’", " 001000 "}, // apostrophe
    // {"′", " 011011 "},  // feet, single prime
    // {"″", " 011011 011011 "},  // inches, double prime
    // {"«", " 000111 011001 "},
    // {"»", " 000111 001011 "},
    {"/", " 000111 001100 "},  // forward slash preferred, contains indicator
    // {"/", " 001100 "},  // divide sign
    {"\\", " 000111 100001 "},
    {"{", " 000111 110001 "},
    {"}", " 000111 001110 "},
    // {"∠", " 000111 010101 "},
    {"#", " 000111 100111 "},
    // {"•", " 000111 010011 "},
    {"[", " 000101 110001 "},
    {"]", " 000101 001110 "},
    {"%", " 000101 001011 "},
    {"—", " 000001 001001 "},
    // {"〃", " 000010 010000 "},
    {"(", " 000010 110001 "},
    {")", " 000010 001110 "},
    {"+", " 000010 011010 "},
    {"-", " 001001 "},  // using simple hyphen for minus and dashes
    // {"–", " 000010 001001 "},
    {"×", " 000010 011001 "},  // multiplication
    {"÷", " 000010 001100 "},
    {"=", " 000010 011011 "},
    // {"≠", " 000010 011011 000100 100011 "},
    {"*", " 000010 001010 "},
    // {"√", " 000010 100101 "},
    {"@", " 000100 100000 "},
    // {"¢", " 000100 100100 "},
    // {"€", " 000100 100010 "},
    // {"₣", " 000100 110100 "},
    // {"£", " 000100 111000 "},
    // {"₦", " 000100 101110 "},
    {"$", " 000100 011100 "},
    // {"¥", " 000100 101111 "},
    {"&", " 000100 111101 "},
    {"<", " 000100 110001 "},
    {"^", " 000100 010001 "},  // caret
    {"~", " 000100 001010 "},  // tilde
    {">", " 000100 001110 "},
    // {"✓", " 000100 100101 "},
    // {"†", " 000100 000001 100111 "},
    // {"‡", " 000100 000001 110111 "},
    // {"©", " 000110 100100 "},
    // {"°", " 000110 010110 "},
    // {"¶", " 000110 111100 "},
    // {"®", " 000110 111010 "},
    // {"§", " 000110 011100 "},
    // {"™", " 000110 011110 "},
    // {"♀", " 000110 101101 "},
    // {"♂", " 000110 101111 "},
    // {"´", " 000110 001100 "},
    {"`", " 000110 100001 "},
    // {"¨", " 000110 010010 "},  // umlaut
};

// std::map<String, String> wordsigns = { // all: alphabetic, strong and lower
//     // ALPHABETIC WORDSIGNS
//     // no sign for a
//     {"but", "b"},
//     {"can", "c"},
//     {"do", "d"},
//     {"every", "e"},
//     {"from", "f"},
//     {"go", "g"},
//     {"have", "h"},
//     // no sign for i
//     {"just", "j"},
//     {"knowledge", "k"},
//     {"like", "l"},
//     {"more", "m"},
//     {"not", "n"},
//     // no sign for o
//     {"people", "p"},
//     {"quite", "q"},
//     {"rather", "r"},
//     {"so", "s"},
//     {"that", "t"},
//     {"us", "u"},
//     {"very", "v"},
//     {"will", "w"},
//     {"it", "x"},
//     {"you", "y"},
//     {"as", "z"},
//     // STRONG WORDSIGNS top bottom left right dots
//     {"child", " 100001 "},
//     {"shall", " 100101 "},
//     {"this", " 100111 "},
//     {"which", " 100011 "},
//     {"out", " 110011 "},
//     {"still", " 001100 "},
//     // LOWER WORDSIGNS not dots 1 or 4
//     {"be", " 011000 "},
//     {"enough", " 010001 "},
//     {"were", " 011011 "},
//     {"his", " 011001 "},
//     {"in", " 001010 "},
//     {"was", " 001011 "}
// };

// std::map<String, String> shortforms = {
//     {"about", "ab"},
//     {"above", "abv"},
//     {"according", "ac"},
//     {"across", "acr"},
//     // {"after", "af"}, // keeping larger word above smaller substring gives it preference, since it appears first in matches list
//     {"afternoon", "afn"},
//     {"afterward", "afw"},
//     {"after", "af"},  // keeping larger word above smaller substring gives it preference, since it appears first in matches list
//     // {"again", "ag"}, // keeping larger word above smaller substring gives it preference, since it appears first in matches list
//     {"against", "agst"},
//     {"again", "ag"},  // keeping larger word above smaller substring gives it preference, since it appears first in matches list
//     {"almost", "alm"},
//     {"already", "alr"},
//     {"also", "al"},
//     {"although", "alth"},
//     {"altogether", "alt"},
//     {"always", "alw"},
//     {"because", "bec"},
//     {"before", "bef"},
//     {"behind", "beh"},
//     {"below", "bel"},
//     {"beneath", "ben"},
//     {"beside", "bes"},
//     {"between", "bet"},
//     {"beyond", "bey"},
//     {"blind", "bl"},
//     {"braille", "brl"},
//     {"children", "chn"},
//     {"conceive", "concv"},
//     {"conceiving", "concvg"},
//     {"could", "cd"},
//     {"deceive", "dcv"},
//     {"deceiving", "dcvg"},
//     {"declare", "dcl"},
//     {"declaring", "dclg"},
//     {"either", "ei"},
//     {"first", "fst"},
//     {"friend", "fr"},
//     {"good", "gd"},
//     {"great", "grt"},
//     {"herself", "herf"},
//     // {"him", "hm"}, // keeping larger word above smaller substring gives it preference, since it appears first in matches list
//     {"himself", "hmf"},
//     {"him", "hm"},  // keeping larger word above smaller substring gives it preference, since it appears first in matches list
//     {"immediate", "imm"},
//     // {"its", "xs"}, // keeping larger word above smaller substring gives it preference, since it appears first in matches list
//     {"itself", "xf"},
//     {"its", "xs"},  // keeping larger word above smaller substring gives it preference, since it appears first in matches list
//     {"letter", "lr"},
//     {"little", "ll"},
//     {"much", "mch"},
//     {"must", "mst"},
//     {"myself", "myf"},
//     {"necessary", "nec"},
//     {"neither", "nei"},
//     {"oneself", "onef"},
//     {"ourselves", "ourvs"},
//     {"paid", "pd"},
//     {"perceive", "percv"},
//     {"perceiving", "percvg"},
//     {"perhaps", "perh"},
//     {"quick", "qk"},
//     {"receive", "rcv"},
//     {"receiving", "rcvg"},
//     {"rejoice", "rjc"},
//     {"rejoicing", "rjcg"},
//     {"said", "sd"},
//     {"should", "shd"},
//     {"such", "sch"},
//     {"themselves", "themvs"},
//     {"thyself", "thyf"},
//     {"today", "td"},
//     {"together", "tgr"},
//     {"tomorrow", "tm"},
//     {"tonight", "tn"},
//     {"would", "wd"},
//     // {"your", "yr"}, // keeping larger word above smaller substring gives it preference, since it appears first in matches list
//     {"yourself", "yrf"},
//     {"yourselves", "yrvs"},
//     {"your", "yr"}  // keeping larger word above smaller substring gives it preference, since it appears first in matches list
// };

// std::map<String, String> contractions = { // smaller substrings should be unique, if they appear in the larger words, put them in lower order
//     // STRONG CONTRACTIONS (Part and Whole Word)
//     {"and", " 111101 "},
//     {"for", " 111111 "},
//     {"of", " 111011 "},
//     // {"the", " 011101 "}, // keeping larger word above smaller substring gives it preference, since it appears first in matches list
//     {"with", " 011111 "},
//     // INITIAL-LETTER CONTRACTIONS
//     {"day", " 000010 100110 "},
//     {"ever", " 000010 100010 "},
//     {"father", " 000010 110100 "},
//     {"here", " 000010 110010 "},
//     {"know", " 000010 101000 "},
//     {"lord", " 000010 111000 "},
//     {"mother", " 000010 101100 "},
//     {"name", " 000010 101110 "},
//     {"one", " 000010 101010 "},
//     {"part", " 000010 111100 "},
//     {"question", " 000010 111110 "},
//     {"right", " 000010 111010 "},
//     {"some", " 000010 011100 "},
//     {"time", " 000010 011110 "},
//     {"under", " 000010 101001 "},
//     {"work", " 000010 010111 "},
//     {"young", " 000010 101111 "},
//     {"there", " 000010 011101 "},
//     {"character", " 000010 100001 "},
//     {"through", " 000010 100111 "},
//     {"where", " 000010 100011 "},
//     {"ought", " 000010 110011 "},
//     {"upon", " 000110 101001 "},
//     {"word", " 000110 010111 "},
//     {"these", " 000110 011101 "},
//     {"those", " 000110 100111 "},
//     {"whose", " 000110 100011 "},
//     {"cannot", " 000111 100100 "},
//     {"had", " 000111 110010 "},
//     {"many", " 000111 101100 "},
//     {"spirit", " 000111 011100 "},
//     {"world", " 000111 010111 "},
//     {"their", " 000111 011101 "},
//     {"the", " 011101 "}  // keeping larger word above smaller substring gives it preference, since it appears first in matches list
// };

// std::map<String, String> groupsigns_final = {
//     {"ing", " 001101 "},  // Not used at beginning, so in groupsigns final dictionary
//     // FINAL-LETTER GROUPSIGNS
//     {"ound", " 000101 100110 "},
//     {"ance", " 000101 100010 "},
//     {"sion", " 000101 101110 "},
//     {"less", " 000101 011100 "},
//     {"ount", " 000101 011110 "},
//     {"ence", " 000011 100010 "},
//     {"ong", " 000011 110110 "},
//     {"ful", " 000011 111000 "},
//     {"tion", " 000011 101110 "},
//     {"ness", " 000011 011100 "},
//     {"ment", " 000011 011110 "},
//     {"ity", " 000011 101111 "}
// };

// std::map<String, String> groupsigns = {
//     // STRONG GROUPSIGNS
//     {"ch", " 100001 "},
//     {"sh", " 100101 "},
//     {"th", " 100111 "},
//     {"wh", " 100011 "},
//     {"ou", " 110011 "},
//     {"st", " 001100 "},
//     {"gh", " 110001 "},
//     {"ed", " 110101 "},
//     {"er", " 110111 "},
//     {"ow", " 010101 "},
//     {"ar", " 001110 "},
//     // {"ing", " 001101 "}, # Not used at beginning, so in groupsigns final dictionary
//     // LOWER GROUPSIGNS
//     {"ea", " 010000 "},
//     {"bb", " 011000 "},
//     {"cc", " 010010 "},
//     {"ff", " 011010 "},
//     {"gg", " 011011 "},
//     {"be", " 011000 "},
//     {"con", " 010010 "},
//     {"dis", " 010011 "},
//     {"en", " 010001 "},
//     {"in", " 001010 "}
// };

// std::map<String, String> contractions_retired = { // not used in UEB, so not used in this project
//     {"ble", " 001111 "},
//     {"ation", " 000001 101110 "},
//     {"ally", " 000001 101111 "},
//     {"dd", " 010011 "},
//     {"com", " 001001 "},
//     {"to", " 011010 "},
//     {"into", " 001010 011010 "},
//     {"by", " 001011 "},
//     {"o'clock", "o'c"}
// };

// std::map<String, String> indicator = {
//     {"capital", " 000001 "},
//     {"letter", " 001111 "},
//     {"shape", " 110101 "},
//     {"arrow", " 110011 "},
//     {"subscript", " 010001 "},
//     {"superscript", " 001010 "}
// };

