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

short readVacationDays(
    const string& INPUT_MESSAGE
) {
    short vacationDays;
    do cout << INPUT_MESSAGE << endl;
    while (
        !isNumber(
            vacationDays
        ) || !isPositiveNumber(
            vacationDays
        )
    );
    return vacationDays;
}

void printDate(
    const Date& DATE,
    const char& SEPARATOR
) { cout << "Date: " << DATE.day << SEPARATOR << DATE.month << SEPARATOR << DATE.year; }

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

void nextWeek(
    Date& date
) {
    for (short day = 0; day < 7; ++day)
        nextDay(
            date
        );
}

short compareDates(
    const Date& FIRST_DATE,
    const Date& SECOND_DATE
) {
    if (
        FIRST_DATE.year == SECOND_DATE.year &&
        FIRST_DATE.month == SECOND_DATE.month &&
        FIRST_DATE.day == SECOND_DATE.day
    )
        return 0;
    if (
        FIRST_DATE.year >= SECOND_DATE.year &&
        FIRST_DATE.month >= SECOND_DATE.month &&
        FIRST_DATE.day >= SECOND_DATE.day
    )
        return 1;
    return -1;
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

bool isWeekend(
    const short& DAY_OF_WEEK
) { return DAY_OF_WEEK == 6; }

short vacationDays(
    Date& firstDate,
    const Date& SECOND_DATE
) {
    short counter = 0;
    while (
        compareDates(
            firstDate,
            SECOND_DATE
        ) == -1
    ) {
        counter = static_cast<short>(
            counter +
            isWeekend(
                dayOfWeek(
                    firstDate.year,
                    firstDate.month,
                    firstDate.day
                )
            )
        );
        nextDay(
            firstDate
        );
    }
    return counter;
}

Date dateAfterVacationDays(
    short& vacationDays,
    Date date
) {
    while (vacationDays) {
        if (
            isWeekend(
                dayOfWeek(
                    date.year,
                    date.month,
                    date.day
                )
            )
        )
            vacationDays--;
        nextDay(
            date
        );
    }
    return date;
}

int main() {
    const Date VACATION_DAY{
        readDate()
    };
    constexpr char SEPARATOR = '-';
    short vacationDays = readVacationDays(
        "Enter Vacation Days:"
    );

    cout << "Start ";
    printDate(
        VACATION_DAY,
        SEPARATOR
    );

    cout << endl << endl;

    printDate(
        dateAfterVacationDays(
            vacationDays,
            VACATION_DAY
        ),
        SEPARATOR
    );
}