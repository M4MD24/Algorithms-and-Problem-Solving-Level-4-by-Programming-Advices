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

string dayOfWeekName(
    const Date& DATE
) {
    static const string DAYS[] = {
        "Saturday",
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday"
    };
    return DAYS[
        dayOfWeek(
            DATE.year,
            DATE.month,
            DATE.day
        )
    ];
}

void printDate(
    const Date& DATE,
    const char& SEPARATOR
) { cout << "Date: " << DATE.day << SEPARATOR << DATE.month << SEPARATOR << DATE.year; }

bool isWeekend(
    const short& DAY_OF_WEEK
) { return DAY_OF_WEEK == 6; }

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

    const string DAY_OF_WEEK_NAME = dayOfWeekName(
        SYSTEM_DATE
    );
    cout << "Day Name: " << DAY_OF_WEEK_NAME;

    cout << endl << endl;

    cout << "Is it End of Week?" << endl <<
        boolalpha << isWeekend(
            dayOfWeek(
                SYSTEM_DATE.year,
                SYSTEM_DATE.month,
                SYSTEM_DATE.day
            )
        );
}