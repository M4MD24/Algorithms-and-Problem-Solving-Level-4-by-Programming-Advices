#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

struct Date {
    short year;
    short month;
    short day;
};

enum DateCompare {
    Before = -1,
    Equal = 0,
    After = 1
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

void nextDay(
    Date& date
) {
    if (
        ++date.day > monthDays(
            date.year,
            date.month
        )
    ) {
        date.day = 1;
        if (++date.month > 12) {
            date.month = 1;
            ++date.year;
        }
    }
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

short daysDifferenceInDates(
    Date firstDate,
    Date secondDate,
    const bool& INCLUDE_END_DAY = false
) {
    short daysDifference = 0;
    if (
        compareDates(
            firstDate,
            secondDate
        ) == 1
    ) {
        const Date& TEMPORARY_DATE = firstDate;
        firstDate = secondDate;
        secondDate = TEMPORARY_DATE;
    }

    while (
        !compareDates(
            firstDate,
            secondDate
        ) == 0
    ) {
        daysDifference += 1;
        nextDay(
            firstDate
        );
    }

    return INCLUDE_END_DAY
               ? ++daysDifference
               : daysDifference;
}

int main() {
    const Date FIRST_DATE{
                   readDate()
               }, SECOND_DATE{
                   readDate()
               };

    cout << "Days difference in dates: " << daysDifferenceInDates(
        FIRST_DATE,
        SECOND_DATE
    ) << " day(s)" << endl;

    cout << "Days difference in dates (Including End Day): " << daysDifferenceInDates(
        FIRST_DATE,
        SECOND_DATE,
        true
    ) << " day(s)";
}