#include <iostream>
using namespace std;

class PredictiveParser {
public:
    bool parse(const string& input) {
        inputString = input + "$"; // Append $ to the end of the input string
        inputIndex = 0;

        // Start parsing with the start symbol
        if (parseStartSymbol()) {
            cout << "String accepted!\n";
            return true;
        } else {
            cout << "String rejected!\n";
            return false;
        }
    }

private:
    string inputString;
    int inputIndex;

    bool parseStartSymbol() {
        if (inputString[inputIndex] == 'a') {
            inputIndex++;
            return parseNonTerminalB();
        } else {
            return false; // Invalid start symbol
        }
    }

    bool parseNonTerminalB() {
        if (inputString[inputIndex] == 'c') {
            inputIndex++;
            return true; // Production B -> c
        } else if (inputString[inputIndex] == '$') {
            return true; // Production B -> ε (epsilon)
        } else {
            return false; // Invalid production
        }
    }
};

int main() {
    PredictiveParser parser;

    // Replace 'ac' with your input string
    parser.parse("ac");

    return 0;
}
