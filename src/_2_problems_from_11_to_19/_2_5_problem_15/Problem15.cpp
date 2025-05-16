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

short readNumber(
    const string &INPUT_TYPE
) {
    short number;
    do cout << "Enter " << INPUT_TYPE << ':' << endl;
    while (
        !isNumber(
            number
        ) || !isPositiveNumber(
            number
        )
    );
    return number;
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

Date readDate() {
    const short YEAR = readNumber(
        "Year"
    );
    const short MONTH = readNumber(
        "Month"
    );
    const short DAY = readNumber(
        "Day"
    );
    return {
        YEAR,
        MONTH,
        DAY
    };
}

int main() {
    const Date DATE = {
        readDate()
    };

    cout << "Is Last Month in Year?" << endl;
    cout << boolalpha << (
        DATE.month == 12
    ) << endl;

    cout << "Is Last Day in Month?" << endl;
    cout << boolalpha << (
        DATE.day == monthDays(
            DATE.year,
            DATE.month
        )
    );
}