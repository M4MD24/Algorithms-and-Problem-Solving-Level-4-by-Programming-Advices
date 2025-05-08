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

short totalDaysFromStartYearToTargetDate(
    const short& YEAR,
    const short& MONTH,
    const short& DAY
) {
    short totalDays = 0;
    for (short month = 1; month < MONTH; ++month)
        totalDays = static_cast<short>(
            totalDays +
            monthDays(
                YEAR,
                month
            )
        );
    return static_cast<short>(totalDays + DAY);
}

int main() {
    const short YEAR = readYear(),
                MONTH = readMonth(),
                DAY = readDay(
                    YEAR,
                    MONTH
                );
    cout << "Total Days from Start Year to Target Date: " << totalDaysFromStartYearToTargetDate(
        YEAR,
        MONTH,
        DAY
    );
}