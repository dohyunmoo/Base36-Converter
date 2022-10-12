#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <vector>

char* dec_to_36(unsigned int decimal);
unsigned int to_dec(char* input, unsigned int type);

int main(int argc, char* argv[]) {

    if (argc == 1) {
        std::cout << "no input was detected" << std::endl;
        return 1;
    }

    std::vector<char*> result;

    for (size_t i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-b") { // binary to Base36
            result.push_back(dec_to_36(to_dec((argv[i + 1]), 2)));
        } else if (std::string(argv[i]) == "-o") { // octal to Base 36
            result.push_back(dec_to_36(to_dec((argv[i + 1]), 8)));
        } else if (std::string(argv[i]) == "-d") { // decimal to Base 36
            result.push_back(dec_to_36((std::atoi(argv[i + 1]))));
        } else if (std::string(argv[i]) == "-h") { // hexadecimal to Base 36
            result.push_back(dec_to_36(to_dec((argv[i + 1]), 16)));
        }
    }

    // std::stringstream strValue;
    // strValue << argv[1];
    // unsigned int input;
    // strValue >> input;

    for (size_t i = 0; i < result.size(); i++) {
        std::cout << result[i] << std::endl;
    }

    return 0;
}

char* dec_to_36(unsigned int decimal) {

    unsigned int exp = 0;
    
    while ((decimal % (unsigned int)std::pow(36, exp)) != decimal) {
        exp++;
    }

    char* result;
    result = new char(exp + 1);

    for (int i = exp - 1; i >= 0; --i) {

        unsigned int temp = decimal - (decimal % (unsigned int)std::pow(36, i));
        temp /= (unsigned int)std::pow(36, i);

        if (temp < 10) {
            result[exp - i - 1] = char(temp + 48); // ASCII 0 to 9
        } else {
            result[exp - i - 1] = char(temp + 87); // ASCII a to z
        }
        decimal %= (unsigned int)std::pow(36, i);
    }

    result[exp] = '\0';
    
    return result;
}

unsigned int to_dec(char* input, unsigned int type) {
    unsigned int result = 0;

    for (int i = strlen(input) - 1; i >= 0; i--) {

        if (type < 16) { // binary, octal
            result += ((int)input[i] - 48) * std::pow(type, strlen(input) - i - 1);
        } else { // hexadecimal
            if ((int)tolower(input[i]) >= 97 ) { // check if letter is a to f
                result += ((int)tolower(input[i]) - 87) * std::pow(type, strlen(input) - i - 1);
            } else {
                result += ((int)input[i] - 48) * std::pow(type, strlen(input) - i - 1);
            }
        }
    }

    return result;
}
