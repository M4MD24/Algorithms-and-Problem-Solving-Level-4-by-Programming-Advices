#pragma once

#include <iostream>
#include <iomanip>

#include "Structures.h"

using namespace Structure;
using namespace Constants;

namespace Display {
    inline void displayAdminMenu(
        const AdminRole& ROLES
    ) {
        cout << "Admin Menu:" << endl;

        cout << (
                ROLES.createNewClientAccount
                    ? ""
                    : "\033[31m"
            )
            << "[1] Create New Client Account" << (
                ROLES.createNewClientAccount
                    ? ""
                    : "\033[0m"
            ) << endl;

        cout << (
                ROLES.showClientAccountList
                    ? ""
                    : "\033[31m"
            )
            << "[2] Show Client Account List" << (
                ROLES.showClientAccountList
                    ? ""
                    : "\033[0m"
            ) << endl;

        cout << (
                ROLES.updateClientAccount
                    ? ""
                    : "\033[31m"
            )
            << "[3] Update Client Account" << (
                ROLES.updateClientAccount
                    ? ""
                    : "\033[0m"
            ) << endl;

        cout << (
                ROLES.deleteClientAccount
                    ? ""
                    : "\033[31m"
            )
            << "[4] Delete Client Account" << (
                ROLES.deleteClientAccount
                    ? ""
                    : "\033[0m"
            ) << endl;

        cout << (
                ROLES.findClientAccount
                    ? ""
                    : "\033[31m"
            )
            << "[5] Find Client Account" << (
                ROLES.findClientAccount
                    ? ""
                    : "\033[0m"
            ) << endl;

        cout << (
                ROLES.transactions
                    ? ""
                    : "\033[31m"
            )
            << "[6] Transactions" << (
                ROLES.transactions
                    ? ""
                    : "\033[0m"
            ) << endl;

        cout << "[7] Logout" << endl;
    }

    inline void displayOwnerMenu() {
        cout << "Owner Menu:" << endl
            << "[1] Create New Admin Account" << endl
            << "[2] Show Admin Account List" << endl
            << "[3] Update Admin Account" << endl
            << "[4] Delete Admin Account" << endl
            << "[5] Find Admin Account" << endl
            << "[6] Logout" << endl;
    }

    inline void displayTransactionsMenu() {
        cout << "Transactions Menu:" << endl
            << "[1] Deposit" << endl
            << "[2] Withdraw" << endl
            << "[3] Total Balances" << endl
            << "[4] Back to Admin Menu" << endl;
    }

    inline void displayAccountTypeLoginMenu() {
        cout << "Account Type Login Menu:" << endl
            << "[1] Owner Account" << endl
            << "[2] Admin Account" << endl
            << "[3] Exit Program" << endl;
    }

    inline void printClientHeader(
        const string& TABLE_LINE
    ) {
        cout << TABLE_LINE << endl;
        cout << "| " << setw(
            20
        ) << "Identifier Number";
        cout << " | " << setw(
            8
        ) << "PIN Code";
        cout << " | " << setw(
            30
        ) << "Full Name";
        cout << " | " << setw(
            25
        ) << "Mobile Number";
        cout << " | " << setw(
            20
        ) << "Balance" << " |";
        cout << endl << TABLE_LINE << endl;
    }

    inline void printBody(
        const ClientAccount& CLIENT_ACCOUNT,
        const string& TABLE_LINE
    ) {
        cout << "| " << setw(
            20
        ) << CLIENT_ACCOUNT.identifierNumber;
        cout << " | " << setw(
            8
        ) << CLIENT_ACCOUNT.PIN_Code;
        cout << " | " << setw(
            30
        ) << CLIENT_ACCOUNT.fullName.firstName + " " + CLIENT_ACCOUNT.fullName.secondName;
        cout << " | " << setw(
            25
        ) << CLIENT_ACCOUNT.mobileNumber.countryCode + CLIENT_ACCOUNT.mobileNumber.contactNumber;
        cout << " | " << setw(
            20
        ) << fixed << setprecision(
            BALANCE_PRECISION
        ) << CLIENT_ACCOUNT.balance << " |";
        cout << endl << TABLE_LINE << endl;
    }

