#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
#include "Trim.h"
using namespace std;
using namespace Trim;

struct Date {
    short year;
    short month;
    short day;
};

bool isLeapYear(
    const short &YEAR
) {
    return YEAR % 4 == 0 &&
    (
        YEAR % 100 != 0 ||
        YEAR % 400 == 0
    );
}

bool isNumber(
    short &number
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
    const short &NUMBER
) { return NUMBER > 0; }

short readYear() {
    short year;
    do cout << "Enter Year:" << endl;
    while (
        !isNumber(
            year
        ) || !isPositiveNumber(
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
        ) || !isPositiveNumber(
            month
        ) ||
        month > 12
    );
    return month;
}

short monthDays(
    const short &YEAR,
    const short &MONTH
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

short readDay(
    const short &YEAR,
    const short &MONTH
) {
    const short MONTH_DAYS = monthDays(
        YEAR,
        MONTH
    );
    short day;
    do cout << "Enter Day:" << endl;
    while (
        !isNumber(
            day
        ) || !isPositiveNumber(
            day
        ) ||
        day > MONTH_DAYS
    );
    return day;
}

Date readDate() {
    const short YEAR = readYear(),
                MONTH = readMonth(),
                DAY = readDay(
                    YEAR,
                    MONTH
                );
    return {
        YEAR,
        MONTH,
        DAY
    };
}

void splitText(
    string text,
    vector<short> &parts,
    const string &DELIMITER
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

vector<short> convertDateTextToDateParts(
    const string &DATE_TEXT,
    const string &DELIMITER
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
    const vector<short> &DATE_PARTS
) {
    return {
        DATE_PARTS[0],
        DATE_PARTS[1],
        DATE_PARTS[2],
    };
}

void printDateStructure(
    const Date &DATE,
    const string &SEPARATOR
) { cout << "Date Structure: " << DATE.year << SEPARATOR << DATE.month << SEPARATOR << DATE.day << endl; }

string convertDateStructureToDateText(
    const Date &DATE,
    const string &SEPARATOR
) {
    return to_string(
            DATE.year
        ) + SEPARATOR +
        to_string(
            DATE.month
        ) + SEPARATOR +
        to_string(
            DATE.day
        );
}

void format_yyyy(
    const short &YEAR,
    string &result,
    size_t &position
) {
    while (
        (
            position = result.find(
                "yyyy"
            )
        ) != string::npos
    )
        result.replace(
            position,
            4,
            to_string(
                YEAR
            )
        );
}

void format_yy(
    const short &YEAR,
    string &result,
    size_t &position
) {
    while (
        (
            position = result.find(
                "yy"
            )
        ) != string::npos
    )
        result.replace(
            position,
            2,
            to_string(
                YEAR % 100
            )
            .insert(
                0,
                2 - to_string(
                    YEAR % 100
                ).length(),
                '0'
            )
        );
}

void format_mm(
    const short &MONTH,
    string &result,
    size_t &position
) {
    while (
        (
            position = result.find(
                "mm"
            )
        ) != string::npos
    )
        result.replace(
            position,
            2,
            to_string(
                MONTH
            )
            .insert(
                0,
                2 - to_string(
                    MONTH
                ).length(),
                '0'
            )
        );
}

void format_m(
    const short &MONTH,
    string &result,
    size_t &position
) {
    while (
        (
            position = result.find(
                'm'
            )
        ) != string::npos
    )
        result.replace(
            position,
            1,
            to_string(
                MONTH
            )
        );
}

void format_dd(
    const short &DAY,
    string &result,
    size_t &position
) {
    while (
        (
            position = result.find(
                "dd"
            )
        ) != string::npos
    )
        result.replace(
            position,
            2,
            to_string(
                DAY
            )
            .insert(
                0,
                2 - to_string(
                    DAY
                ).length(),
                '0'
            )
        );
}

void format_d(
    const short &DAY,
    string &result,
    size_t &position
) {
    while (
        (
            position = result.find(
                'd'
            )
        ) != string::npos
    )
        result.replace(
            position,
            1,
            to_string(
                DAY
            )
        );
}

void formatYear(
    const short &DATE,
    string &result,
    size_t &position
) {
    format_yyyy(
        DATE,
        result,
        position
    );

    format_yy(
        DATE,
        result,
        position
    );
}

void formatMonth(
    const short &MONTH,
    string &result,
    size_t &position
) {
    format_mm(
        MONTH,
        result,
        position
    );

    format_m(
        MONTH,
        result,
        position
    );
}

void formatDay(
    const short &DAY,
    string &result,
    size_t &position
) {
    format_dd(
        DAY,
        result,
        position
    );

    format_d(
        DAY,
        result,
        position
    );
}

string formatDate(
    const Date &DATE,
    const string &FORMAT
) {
    string result = FORMAT;

    size_t position;

    formatYear(
        DATE.year,
        result,
        position
    );

    formatMonth(
        DATE.month,
        result,
        position
    );

    formatDay(
        DATE.day,
        result,
        position
    );

    return result;
}

void printDateText(
    const string &DATE_TEXT
) { cout << "Date: " << DATE_TEXT << endl; }

int main() {
    const Date DATE {
        readDate()
    };

    printDateText(
        formatDate(
            DATE,
            "yyyy-mm-dd"
        )
    );

    printDateText(
        formatDate(
            DATE,
            "yy|m|d"
        )
    );

    printDateText(
        formatDate(
            DATE,
            "yy-mm/dd"
        )
    );
}