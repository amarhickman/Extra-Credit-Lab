#include <iostream>
#include <iomanip> // For formatting a double-precision number
#include <string>  // For string handling
#include <cctype>  // For character checks

using namespace std;

// Prototype for the extractNumeric function
double extractNumeric(const string& str);

int main() {
    string input;

    cout << "Enter a string (or 'END' to quit):" << endl;
    while (true) {
        cout << "> ";
        cin >> input;

        // Check for termination 
        if (input == "END") {
            break;
        }

        // Extract value
        double number = extractNumeric(input);

        // Display output
        if (number != -999999.99) {
            cout << "The input is: " << fixed << setprecision(4) << number << endl;
        } else {
            cout << "The input is invalid." << endl;
        }
    }

    return 0;
}

// Function to extract and validate a value from the input 
double extractNumeric(const string& str) {
    bool hasSign = false;
    bool hasDecimal = false;
    bool validNumber = true;
    size_t i = 0;

    // Check for an optional sign at the beginning
    if (str[i] == '+' || str[i] == '-') {
        hasSign = true;
        i++;
    }

    // Iterate through the string to validate the format
    for (; i < str.size(); i++) {
        if (isdigit(str[i])) {
            continue; // Valid digit
        } else if (str[i] == '.') {
            if (hasDecimal) {
                validNumber = false;   
                break;
            }
            hasDecimal = true;
        } else {
            validNumber = false; // Invalid character
            break;
        }
    }

    // No trailing sign or dot
    if (str.empty() || str.back() == '.' || str.back() == '+' || str.back() == '-') {
        validNumber = false;
    }

    // Convert to double if valid
    if (validNumber) {
        try {
            double result = 0.0;
            size_t decimalPos = str.find('.');
            bool isNegative = (str[0] == '-');

            // Process integer 
            for (size_t j = (hasSign ? 1 : 0); j < (decimalPos != string::npos ? decimalPos : str.size()); j++) {
                result = result * 10 + (str[j] - '0');
            }

            // Process decimal 
            if (decimalPos != string::npos) {
                double fraction = 0.0;
                double divisor = 10.0;
                for (size_t j = decimalPos + 1; j < str.size(); j++) {
                    fraction += (str[j] - '0') / divisor;
                    divisor *= 10;
                }
                result += fraction;
            }

            return isNegative ? -result : result;
        } catch (...) {
            return -999999.99; // Return error code if any exception occurs
        }
    }

    return -999999.99; // Return error code for invalid input
}
 