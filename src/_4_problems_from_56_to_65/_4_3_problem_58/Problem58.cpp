#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

struct Date {
    short year;
    short month;
    short day;
};

struct Period {
    Date startDate;
    Date endDate;
};

enum DateCompare {
    Before = -1,
    Equal = 0,
    After = 1
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

Date readDate(
    const string &INPUT_TYPE
) {
    cout << INPUT_TYPE << endl;
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

Period readPeriod(
    const string &INPUT_TYPE
) {
    cout << "# " << INPUT_TYPE << endl;

    const Date FIRST_DATE = readDate(
                   "Start Date"
               ),
               SECOND_DATE = readDate(
                   "End Date"
               );

    return {
        FIRST_DATE,
        SECOND_DATE
    };
}

bool areDatesEqual(
    const Date &FIRST_DATE,
    const Date &SECOND_DATE
) {
    return FIRST_DATE.year == SECOND_DATE.year &&
        FIRST_DATE.month == SECOND_DATE.month &&
        FIRST_DATE.day == SECOND_DATE.day;
}

bool isAfter(
    const Date &FIRST_DATE,
    const Date &SECOND_DATE
) {
    if (FIRST_DATE.year != SECOND_DATE.year)
        return FIRST_DATE.year > SECOND_DATE.year;
    if (FIRST_DATE.month != SECOND_DATE.month)
        return FIRST_DATE.month > SECOND_DATE.month;
    return FIRST_DATE.day > SECOND_DATE.day;
}

DateCompare compareDates(
    const Date &FIRST_DATE,
    const Date &SECOND_DATE
) {
    if (
        areDatesEqual(
            FIRST_DATE,
            SECOND_DATE
        )
    )
        return Equal;
    if (
        isAfter(
            FIRST_DATE,
            SECOND_DATE
        )
    )
        return After;
    return Before;
}

bool areOverlap(
    const Period &FIRST_DATE,
    const Period &SECOND_DATE
) {
    return !(
        compareDates(
            SECOND_DATE.endDate,
            FIRST_DATE.startDate
        ) == Before ||
        compareDates(
            SECOND_DATE.startDate,
            FIRST_DATE.endDate
        ) == After
    );
}

int main() {
    const Period FIRST_PERIOD {
                     readPeriod(
                         "First Date"
                     )
                 }, SECOND_PERIOD {
                     readPeriod(
                         "Second Date"
                     )
                 };

    cout << "Periods are" << (
        areOverlap(
            FIRST_PERIOD,
            SECOND_PERIOD
        )
            ? ""
            : "n't"
    ) << " Overlap";
}