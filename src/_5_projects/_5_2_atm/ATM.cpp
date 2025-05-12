#include <fstream>
#include <cmath>

#include "../_5_1_bank/library/Constants.h"
#include "../_5_1_bank/library/Display.h"
#include "../_5_1_bank/library/Options.h"
#include "../_5_1_bank/library/Read.h"
#include "../_5_1_bank/library/Tools.h"

using namespace Constants;
using namespace Display;
using namespace Read;
using namespace Options;

enum ClientMenuChoice {
    Withdraw = 1,
    Deposit = 2,
    ShowBalance = 3,
    Logout = 4
};

void displayClientMenu() {
    cout << "Client Menu:" << endl
        << "[1] Withdraw" << endl
        << "[2] Deposit" << endl
        << "[3] Show Balance" << endl
        << "[4] Logout" << endl;
}

void displayWithdrawMenu() {
    cout << "Withdraw Menu:" << endl
        << "[1] 50     | [2] 100" << endl
        << "[3] 500    | [4] 1000" << endl
        << "[5] 2000   | [6] 4000" << endl
        << "[7] Custom | [8] back to Client Menu" << endl;
}

void withdraw(
    ClientAccount& clientAccount,
    const long double& BALANCE
) {
    if (clientAccount.balance >= BALANCE) {
        clientAccount.balance -= BALANCE;
        Tools::updateClientAccountByIdentifierNumber(
            clientAccount,
            true
        );
    } else
        cout << "The amount is greater than your balance" << endl;
}

void performWithdrawMenu(
    ClientAccount& clientAccount
) {
    do {
        displayWithdrawMenu();
        constexpr short START_NUMBER = 1,
                        END_NUMBER = 8;
        const short CHOICE = readNumber(
            START_NUMBER,
            END_NUMBER
        );
        switch (static_cast<ClientMenuChoice>(CHOICE)) {
        case 1:
            withdraw(
                clientAccount,
                50
            );
            cout << endl;
            break;
        case 2:
            withdraw(
                clientAccount,
                100
            );
            cout << endl;
            break;
        case 3:
            withdraw(
                clientAccount,
                500
            );
            cout << endl;
            break;
        case 4:
            withdraw(
                clientAccount,
                1000
            );
            cout << endl;
            break;
        case 5:
            withdraw(
                clientAccount,
                2000
            );
            cout << endl;
            break;
        case 6:
            withdraw(
                clientAccount,
                4000
            );
            cout << endl;
            break;
        case 7:
            withdraw(
                clientAccount,
                readAmount()
            );
            cout << endl;
            break;
        case 8:
            return;
        default: ;
        }
    } while (true);
}

void deposit(
    ClientAccount& clientAccount
) {
    long double amount;
    do cout << "Enter Amount (multiples of 5)" << endl;
    while (
        !isNumber(
            amount
        ) ||
        !isPositiveNumber(
            amount
        ) ||
        fmod(
            amount,
            5.0
        ) != 0
    );

    clientAccount.balance += amount;

    Tools::updateClientAccountByIdentifierNumber(
        clientAccount,
        true
    );
}

void performClientMenu(
    ClientAccount& clientAccount
) {
    do {
        displayClientMenu();
        constexpr short START_NUMBER = 1,
                        END_NUMBER = 4;
        const short CHOICE = readNumber(
            START_NUMBER,
            END_NUMBER
        );
        switch (static_cast<ClientMenuChoice>(CHOICE)) {
        case ClientMenuChoice::Withdraw:
            performWithdrawMenu(
                clientAccount
            );
            cout << endl;
            break;
        case ClientMenuChoice::Deposit:
            deposit(
                clientAccount
            );
            cout << endl;
            break;
        case ShowBalance:
            printBalance(
                clientAccount.balance
            );
            cout << endl;
            break;
        case Logout:
            return;
        default: ;
        }
    } while (true);
}

void login() {
    ClientAccount targetAccount{};

    Tools::readIdentifierNumber(
        targetAccount.identifierNumber,
        true
    );

    readPIN_Code(
        targetAccount.PIN_Code
    );

    ClientAccount foundAccount = Tools::findAccount(
        targetAccount,
        false
    );

    if (foundAccount.identifierNumber == ClientAccount{}.identifierNumber) {
        cout << "Identifier Number not Valid" << endl;
        return;
    }

    if (foundAccount.PIN_Code == ClientAccount{}.PIN_Code) {
        cout << "PIN Code not Valid" << endl;
        return;
    }

    performClientMenu(
        foundAccount
    );
}

[[noreturn]] void startProgram() {
    while (true)
        login();
}

int main() { startProgram(); }