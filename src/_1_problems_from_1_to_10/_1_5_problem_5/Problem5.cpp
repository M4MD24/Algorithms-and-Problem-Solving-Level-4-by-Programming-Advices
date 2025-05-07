#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

struct MonthTimeUnits {
    float weeks;
    short days;
    short hours;
    int minutes;
    int seconds;
    long long milliseconds;
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

void printMonthTimeUnits(
    const MonthTimeUnits& MONTH_TIME_UNITS
) {
    constexpr short FIELD_WIDTH = 13;
    cout << setw(
        FIELD_WIDTH
    ) << "Weeks: " << MONTH_TIME_UNITS.weeks << endl;
    cout << setw(
        FIELD_WIDTH
    ) << "Days: " << MONTH_TIME_UNITS.days << endl;
    cout << setw(
        FIELD_WIDTH
    ) << "Hours: " << MONTH_TIME_UNITS.hours << endl;
    cout << setw(
        FIELD_WIDTH
    ) << "Minutes: " << MONTH_TIME_UNITS.minutes << endl;
    cout << setw(
        FIELD_WIDTH
    ) << "Seconds: " << MONTH_TIME_UNITS.seconds << endl;
    cout << setw(
        FIELD_WIDTH
    ) << "MillSeconds: " << MONTH_TIME_UNITS.milliseconds;
}

MonthTimeUnits getMonthTimeUnits(
    const short& YEAR,
    const short& MONTH
) {
    MonthTimeUnits monthTimeUnits{};
    const short MONTH_DAYS = monthDays(
        YEAR,
        MONTH
    );
    monthTimeUnits.weeks = static_cast<float>(
        MONTH_DAYS / 7.0
    );
    monthTimeUnits.days = MONTH_DAYS;
    monthTimeUnits.hours = static_cast<short>(MONTH_DAYS * 24);
    monthTimeUnits.minutes = monthTimeUnits.hours * 60;
    monthTimeUnits.seconds = monthTimeUnits.minutes * 60;
    monthTimeUnits.milliseconds = static_cast<long long>(monthTimeUnits.seconds) * 1000L;
    return monthTimeUnits;
}

void showMonthTimeBreakdown(
    const short& YEAR,
    const short& MONTH
) {
    cout << "Month Time Units:" << endl;
    printMonthTimeUnits(
        getMonthTimeUnits(
            YEAR,
            MONTH
        )
    );
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
        month < 1 ||
        month > 12
    );
    return month;
}

int main() {
    const short YEAR = readYear();
    const short MONTH = readMonth();
    showMonthTimeBreakdown(
        YEAR,
        MONTH
    );
}