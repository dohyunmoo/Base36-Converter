#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <vector>

char* dec_to_36(int decimal);
int to_dec(char* input, unsigned int type);

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

    for (size_t i = 0; i < result.size(); i++) {
        std::cout << result[i] << std::endl;
        delete[] result[i];
        result[i] = NULL;
    }

    return 0;
}

char* dec_to_36(int decimal) {

    bool is_neg = false;
    unsigned int exp = 0;

    if (decimal < 0) {
        decimal *= -1;
        is_neg = true;
    }
    
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

    if (is_neg) {
        char* total_result = new char(exp + 2);
        for (size_t i = 0; i < sizeof(total_result)/sizeof(char); i++) {
            if (i == 0) {
                total_result[i] = '-';
            } else {
                total_result[i] = result[i - 1];
            }
        }
        return total_result;
    }
    return result;
}

int to_dec(char* input, unsigned int type) {
    int result = 0;
    unsigned int is_neg = input[0] == '-' ? 1 : 0;

    std::vector<char> real_input;

    for (size_t i = 0; i < strlen(input) - is_neg; i++) {
        real_input.push_back(input[i + is_neg]);
    }

    for (int i = real_input.size() - 1; i >= 0; i--) {

        if (type < 16) { // binary, octal
            result += ((int)real_input[i] - 48) * std::pow(type, real_input.size() - i - 1);
        } else { // hexadecimal
            if ((int)tolower(real_input[i]) >= 97 ) { // check if letter is a to f
                result += ((int)tolower(real_input[i]) - 87) * std::pow(type,  real_input.size() - i - 1);
            } else {
                result += ((int)real_input[i] - 48) * std::pow(type,  real_input.size() - i - 1);
            }
        }
    }

    result = is_neg == 1 ? result * -1 : result;

    return result;
}
