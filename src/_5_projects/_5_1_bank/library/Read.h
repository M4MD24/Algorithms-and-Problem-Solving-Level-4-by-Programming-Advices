#pragma once

#include <iostream>

#include "CheckValue.h"
#include "Structures.h"

using namespace Structure;

namespace Read {
    inline short readNumber(
        const short& FROM,
        const short& TO
    ) {
        short number;
        do cout << "Enter number [" << FROM << ":" << TO << "]" << endl;
        while (
            !isNumber(
                number
            ) && isPositiveNumber(
                number
            )
        );
        return number;
    }

    inline string readText(
        const string& INPUT_TYPE_NAME
    ) {
        cout << "Enter " << INPUT_TYPE_NAME << ":" << endl;
        string TEXT;
        cin >> TEXT;
        return TEXT;
    }

    inline void readPIN_Code(
        string& PIN_Code
    ) {
        do {
            PIN_Code = readText(
                "PIN Code"
            );
        } while (PIN_Code.length() != 4);
    }

    inline void readFirstName(
        string& firstName
    ) {
        firstName = readText(
            "First Name"
        );
    }

    inline void readSecondName(
        string& secondName
    ) {
        secondName = readText(
            "Second Name"
        );
    }

    inline void readFullName(
        FullName& fullName
    ) {
        readFirstName(
            fullName.firstName
        );
        readSecondName(
            fullName.secondName
        );
    }

    inline void readCountryCode(
        string& countryCode
    ) {
        countryCode = readText(
            "Country Code"
        );
    }

    inline void readContactNumber(
        string& contactNumber
    ) {
        contactNumber = readText(
            "Contact Number"
        );
    }

    inline void readMobileNumber(
        MobileNumber& mobileNumber
    ) {
        readCountryCode(
            mobileNumber.countryCode
        );
        readContactNumber(
            mobileNumber.contactNumber
        );
    }

    inline void readBalance(
        long double& balance
    ) {
        cout << "Enter Balance" << endl;
        cin >> balance;
    }

    inline long double readAmount() {
        long double amount;
        do {
            readBalance(
                amount
            );
        } while (
            !isPositiveNumber(
                amount
            ) && !areYourSure(
                "Are your sure?"
            )
        );
        return amount;
    }

    inline void readUsername(
        string& username
    ) {
        while (
            (
                username = readText(
                    "Username"
                )
            ).length() < 4
        );
    }

    inline void readPassword(
        string& password
    ) {
        while (
            (
                password = readText(
                    "Password"
                )
            ).length() < 8
        );
    }

    inline void readCreateNewClientAccountPermission(
        AdminRole& adminRole
    ) {
        adminRole.createNewClientAccount = areYourSure(
            "Can Create New Client Account?"
        );
    }

    inline void readShowClientAccountListPermission(
        AdminRole& adminRole
    ) {
        adminRole.showClientAccountList = areYourSure(
            "Can Show Client Account List?"
        );
    }

    inline void readUpdateClientAccountPermission(
        AdminRole& adminRole
    ) {
        adminRole.updateClientAccount = areYourSure(
            "Can Update Client Account?"
        );
    }

    inline void readFindClientAccountPermission(
        AdminRole& adminRole
    ) {
        adminRole.findClientAccount = areYourSure(
            "Can Find Client Account?"
        );
    }

    inline void readDeleteClientAccountPermission(
        AdminRole& adminRole
    ) {
        adminRole.deleteClientAccount = areYourSure(
            "Can Delete Client Account?"
        );
    }

    inline void readTransactionsPermission(
        AdminRole& adminRole
    ) {
        adminRole.transactions = areYourSure(
            "Can Transactions?"
        );
    }

    inline void readAdminRole(
        AdminRole& adminRole
    ) {
        readCreateNewClientAccountPermission(
            adminRole
        );

        readShowClientAccountListPermission(
            adminRole
        );

        readUpdateClientAccountPermission(
            adminRole
        );

        readFindClientAccountPermission(
            adminRole
        );

        readDeleteClientAccountPermission(
            adminRole
        );

        readTransactionsPermission(
            adminRole
        );
    }

    inline bool whatDoYouNeedForFile(
        const string& REQUEST
    ) {
        string accepting;
        const string ACCEPT_TEXT = "yes",
                     REJECT_TEXT = "no";
        do {
            cout << "Do you want " << REQUEST << " it? (" << ACCEPT_TEXT << '/' << REJECT_TEXT << ")" << endl;
            cin >> accepting;
        } while (
            accepting != ACCEPT_TEXT &&
            accepting != REJECT_TEXT
        );
        return accepting == ACCEPT_TEXT;
    }
}