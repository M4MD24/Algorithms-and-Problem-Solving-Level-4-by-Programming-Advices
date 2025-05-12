#include <fstream>

#include "library/Constants.h"
#include "library/Display.h"
#include "library/Options.h"
#include "library/Read.h"
#include "library/Tools.h"

using namespace Constants;
using namespace Display;
using namespace Read;
using namespace Options;
using namespace Tools;

void performTransactionMenu() {
    do {
        displayTransactionsMenu();
        constexpr short START_NUMBER = 1,
                        END_NUMBER = 4;
        const short CHOICE = readNumber(
            START_NUMBER,
            END_NUMBER
        );
        switch (static_cast<TransactionsChoice>(CHOICE)) {
        case Deposit:
            deposit(
                findClientAccountByIdentifierNumber(
                    true
                )
            );
            cout << endl;
            break;
        case Withdraw:
            withdraw(
                findClientAccountByIdentifierNumber(
                    true
                )
            );
            cout << endl;
            break;
        case TotalBalances:
            printTotalBalances(
                readLinePartsInFile(
                    CLIENT_ACCOUNTS_PATH
                )
            );
            cout << endl;
            break;
        case BackToAdminMenu:
            return;
        default: ;
        }
    } while (true);
}

void performAdminMenu(
    const AdminAccount& ADMIN_ACCOUNT
) {
    do {
        displayAdminMenu(
            ADMIN_ACCOUNT.adminRole
        );
        constexpr short START_NUMBER = 1,
                        END_NUMBER = 7;
        const short CHOICE = readNumber(
            START_NUMBER,
            END_NUMBER
        );
        switch (static_cast<AdminMenuChoice>(CHOICE)) {
        case CreateNewClientAccount:
            if (ADMIN_ACCOUNT.adminRole.createNewClientAccount)
                createNewClientAccount();
            else
                cout << "You don't have permission!" << endl;
            cout << endl;
            break;
        case ShowClientAccountList:
            if (ADMIN_ACCOUNT.adminRole.showClientAccountList)
                showClientAccountList();
            else
                cout << "You don't have permission!" << endl;
            cout << endl;
            break;
        case UpdateClientAccount:
            if (ADMIN_ACCOUNT.adminRole.updateClientAccount)
                updateClientAccountByIdentifierNumber(
                    findClientAccountByIdentifierNumber(
                        true
                    ),
                    false
                );
            else
                cout << "You don't have permission!" << endl;
            cout << endl;
            break;
        case DeleteClientAccount:
            if (ADMIN_ACCOUNT.adminRole.deleteClientAccount)
                deleteAccount(
                    findClientAccountByIdentifierNumber(
                        true
                    )
                );
            else
                cout << "You don't have permission!" << endl;
            cout << endl;
            break;
        case FindClientAccount:
            if (ADMIN_ACCOUNT.adminRole.findClientAccount)
                findClientAccountByIdentifierNumber(
                    true
                );
            else
                cout << "You don't have permission!" << endl;
            cout << endl;
            break;
        case Transactions:
            if (ADMIN_ACCOUNT.adminRole.transactions)
                performTransactionMenu();
            else
                cout << "You don't have permission!" << endl;
            break;
        case AdminLogout:
            return;
        default: ;
        }
    } while (true);
}

void performOwnerMenu() {
    do {
        displayOwnerMenu();
        constexpr short START_NUMBER = 1,
                        END_NUMBER = 6;
        const short CHOICE = readNumber(
            START_NUMBER,
            END_NUMBER
        );
        switch (static_cast<AdminMenuChoice>(CHOICE)) {
        case CreateNewAdminAccount:
            createNewAdminAccount();
            cout << endl;
            break;
        case ShowAdminAccountList:
            showAdminAccountList();
            cout << endl;
            break;
        case UpdateAdminAccount:
            updateAdminAccountByUsername(
                findAccount(
                    true
                )
            );
            cout << endl;
            break;
        case DeleteAdminAccount:
            deleteAccount(
                findAccount(
                    true
                )
            );
            cout << endl;
            break;
        case FindAdminAccount:
            findAccount(
                true
            );
            cout << endl;
            break;
        case OwnerLogout:
            return;
        default: ;
        }
    } while (true);
}

inline void login(
    const AdminAccount& TARGET_ACCOUNT
) {
    const AdminAccount FOUND_ACCOUNT = findAccount(
        TARGET_ACCOUNT,
        false
    );

    if (FOUND_ACCOUNT.username == AdminAccount{}.username) {
        cout << "Username not Valid" << endl;
        return;
    }

    if (FOUND_ACCOUNT.password == AdminAccount{}.password) {
        cout << "Password not Valid" << endl;
        return;
    }

    cout << endl;

    performAdminMenu(
        FOUND_ACCOUNT
    );
}

inline void login(
    const OwnerAccount& TARGET_ACCOUNT
) {
    const OwnerAccount FOUND_ACCOUNT = findAccount(
        TARGET_ACCOUNT,
        false
    );

    if (FOUND_ACCOUNT.username == OwnerAccount{}.username) {
        cout << "Username not Valid" << endl;
        return;
    }

    if (FOUND_ACCOUNT.password == OwnerAccount{}.password) {
        cout << "Password not Valid" << endl;
        return;
    }

    cout << endl;

    performOwnerMenu();
}

void performAccountTypeLoginMenu() {
    do {
        displayAccountTypeLoginMenu();
        constexpr short START_NUMBER = 1,
                        END_NUMBER = 3;
        const short CHOICE = readNumber(
            START_NUMBER,
            END_NUMBER
        );
        if (
            CHOICE < END_NUMBER &&
            CHOICE >= START_NUMBER
        ) {
            const string USERNAME = readText(
                             "Username"
                         ),
                         PASSWORD = readText(
                             "Password"
                         );
            switch (static_cast<AccountTypeLoginMenuChoice>(CHOICE)) {
            case Owner:
                login(
                    OwnerAccount{
                        USERNAME,
                        PASSWORD
                    }
                );
                cout << endl;
                break;
            case Admin:
                login(
                    AdminAccount{
                        USERNAME,
                        PASSWORD,
                        {
                            false,
                            false,
                            false,
                            false,
                            false,
                            false,
                        }
                    }
                );
                cout << endl;
                break;
            default: ;
            }
        } else if (CHOICE == END_NUMBER) {
            cout << "Salam!";
            exit(
                0
            );
        }
    } while (true);
}

void startProgram() { performAccountTypeLoginMenu(); }

int main() { startProgram(); }