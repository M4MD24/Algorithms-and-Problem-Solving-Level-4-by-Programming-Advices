#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

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

int main() {
    const Date DATE{
        readDate()
    };

    cout << "Date is" << (
        dateIsValid(
            DATE
        )
            ? ""
            : "n't"
    ) << " Valid";
}