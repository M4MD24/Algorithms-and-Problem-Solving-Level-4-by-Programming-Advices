#include <iostream>
#include <limits>
#include <string>
using namespace std;

string numberBelow1000(
    const int& NUMBER
) {
    const string UNITS[] = {
        "",
        "One",
        "Two",
        "Three",
        "Four",
        "Five",
        "Six",
        "Seven",
        "Eight",
        "Nine",
        "Ten",
        "Eleven",
        "Twelve",
        "Thirteen",
        "Fourteen",
        "Fifteen",
        "Sixteen",
        "Seventeen",
        "Eighteen",
        "Nineteen"
    };

    const string TENS[] = {
        "",
        "",
        "Twenty",
        "Thirty",
        "Forty",
        "Fifty",
        "Sixty",
        "Seventy",
        "Eighty",
        "Ninety"
    };

    if (NUMBER == 0)
        return "";
    if (NUMBER < 20)
        return UNITS[NUMBER];
    if (NUMBER < 100)
        return TENS[NUMBER / 10] + (
            NUMBER % 10
                ? " " + UNITS[NUMBER % 10]
                : ""
        );
    return UNITS[NUMBER / 100] + " Hundred" + (
        NUMBER % 100
            ? " " + numberBelow1000(
                NUMBER % 100
            )
            : ""
    );
}

bool isPositiveNumber(
    const int& NUMBER
) { return NUMBER > 0; }

string numberToText(
    int number
) {
    if (number == 0)
        return "Zero";

    if (
        !isPositiveNumber(
            number
        )
    )
        return "Negative " + numberToText(
            -number
        );

    string numberText;
    if (number >= 1000000000) {
        numberText += numberBelow1000(
            number / 1000000000
        ) + " Billion ";
        number %= 1000000000;
    }
    if (number >= 1000000) {
        numberText += numberBelow1000(
            number / 1000000
        ) + " Million ";
        number %= 1000000;
    }
    if (number >= 1000) {
        numberText += numberBelow1000(
            number / 1000
        ) + " Thousand ";
        number %= 1000;
    }
    if (number > 0) {
        numberText += numberBelow1000(
            number
        );
    }

    while (
        !numberText.empty() &&
        numberText.back() == ' '
    )
        numberText.pop_back();

    return numberText;
}

bool isNumber(
    int& number
) {
    cin >> number;
    if (
        const bool VALID = !cin.fail();
        !VALID
    ) {
        cin.clear();
        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );
        return false;
    }
    return true;
}

int readNumber() {
    int number;
    do cout << "Enter Number:" << endl;
    while (
        !isNumber(
            number
        )
    );
    return number;
}

int main() {
    const int NUMBER = readNumber();
    cout << "Number Text is:\n" << numberToText(
        NUMBER
    );
}