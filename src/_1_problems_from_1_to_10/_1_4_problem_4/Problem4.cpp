#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

struct YearTimeUnits {
    short months;
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

YearTimeUnits getRegularYear() {
    YearTimeUnits yearTimeUnits{};
    yearTimeUnits.months = 12;
    yearTimeUnits.weeks = 365.0 / 7;
    yearTimeUnits.days = 365;
    yearTimeUnits.hours = static_cast<short>(yearTimeUnits.days * 24);
    yearTimeUnits.minutes = yearTimeUnits.hours * 60;
    yearTimeUnits.seconds = yearTimeUnits.minutes * 60;
    yearTimeUnits.milliseconds = yearTimeUnits.seconds * 1000;
    return yearTimeUnits;
}

YearTimeUnits getLeapYear() {
    YearTimeUnits yearTimeUnits{};
    yearTimeUnits.months = 12;
    yearTimeUnits.weeks = 366.0 / 7;
    yearTimeUnits.days = 366;
    yearTimeUnits.hours = static_cast<short>(yearTimeUnits.days * 24);
    yearTimeUnits.minutes = yearTimeUnits.hours * 60;
    yearTimeUnits.seconds = yearTimeUnits.minutes * 60L;
    yearTimeUnits.milliseconds = yearTimeUnits.seconds * 1000L;
    return yearTimeUnits;
}

void printYearTimeUnits(
    const YearTimeUnits& YEAR_TIME_UNITS
) {
    constexpr short FIELD_WIDTH = 13;
    cout << setw(
        FIELD_WIDTH
    ) << "Months: " << YEAR_TIME_UNITS.months << endl;
    cout << setw(
        FIELD_WIDTH
    ) << "Weeks: " << YEAR_TIME_UNITS.weeks << endl;
    cout << setw(
        FIELD_WIDTH
    ) << "Days: " << YEAR_TIME_UNITS.days << endl;
    cout << setw(
        FIELD_WIDTH
    ) << "Hours: " << YEAR_TIME_UNITS.hours << endl;
    cout << setw(
        FIELD_WIDTH
    ) << "Minutes: " << YEAR_TIME_UNITS.minutes << endl;
    cout << setw(
        FIELD_WIDTH
    ) << "Seconds: " << YEAR_TIME_UNITS.seconds << endl;
    cout << setw(
        FIELD_WIDTH
    ) << "MillSeconds: " << YEAR_TIME_UNITS.milliseconds;
}

void showYearTimeBreakdown(
    const bool& IS_LEAP_YEAR
) {
    cout << "Year Time Units:" << endl;
    if (IS_LEAP_YEAR)
        printYearTimeUnits(
            getLeapYear()
        );
    else
        printYearTimeUnits(
            getRegularYear()
        );
}

int main() {
    const short YEAR = readYear();
    showYearTimeBreakdown(
        isLeapYear(
            YEAR
        )
    );
}