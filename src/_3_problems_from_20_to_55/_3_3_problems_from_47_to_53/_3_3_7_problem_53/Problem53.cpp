#include <iomanip>
#include <iostream>
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

short daysUntilEndOfYear(
    const Date& DATE
) {
    const short REMAINDER = isLeapYear(
                                DATE.year
                            )
                                ? 366
                                : 365;
    short daysBeforeTargetDate = DATE.day;
    for (short month = 1; month < DATE.month; ++month)
        daysBeforeTargetDate = static_cast<short>(
            daysBeforeTargetDate +
            monthDays(
                DATE.year,
                month
            )
        );

    return REMAINDER - daysBeforeTargetDate;
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

    cout << "Days Until The End of Year: " << daysUntilEndOfYear(
        SYSTEM_DATE
    ) << " Day(s)";
}