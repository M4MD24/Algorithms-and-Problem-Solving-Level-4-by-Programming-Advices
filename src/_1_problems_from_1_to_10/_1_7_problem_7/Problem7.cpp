#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

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
    const short& YEAR,
    const short& MONTH,
    const short& DAY
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
            YEAR,
            MONTH,
            DAY
        )
    ];
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

void showDayName(
    const short& YEAR,
    const short& MONTH,
    const short& DAY
) {
    cout << "Day Name: " << dayOfWeekName(
        YEAR,
        MONTH,
        DAY
    );
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

void printDate(
    const short& YEAR,
    const short& MONTH,
    const short& DAY,
    const char& SEPARATOR
) { cout << "Date: " << DAY << SEPARATOR << MONTH << SEPARATOR << YEAR << endl; }

int main() {
    const short YEAR = readYear(),
                MONTH = readMonth(),
                DAY = readDay(
                    YEAR,
                    MONTH
                );
    constexpr char SEPARATOR = '-';

    printDate(
        YEAR,
        MONTH,
        DAY,
        SEPARATOR
    );

    showDayName(
        YEAR,
        MONTH,
        DAY
    );
}