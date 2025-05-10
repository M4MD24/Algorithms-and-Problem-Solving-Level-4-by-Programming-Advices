#include <iomanip>
#include <iostream>
using namespace std;

struct Date {
    short year;
    short month;
    short day;
};

Date getSystemDate() {
    const time_t TIME = time(
        nullptr
    );
    const tm* TIME_NOW = localtime(
        &TIME
    );
    return {
        static_cast<short>(TIME_NOW->tm_year + 1900),
        static_cast<short>(TIME_NOW->tm_mon + 1),
        static_cast<short>(TIME_NOW->tm_mday)
    };
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
    const Date& DATE
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
            DATE.year,
            DATE.month,
            DATE.day
        )
    ];
}

void printDate(
    const Date& DATE,
    const char& SEPARATOR
) { cout << "Date: " << DATE.day << SEPARATOR << DATE.month << SEPARATOR << DATE.year; }

bool isWeekend(
    const short& DAY_OF_WEEK
) { return DAY_OF_WEEK == 6; }

int main() {
    const Date SYSTEM_DATE{
        getSystemDate()
    };
    constexpr char SEPARATOR = '-';

    printDate(
        SYSTEM_DATE,
        SEPARATOR
    );

    cout << endl << endl;

    const string DAY_OF_WEEK_NAME = dayOfWeekName(
        SYSTEM_DATE
    );
    cout << "Day Name: " << DAY_OF_WEEK_NAME;

    cout << endl << endl;

    cout << "Is it Weekend?" << endl <<
        boolalpha << isWeekend(
            dayOfWeek(
                SYSTEM_DATE.year,
                SYSTEM_DATE.month,
                SYSTEM_DATE.day
            )
        );
}