    inline void printAdminHeader(
        const string& TABLE_LINE
    ) {
        cout << TABLE_LINE << endl;
        cout << "| " << setw(
            20
        ) << "Username";
        cout << " | " << setw(
            30
        ) << "Password";
        cout << " | " << setw(
            28
        ) << "Create New Client Account?";
        cout << " | " << setw(
            28
        ) << "Show Client Account List?";
        cout << " | " << setw(
            28
        ) << "Update Client Account?";
        cout << " | " << setw(
            28
        ) << "Find Client Account?";
        cout << " | " << setw(
            28
        ) << "Delete Client Account?";
        cout << " | " << setw(
            28
        ) << "Transactions?";
        cout << " |";
        cout << endl << TABLE_LINE << endl;
    }

    inline void printBody(
        const AdminAccount& ADMIN_ACCOUNT,
        const string& TABLE_LINE
    ) {
        cout << "| " << setw(
            20
        ) << ADMIN_ACCOUNT.username;
        cout << " | " << setw(
            30
        ) << ADMIN_ACCOUNT.password;
        cout << " | " << setw(
            28
        ) << ADMIN_ACCOUNT.adminRole.createNewClientAccount;
        cout << " | " << setw(
            28
        ) << ADMIN_ACCOUNT.adminRole.showClientAccountList;
        cout << " | " << setw(
            28
        ) << ADMIN_ACCOUNT.adminRole.updateClientAccount;
        cout << " | " << setw(
            28
        ) << ADMIN_ACCOUNT.adminRole.findClientAccount;
        cout << " | " << setw(
            28
        ) << ADMIN_ACCOUNT.adminRole.deleteClientAccount;
        cout << " | " << setw(
            28
        ) << ADMIN_ACCOUNT.adminRole.transactions;
        cout << " |";
        cout << endl << TABLE_LINE << endl;
    }

    inline void printBody(
        const OwnerAccount& OWNER_ACCOUNT,
        const string& TABLE_LINE
    ) {
        cout << "| " << setw(
            30
        ) << OWNER_ACCOUNT.username;
        cout << " | " << setw(
            30
        ) << OWNER_ACCOUNT.password << " |";
        cout << endl << TABLE_LINE << endl;
    }

    inline void printClientAccountRecordsTable(
        const ClientAccount& CLIENT_ACCOUNT
    ) {
        printClientHeader(
            CLIENT_TABLE_LINE
        );
        printBody(
            CLIENT_ACCOUNT,
            CLIENT_TABLE_LINE
        );
    }

    inline void printBalance(
        const long double BALANCE
    ) {
        cout << "Current Balance = " << fixed << setprecision(
            BALANCE_PRECISION
        ) << BALANCE << endl;
    }

    inline void printTotalBalancesHeader() {
        cout << TOTAL_BALANCES_TABLE_LINE << endl;
        cout << "| " << setw(
            20
        ) << "Identifier Number";
        cout << " | " << setw(
            30
        ) << "Full Name";
        cout << " | " << setw(
            20
        ) << "Balance" << " |";
        cout << endl << TOTAL_BALANCES_TABLE_LINE << endl;
    }

    inline void printTotalBalancesBody(
        const ClientAccount& CLIENT_ACCOUNT
    ) {
        cout << "| " << setw(
            20
        ) << CLIENT_ACCOUNT.identifierNumber;
        cout << " | " << setw(
            30
        ) << CLIENT_ACCOUNT.fullName.firstName + " " + CLIENT_ACCOUNT.fullName.secondName;
        cout << " | " << setw(
            20
        ) << fixed << setprecision(
            BALANCE_PRECISION
        ) << CLIENT_ACCOUNT.balance << " |";
        cout << endl << TOTAL_BALANCES_TABLE_LINE << endl;
    }
}