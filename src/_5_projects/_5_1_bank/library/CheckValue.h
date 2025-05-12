#pragma once

#include <limits>

#include "Options.h"

using namespace std;
using namespace Options;

namespace Read {
    inline bool isNumber(
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
    inline bool isNumber(
        long double& number
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

    inline bool isPositiveNumber(
        const short& NUMBER
    ) { return NUMBER > 0; }

    inline bool isPositiveNumber(
        const long double& NUMBER
    ) { return NUMBER > 0; }

    inline bool areYourSure(
        const string& INPUT_MESSAGE
    ) {
        string accepting;
        const string ACCEPT_TEXT = "yes",
                     REJECT_TEXT = "no";
        do {
            cout << INPUT_MESSAGE << " (yes/no)" << endl;
            cin >> accepting;
        } while (
            accepting != ACCEPT_TEXT &&
            accepting != REJECT_TEXT
        );
        return accepting == ACCEPT_TEXT;
    }

    inline string checkFileRequest(
    const FileRequest& REQUEST
) {
        if (REQUEST == Update)
            return "Update";
        return "Delete";
    }
}