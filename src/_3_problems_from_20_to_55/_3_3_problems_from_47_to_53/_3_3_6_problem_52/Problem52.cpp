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

short readDay(
    const short& YEAR,
    const short& MONTH
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

Date getSystemDate() {
    const time_t TIME = time(
        nullptr
    );
    const tm* TIME_NOW = localtime(
        &TIME
    );
    return {
        static_cast<short>(TIME_NOW->tm_year + 1900),
        static_cast<short>(TIME_NOW->tm_mon + 1),
        static_cast<short>(TIME_NOW->tm_mday)
    };
}

void printDate(
    const Date& DATE,
    const char& SEPARATOR
) { cout << "Date: " << DATE.day << SEPARATOR << DATE.month << SEPARATOR << DATE.year; }

short daysUntilEndOfMonth(
    const Date& DATE
) {
    const short MONTH_DAYS = monthDays(
        DATE.year,
        DATE.month
    );
    return static_cast<short>(MONTH_DAYS - DATE.day);
}

int main() {
    const Date SYSTEM_DATE{
        getSystemDate()
    };
    constexpr char SEPARATOR = '-';

    printDate(
        SYSTEM_DATE,
        SEPARATOR
    );

    cout << endl << endl;

    cout << "Days Until The End of Month: " << daysUntilEndOfMonth(
        SYSTEM_DATE
    ) << " Day(s)";
}