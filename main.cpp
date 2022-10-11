#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

char* dec_to_36(unsigned int decimal);

int main(int argc, char* argv[]) {

    if (argc == 1) {
        std::cout << "no input was detected" << std::endl;
        return 1;
    }

    std::stringstream strValue;
    strValue << argv[1];
    unsigned int input;
    strValue >> input;

    std::cout << dec_to_36(input) << std::endl;

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
            result[exp - i - 1] = char(temp + 55); // ASCII A to Z
        }
        decimal %= (unsigned int)std::pow(36, i);
    }

    result[exp] = '\0';
    
    return result;
}