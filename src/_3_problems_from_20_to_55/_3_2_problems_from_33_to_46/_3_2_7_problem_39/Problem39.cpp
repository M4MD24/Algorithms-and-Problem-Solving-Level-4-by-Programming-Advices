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
    const short YEAR = readYear();
    const short MONTH = readMonth();
    const short DAY = readDay(
        YEAR,
        MONTH
    );
    return {
        YEAR,
        MONTH,
        DAY
    };
}

void previousDay(
    Date &date
) {
    if (--date.day == 0) {
        if (--date.month == 0) {
            date.month = 12;
            --date.year;
        }
        date.day = monthDays(
            date.year,
            date.month
        );
    }
}

void previousDays(
    short dayCount,
    Date &date
) {
    while (dayCount--)
        previousDay(
            date
        );
}

void previousYear(
    Date &date
) {
    if (
        isLeapYear(
            date.year--
        ) && (
            date.month > 2 ||
            (
                date.month == 2 &&
                date.day == 29
            )
        )
    )
        previousDay(
            date
        );
}

void printDate(
    const Date &DATE,
    const char &SEPARATOR
) { cout << "Date: " << DATE.day << SEPARATOR << DATE.month << SEPARATOR << DATE.year; }

int main() {
    Date date {
        readDate()
    };
    constexpr char SEPARATOR = '-';

    previousYear(
        date
    );

    printDate(
        date,
        SEPARATOR
    );
}