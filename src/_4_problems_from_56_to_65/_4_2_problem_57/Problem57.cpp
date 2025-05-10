#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

struct Date {
    string title;
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

string readTitle() {
    cout << "Enter Title:" << endl;
    string title;
    getline(
        cin,
        title
    );
    return title;
}

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

Date readDate(
    const string& INPUT_TYPE
) {
    cout << INPUT_TYPE << endl;

    const string TITLE = readTitle();
    const short YEAR = readYear();
    const short MONTH = readMonth();
    const short DAY = readDay(
        YEAR,
        MONTH
    );
    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );

    return {
        TITLE,
        YEAR,
        MONTH,
        DAY
    };
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

int main() {
    const Date FIRST_DATE{
                   readDate(
                       "First Date"
                   )
               }, SECOND_DATE{
                   readDate(
                       "Second Date"
                   )
               };

    cout << "Compare Result: " << compareDates(
        FIRST_DATE,
        SECOND_DATE
    );
}