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
        month < 1 ||
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

string dayName(
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
        DAY - 1
    ];
}

string monthName(
    const short& MONTH
) {
    static const string MONTHS[] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };
    return MONTHS[
        MONTH - 1
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

void showMonthCalendar(
    const short& YEAR,
    const short& MONTH
) {
    short dayOfWeekIndex = dayOfWeek(
        YEAR,
        MONTH,
        1
    );
    const short MONTH_DAYS = monthDays(
        YEAR,
        MONTH
    );

    printf(
        "_______________________________%9s_______________________________\n",
        monthName(
            MONTH
        ).c_str()
    );

    for (short day = 1; day <= 7; ++day) {
        printf(
            "%10s",
            dayName(
                day
            ).c_str()
        );
    }

    cout << endl;

    for (short index = 0; index < dayOfWeekIndex; index++)
        printf(
            "%10c",
            ' '
        );

    for (short day = 1; day <= MONTH_DAYS; day++) {
        printf(
            "%10d",
            day
        );
        if (++dayOfWeekIndex == 7) {
            dayOfWeekIndex = 0;
            printf(
                "\n"
            );
        }
    }

    printf(
        "\n_______________________________________________________________________"
    );
}

int main() {
    const short YEAR = readYear(),
                MONTH = readMonth();
    showMonthCalendar(
        YEAR,
        MONTH
    );
}