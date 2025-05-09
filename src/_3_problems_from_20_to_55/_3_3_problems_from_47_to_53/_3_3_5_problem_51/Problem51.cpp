#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

struct Date {
    short year;
    short month;
    short day;
};

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

short dayOfWeek(
    short year,
    short month,
    const short& DAY
) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }

    const short YEAR_PART = static_cast<short>(year % 100);
    const short CENTURY = static_cast<short>(year / 100);
    const short ZELLER_RESULT = static_cast<short>(
        (
            DAY + 13 *
            (month + 1) / 5 +
            YEAR_PART + YEAR_PART / 4 +
            CENTURY / 4 + 5 *
            CENTURY
        ) %
        7
    );

    return ZELLER_RESULT;
}

short daysUntilEndOfWeek(
    const Date& DATE
) {
    constexpr short REMAINDER_DAYS = 6;
    const short DAYS_UNTIL_END_OF_WEEK = static_cast<short>(
        REMAINDER_DAYS -
        dayOfWeek(
            DATE.year,
            DATE.month,
            DATE.day
        )
    );
    return DAYS_UNTIL_END_OF_WEEK != 0
               ? DAYS_UNTIL_END_OF_WEEK
               : REMAINDER_DAYS;
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

    cout << "Days Until The End of Week: " << daysUntilEndOfWeek(
        SYSTEM_DATE
    ) << " Day(s)";
}