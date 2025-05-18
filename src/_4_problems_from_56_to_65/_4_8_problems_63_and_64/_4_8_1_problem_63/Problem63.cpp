#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
#include "../Trim.h"
using namespace std;
using namespace Trim;

struct Date {
    short year;
    short month;
    short day;
};

bool isLeapYear(
    const short& YEAR
) {
    return YEAR % 4 == 0 &&
    (
        YEAR % 100 != 0 ||
        YEAR % 400 == 0
    );
}

bool isNumber(
    short& number
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

bool isPositiveNumber(
    const short& NUMBER
) { return NUMBER > 0; }

short readYear() {
    short year;
    do cout << "Enter Year:" << endl;
    while (
        !isNumber(
            year
        )
    );
    return year;
}

short readMonth() {
    short month;
    do cout << "Enter Month:" << endl;
    while (
        !isNumber(
            month
        )
    );
    return month;
}

short readDay() {
    short day;
    do cout << "Enter Day:" << endl;
    while (
        !isNumber(
            day
        )
    );
    return day;
}

Date readDate() {
    const short YEAR = readYear(),
                MONTH = readMonth(),
                DAY = readDay();
    return {
        YEAR,
        MONTH,
        DAY
    };
}

short monthDays(
    const short& YEAR,
    const short& MONTH
) {
    if (MONTH == 2)
        return isLeapYear(
                   YEAR
               )
                   ? 29
                   : 28;

    switch (MONTH) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    default:
        return 30;
    }
}

bool dateIsValid(
    const Date& DATE
) {
    return isPositiveNumber(
            DATE.year
        ) &&
        isPositiveNumber(
            DATE.month
        ) &&
        DATE.month <= 12 &&
        isPositiveNumber(
            DATE.day &&
            DATE.day <= monthDays(
                DATE.year,
                DATE.month
            )
        );
}

string readDateText() {
    cout << "Enter Date Text: " << endl;
    string dateText;
    getline(
        cin,
        dateText
    );
    trim(
        dateText
    );
    return dateText;
}

void splitText(
    string text,
    vector<short>& parts,
    const string& DELIMITER
) {
    size_t position;
    while (
        (
            position = text.find(
                DELIMITER
            )
        ) != string::npos
    ) {
        parts.push_back(
            static_cast<short>(
                stoi(
                    text.substr(
                        0,
                        position
                    )
                )
            )
        );
        text.erase(
            0,
            position + DELIMITER.length()
        );
    }
    parts.push_back(
        static_cast<short>(
            stoi(
                text
            )
        )
    );
}

vector<short> convertDateTextToDateParts(
    const string& DATE_TEXT,
    const string& DELIMITER
) {
    vector<short> dateParts;
    splitText(
        DATE_TEXT,
        dateParts,
        DELIMITER
    );
    return dateParts;
}

Date convertDatePartsToDateStructure(
    const vector<short>& DATE_PARTS
) {
    return {
        DATE_PARTS[0],
        DATE_PARTS[1],
        DATE_PARTS[2],
    };
}

void printDate(
    const Date& DATE,
    const string& SEPARATOR
) { cout << "Date: " << DATE.year << SEPARATOR << DATE.month << SEPARATOR << DATE.day; }

int main() {
    const string SEPARATOR = "-";
    const string DATE_TEXT = readDateText();
    const vector<short> DATE_PARTS = convertDateTextToDateParts(
        DATE_TEXT,
        SEPARATOR
    );
    const Date DATE = {
        convertDatePartsToDateStructure(
            DATE_PARTS
        )
    };

    cout << "Date is" << (
        dateIsValid(
            DATE
        )
            ? ""
            : "n't"
    ) << " Valid" << endl;

    printDate(
        DATE,
        SEPARATOR
    );
}