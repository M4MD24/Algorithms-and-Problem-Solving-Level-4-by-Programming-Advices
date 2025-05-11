#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
#include "Constants.h"
using namespace std;
using namespace Constants;

enum AccountTypeLoginMenuChoice {
    Owner = 1,
    Admin = 2,
    ExitProgram = 3
};

enum AdminMenuChoice {
    CreateNewClientAccount = 1,
    ShowClientAccountList = 2,
    UpdateClientAccount = 3,
    DeleteClientAccount = 4,
    FindClientAccount = 5,
    Transactions = 6,
    AdminLogout = 7
};

enum OwnerMenuChoice {
    CreateNewAdminAccount = 1,
    ShowAdminAccountList = 2,
    UpdateAdminAccount = 3,
    DeleteAdminAccount = 4,
    FindAdminAccount = 5,
    OwnerLogout = 6
};

enum TransactionsChoice {
    Deposit = 1,
    Withdraw = 2,
    TotalBalances = 3,
    BackToAdminMenu = 4
};

enum FileRequest {
    Update = 1,
    Delete = 2
};

struct MobileNumber {
    string countryCode,
           contactNumber;
};

struct FullName {
    string firstName,
           secondName;
};

struct ClientAccount {
    string identifierNumber;
    string PIN_Code;
    FullName fullName;
    MobileNumber mobileNumber;
    long double balance = 0.0;
};

struct OwnerAccount {
    string username;
    string password;
};

struct AdminRole {
    bool createNewClientAccount;
    bool showClientAccountList;
    bool updateClientAccount;
    bool findClientAccount;
    bool deleteClientAccount;
    bool transactions;
};

struct AdminAccount {
    string username;
    string password;
    AdminRole adminRole{};
};

AdminAccount findAccount(
    const AdminAccount& ACCOUNT,
    const bool& PRINT_TABLE
);

ClientAccount findClientAccountByIdentifierNumber(
    const bool& DISPLAY_CLIENT_ACCOUNT_INFORMATION,
    const string& IDENTIFIER_NUMBER
);

void displayAdminMenu(
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


void displayOwnerMenu() {
    cout << "Owner Menu:" << endl
        << "[1] Create New Admin Account" << endl
        << "[2] Show Admin Account List" << endl
        << "[3] Update Admin Account" << endl
        << "[4] Delete Admin Account" << endl
        << "[5] Find Admin Account" << endl
        << "[6] Logout" << endl;
}

void displayTransactionsMenu() {
    cout << "Transactions Menu:" << endl
        << "[1] Deposit" << endl
        << "[2] Withdraw" << endl
        << "[3] Total Balances" << endl
        << "[4] Back to Admin Menu" << endl;
}

void displayAccountTypeLoginMenu() {
    cout << "Account Type Login Menu:" << endl
        << "[1] Owner Account" << endl
        << "[2] Admin Account" << endl
        << "[3] Exit Program" << endl;
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

short readNumber(
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

bool isPositiveNumber(
    const long double& NUMBER
) { return NUMBER > 0; }

string readText(
    const string& INPUT_TYPE_NAME
) {
    cout << "Enter " << INPUT_TYPE_NAME << ":" << endl;
    string TEXT;
    cin >> TEXT;
    return TEXT;
}

void readPIN_Code(
    string& PIN_Code
) {
    do {
        PIN_Code = readText(
            "PIN Code"
        );
    } while (PIN_Code.length() != 4);
}

void readFirstName(
    string& firstName
) {
    firstName = readText(
        "First Name"
    );
}

void readSecondName(
    string& secondName
) {
    secondName = readText(
        "Second Name"
    );
}

void readFullName(
    FullName& fullName
) {
    readFirstName(
        fullName.firstName
    );
    readSecondName(
        fullName.secondName
    );
}

void readCountryCode(
    string& countryCode
) {
    countryCode = readText(
        "Country Code"
    );
}

void readContactNumber(
    string& contactNumber
) {
    contactNumber = readText(
        "Contact Number"
    );
}

void readMobileNumber(
    MobileNumber& mobileNumber
) {
    readCountryCode(
        mobileNumber.countryCode
    );
    readContactNumber(
        mobileNumber.contactNumber
    );
}

void readBalance(
    long double& balance
) {
    cout << "Enter Balance" << endl;
    cin >> balance;
}

void readUsername(
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

void readPassword(
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

bool areYourSure(
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

void readCreateNewClientAccountPermission(
    AdminRole& adminRole
) {
    adminRole.createNewClientAccount = areYourSure(
        "Can Create New Client Account?"
    );
}

void readShowClientAccountListPermission(
    AdminRole& adminRole
) {
    adminRole.showClientAccountList = areYourSure(
        "Can Show Client Account List?"
    );
}

void readUpdateClientAccountPermission(
    AdminRole& adminRole
) {
    adminRole.updateClientAccount = areYourSure(
        "Can Update Client Account?"
    );
}

void readFindClientAccountPermission(
    AdminRole& adminRole
) {
    adminRole.findClientAccount = areYourSure(
        "Can Find Client Account?"
    );
}

void readDeleteClientAccountPermission(
    AdminRole& adminRole
) {
    adminRole.deleteClientAccount = areYourSure(
        "Can Delete Client Account?"
    );
}

void readTransactionsPermission(
    AdminRole& adminRole
) {
    adminRole.transactions = areYourSure(
        "Can Transactions?"
    );
}

void readAdminRole(
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

void readAccount(
    AdminAccount& account
) {
    readUsername(
        account.username
    );

    readPassword(
        account.password
    );

    readAdminRole(
        account.adminRole
    );
}

string convertFromRecordToLine(
    const ClientAccount& ACCOUNT,
    const string& SEPARATOR = "\\\\"
) {
    return ACCOUNT.identifierNumber + SEPARATOR +
        ACCOUNT.PIN_Code + SEPARATOR +
        ACCOUNT.fullName.firstName + SEPARATOR +
        ACCOUNT.fullName.secondName + SEPARATOR +
        ACCOUNT.mobileNumber.countryCode + SEPARATOR +
        ACCOUNT.mobileNumber.contactNumber + SEPARATOR +
        to_string(
            ACCOUNT.balance
        );
}

string convertFromRecordToLine(
    const AdminAccount& ACCOUNT,
    const string& SEPARATOR = "\\\\"
) {
    return ACCOUNT.username + SEPARATOR +
        ACCOUNT.password + SEPARATOR +
        to_string(
            ACCOUNT.adminRole.createNewClientAccount
        ) + SEPARATOR +
        to_string(
            ACCOUNT.adminRole.showClientAccountList
        ) + SEPARATOR +
        to_string(
            ACCOUNT.adminRole.updateClientAccount
        ) + SEPARATOR +
        to_string(
            ACCOUNT.adminRole.deleteClientAccount
        ) + SEPARATOR +
        to_string(
            ACCOUNT.adminRole.findClientAccount
        ) + SEPARATOR +
        to_string(
            ACCOUNT.adminRole.transactions
        );
}

void saveLineToFile(
    const string& LINE,
    const string& FILE_PATH
) {
    fstream file(
        FILE_PATH,
        ios::out | ios::app
    );
    if (file.is_open())
        file << LINE << endl;
    file.close();
}

void createNewAdminAccount() {
    AdminAccount account{};

    readAccount(
        account
    );

    const string ACCOUNT_LINE = convertFromRecordToLine(
        account
    );

    saveLineToFile(
        ACCOUNT_LINE,
        ADMIN_ACCOUNTS_PATH
    );

    cout << "Admin account has been created successfully." << endl;
}

void printClientHeader(
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

void printBody(
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

void printAdminHeader(
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

void printBody(
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

void printBody(
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

void printClientAccountRecordsTable(
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

vector<string> readLineParts(
    const string& ACCOUNT_LINE,
    const string& SEPARATOR = "\\\\"
) {
    vector<string> tokens;
    size_t previous = 0,
           position;
    while (
        (
            position = ACCOUNT_LINE.find(
                SEPARATOR,
                previous
            )
        ) != string::npos
    ) {
        tokens.push_back(
            ACCOUNT_LINE.substr(
                previous,
                position - previous
            )
        );
        previous = position + SEPARATOR.length();
    }
    tokens.push_back(
        ACCOUNT_LINE.substr(
            previous
        )
    );
    return tokens;
}

void readFields(
    ClientAccount& clientAccount,
    const vector<string>& FIELDS
) {
    if (FIELDS.size() == 7) {
        clientAccount.identifierNumber = FIELDS[0];

        clientAccount.PIN_Code = FIELDS[1];

        clientAccount.fullName = {
            FIELDS[2],
            FIELDS[3]
        };

        clientAccount.mobileNumber = {
            FIELDS[4],
            FIELDS[5]
        };

        clientAccount.balance = stold(
            FIELDS[6]
        );
    }
}

void readFields(
    AdminAccount& adminAccount,
    const vector<string>& FIELDS
) {
    if (FIELDS.size() == 8) {
        adminAccount.username = FIELDS[0];

        adminAccount.password = FIELDS[1];

        adminAccount.adminRole.createNewClientAccount = static_cast<bool>(
            stoi(
                FIELDS[2]
            )
        );

        adminAccount.adminRole.showClientAccountList = static_cast<bool>(
            stoi(
                FIELDS[3]
            )
        );

        adminAccount.adminRole.updateClientAccount = static_cast<bool>(
            stoi(
                FIELDS[4]
            )
        );

        adminAccount.adminRole.findClientAccount = static_cast<bool>(
            stoi(
                FIELDS[5]
            )
        );

        adminAccount.adminRole.deleteClientAccount = static_cast<bool>(
            stoi(
                FIELDS[6]
            )
        );

        adminAccount.adminRole.transactions = static_cast<bool>(
            stoi(
                FIELDS[7]
            )
        );
    }
}

void readFields(
    OwnerAccount& ownerAccount,
    const vector<string>& FIELDS
) {
    if (FIELDS.size() == 2) {
        ownerAccount.username = FIELDS[0];

        ownerAccount.password = FIELDS[1];
    }
}

void showClientAccountList() {
    fstream file(
        CLIENT_ACCOUNTS_PATH,
        ios::in
    );

    printClientHeader(
        CLIENT_TABLE_LINE
    );

    size_t counter = 0;
    if (file.is_open()) {
        string clientAccountLine;
        while (
            getline(
                file,
                clientAccountLine
            )
        ) {
            counter++;

            ClientAccount clientAccount;

            readFields(
                clientAccount,
                readLineParts(
                    clientAccountLine
                )
            );

            printBody(
                clientAccount,
                CLIENT_TABLE_LINE
            );
        }
        file.close();
    }

    cout << "Count of Client Accounts = " << counter << " Client(s)" << endl;
}

void showAdminAccountList() {
    fstream file(
        ADMIN_ACCOUNTS_PATH,
        ios::in
    );

    printAdminHeader(
        ADMIN_TABLE_LINE
    );

    size_t counter = 0;
    if (file.is_open()) {
        string adminAccountLine;
        while (
            getline(
                file,
                adminAccountLine
            )
        ) {
            counter++;

            AdminAccount adminAccount;

            readFields(
                adminAccount,
                readLineParts(
                    adminAccountLine
                )
            );

            printBody(
                adminAccount,
                ADMIN_TABLE_LINE
            );
        }
        file.close();
    }

    cout << "Count of Admin Accounts = " << counter << " Admin(s)" << endl;
}

void updateClientAccount(
    ClientAccount& clientAccount
) {
    readPIN_Code(
        clientAccount.PIN_Code
    );

    readFullName(
        clientAccount.fullName
    );

    readMobileNumber(
        clientAccount.mobileNumber
    );

    readBalance(
        clientAccount.balance
    );
}

vector<string> readLinePartsInFile(
    const string& FILE_PATH
) {
    fstream file(
        FILE_PATH,
        ios::in
    );

    vector<string> lines;

    if (file.is_open()) {
        string line;
        while (
            getline(
                file,
                line
            )
        )
            lines.push_back(
                line
            );
        file.close();
    }

    return lines;
}

bool whatDoYouNeedForFile(
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

string checkFileRequest(
    const FileRequest& REQUEST
) {
    if (REQUEST == Update)
        return "Update";
    return "Delete";
}

void updateClientAccountByIdentifierNumber(
    const ClientAccount& CLIENT_ACCOUNT,
    const bool isTransaction
) {
    if (
        const string CLIENT_ACCOUNT_IDENTIFIER_NUMBER = CLIENT_ACCOUNT.identifierNumber;
        !CLIENT_ACCOUNT_IDENTIFIER_NUMBER.empty()
    )
        if (
            whatDoYouNeedForFile(
                checkFileRequest(
                    Update
                )
            )
        ) {
            vector<string> clientAccountLines = readLinePartsInFile(
                CLIENT_ACCOUNTS_PATH
            );

            vector<string> updatedClientAccountLines;

            for (string& clientAccountLine : clientAccountLines) {
                ClientAccount currentClientAccount;

                const vector<string> CLIENT_ACCOUNT_FIELDS = readLineParts(
                    clientAccountLine
                );

                readFields(
                    currentClientAccount,
                    CLIENT_ACCOUNT_FIELDS
                );

                if (currentClientAccount.identifierNumber == CLIENT_ACCOUNT_IDENTIFIER_NUMBER) {
                    if (!isTransaction) {
                        updateClientAccount(
                            currentClientAccount
                        );
                        updatedClientAccountLines.push_back(
                            convertFromRecordToLine(
                                currentClientAccount
                            )
                        );
                    } else
                        updatedClientAccountLines.push_back(
                            convertFromRecordToLine(
                                CLIENT_ACCOUNT
                            )
                        );
                } else
                    updatedClientAccountLines.push_back(
                        clientAccountLine
                    );
            }

            fstream file(
                CLIENT_ACCOUNTS_PATH,
                ios::out | ios::trunc
            );

            for (const string& UPDATED_LINE : updatedClientAccountLines)
                file << UPDATED_LINE << endl;

            file.close();

            cout << "Client account has been updated successfully." << endl;
        }
}

void updateAdminAccount(
    AdminAccount& adminAccount
) {
    readPassword(
        adminAccount.password
    );

    readAdminRole(
        adminAccount.adminRole
    );
}

void updateAdminAccountByUsername(
    const AdminAccount& ADMIN_ACCOUNT
) {
    if (
        const string ADMIN_ACCOUNT_USERNAME = ADMIN_ACCOUNT.username;
        !ADMIN_ACCOUNT_USERNAME.empty()
    )
        if (
            whatDoYouNeedForFile(
                checkFileRequest(
                    Update
                )
            )
        ) {
            vector<string> adminAccountLines = readLinePartsInFile(
                ADMIN_ACCOUNTS_PATH
            );

            vector<string> updatedAdminAccountLines;

            for (string& adminAccountLine : adminAccountLines) {
                AdminAccount currentAdminAccount;

                const vector<string> ADMIN_ACCOUNT_FIELDS = readLineParts(
                    adminAccountLine
                );

                readFields(
                    currentAdminAccount,
                    ADMIN_ACCOUNT_FIELDS
                );

                if (currentAdminAccount.username == ADMIN_ACCOUNT_USERNAME) {
                    updateAdminAccount(
                        currentAdminAccount
                    );
                    updatedAdminAccountLines.push_back(
                        convertFromRecordToLine(
                            currentAdminAccount
                        )
                    );
                } else
                    updatedAdminAccountLines.push_back(
                        adminAccountLine
                    );
            }

            fstream file(
                ADMIN_ACCOUNTS_PATH,
                ios::out | ios::trunc
            );

            for (const string& UPDATED_LINE : updatedAdminAccountLines)
                file << UPDATED_LINE << endl;

            file.close();

            cout << "Client account has been updated successfully." << endl;
        }
}

void deleteAccount(
    const ClientAccount& CLIENT_ACCOUNT
) {
    if (
        const string CLIENT_ACCOUNT_IDENTIFIER_NUMBER = CLIENT_ACCOUNT.identifierNumber;
        !CLIENT_ACCOUNT_IDENTIFIER_NUMBER.empty()
    )
        if (
            whatDoYouNeedForFile(
                checkFileRequest(
                    Delete
                )
            )
        ) {
            vector<string> accountLines = readLinePartsInFile(
                CLIENT_ACCOUNTS_PATH
            );

            fstream file(
                CLIENT_ACCOUNTS_PATH,
                ios::out | ios::trunc
            );

            for (string& accountLine : accountLines) {
                const string CURRENT_IDENTIFIER_NUMBER = readLineParts(
                    accountLine
                )[0];

                if (CURRENT_IDENTIFIER_NUMBER != CLIENT_ACCOUNT_IDENTIFIER_NUMBER)
                    file << accountLine << endl;
            }

            file.close();

            cout << "Client account has been deleted successfully." << endl;
        }
}

void deleteAccount(
    const AdminAccount& ADMIN_ACCOUNT
) {
    if (
        const string ADMIN_ACCOUNT_USERNAME = ADMIN_ACCOUNT.username;
        !ADMIN_ACCOUNT_USERNAME.empty()
    )
        if (
            whatDoYouNeedForFile(
                checkFileRequest(
                    Delete
                )
            )
        ) {
            vector<string> accountLines = readLinePartsInFile(
                ADMIN_ACCOUNTS_PATH
            );

            fstream file(
                ADMIN_ACCOUNTS_PATH,
                ios::out | ios::trunc
            );

            for (string& accountLine : accountLines) {
                const string CURRENT_USERNAME = readLineParts(
                    accountLine
                )[0];

                if (CURRENT_USERNAME != ADMIN_ACCOUNT_USERNAME)
                    file << accountLine << endl;
            }

            file.close();

            cout << "Admin account has been deleted successfully." << endl;
        }
}

void readIdentifierNumber(
    string& identifierNumber,
    const bool& UPDATE
) {
    if (UPDATE)
        identifierNumber = readText(
            "Identifier Number"
        );
    else
        do {
            identifierNumber = readText(
                "Identifier Number"
            );
        } while (
            identifierNumber == findClientAccountByIdentifierNumber(
                false,
                identifierNumber
            ).identifierNumber
        );
}

void readAccount(
    ClientAccount& clientAccount
) {
    readIdentifierNumber(
        clientAccount.identifierNumber,
        false
    );

    readPIN_Code(
        clientAccount.PIN_Code
    );

    readFullName(
        clientAccount.fullName
    );

    readMobileNumber(
        clientAccount.mobileNumber
    );

    readBalance(
        clientAccount.balance
    );
}

void createNewClientAccount() {
    ClientAccount account{};
    readAccount(
        account
    );

    const string ACCOUNT_LINE = convertFromRecordToLine(
        account
    );

    saveLineToFile(
        ACCOUNT_LINE,
        CLIENT_ACCOUNTS_PATH
    );

    cout << "Client account has been created successfully." << endl;
}

ClientAccount findClientAccountByIdentifierNumber(
    const bool& DISPLAY_CLIENT_ACCOUNT_INFORMATION
) {
    string identifierNumberTarget;
    readIdentifierNumber(
        identifierNumberTarget,
        true
    );

    fstream file(
        CLIENT_ACCOUNTS_PATH,
        ios::in
    );

    if (file.is_open()) {
        string clientAccountLine;
        while (
            getline(
                file,
                clientAccountLine
            )
        ) {
            const string CURRENT_IDENTIFIER_NUMBER = readLineParts(
                clientAccountLine
            )[0];

            if (CURRENT_IDENTIFIER_NUMBER == identifierNumberTarget) {
                cout << "Is Found" << endl;

                ClientAccount clientAccount;
                readFields(
                    clientAccount,
                    readLineParts(
                        clientAccountLine
                    )
                );

                if (DISPLAY_CLIENT_ACCOUNT_INFORMATION) {
                    printClientHeader(
                        CLIENT_TABLE_LINE
                    );
                    printBody(
                        clientAccount,
                        CLIENT_TABLE_LINE
                    );
                }

                return clientAccount;
            }
        }

        file.close();

        cout << "Isn't Found" << endl;
    }

    return ClientAccount{};
}

ClientAccount findClientAccountByIdentifierNumber(
    const bool& DISPLAY_CLIENT_ACCOUNT_INFORMATION,
    const string& IDENTIFIER_NUMBER
) {
    fstream file(
        CLIENT_ACCOUNTS_PATH,
        ios::in
    );

    if (file.is_open()) {
        string clientAccountLine;
        while (
            getline(
                file,
                clientAccountLine
            )
        ) {
            const string CURRENT_IDENTIFIER_NUMBER = readLineParts(
                clientAccountLine
            )[0];

            if (CURRENT_IDENTIFIER_NUMBER == IDENTIFIER_NUMBER) {
                ClientAccount clientAccount;
                readFields(
                    clientAccount,
                    readLineParts(
                        clientAccountLine
                    )
                );

                if (DISPLAY_CLIENT_ACCOUNT_INFORMATION) {
                    cout << "Is Found" << endl;

                    printClientHeader(
                        CLIENT_TABLE_LINE
                    );

                    printBody(
                        clientAccount,
                        CLIENT_TABLE_LINE
                    );
                }

                return clientAccount;
            }
        }

        if (DISPLAY_CLIENT_ACCOUNT_INFORMATION)
            cout << "Isn't Found" << endl;

        file.close();
    }

    return ClientAccount{};
}

void printBalance(
    const long double BALANCE
) {
    cout << "Current Balance = " << fixed << setprecision(
        BALANCE_PRECISION
    ) << BALANCE << endl;
}

long double readAmount() {
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

void withdraw(
    ClientAccount clientAccount
) {
    long double& balance = clientAccount.balance;

    const long double AMOUNT = readAmount();

    balance -= AMOUNT;

    updateClientAccountByIdentifierNumber(
        clientAccount,
        true
    );
}

void deposit(
    ClientAccount clientAccount
) {
    long double& balance = clientAccount.balance;

    const long double AMOUNT = readAmount();

    balance += AMOUNT;

    updateClientAccountByIdentifierNumber(
        clientAccount,
        true
    );
}

void printTotalBalancesHeader() {
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

void printTotalBalancesBody(
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

void printTotalBalances(
    const vector<string>& CLIENT_ACCOUNT_LINES
) {
    long double totalBalances = 0.0;

    printTotalBalancesHeader();

    for (const string& CLIENT_ACCOUNT_LINE : CLIENT_ACCOUNT_LINES) {
        ClientAccount clientAccount;

        readFields(
            clientAccount,
            readLineParts(
                CLIENT_ACCOUNT_LINE
            )
        );

        totalBalances += clientAccount.balance;

        printTotalBalancesBody(
            clientAccount
        );
    }

    cout << "Total Balances = " << totalBalances << endl;
}

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

AdminAccount findAccount(
    const bool& PRINT_TABLE
) {
    string username;
    readUsername(
        username
    );

    fstream file(
        ADMIN_ACCOUNTS_PATH,
        ios::in
    );

    if (
        file.is_open() &&
        findAccount(
            {
                username,
                "",
                {
                    false,
                    false,
                    false,
                    false,
                    false,
                    false,
                }
            },
            false
        ).username == username
    ) {
        string adminAccountLine;
        while (
            getline(
                file,
                adminAccountLine
            )
        ) {
            const vector<string> ACCOUNT_PARTS = readLineParts(
                adminAccountLine
            );

            AdminAccount foundAccount{
                ACCOUNT_PARTS[0],
                ACCOUNT_PARTS[1],
                {
                    static_cast<bool>(
                        stoi(
                            ACCOUNT_PARTS[2]
                        )
                    ),
                    static_cast<bool>(
                        stoi(
                            ACCOUNT_PARTS[3]
                        )
                    ),
                    static_cast<bool>(
                        stoi(
                            ACCOUNT_PARTS[4]
                        )
                    ),
                    static_cast<bool>(
                        stoi(
                            ACCOUNT_PARTS[5]
                        )
                    ),
                    static_cast<bool>(
                        stoi(
                            ACCOUNT_PARTS[6]
                        )
                    ),
                    static_cast<bool>(
                        stoi(
                            ACCOUNT_PARTS[7]
                        )
                    )
                }
            };

            if (
                username == foundAccount.username
            ) {
                AdminAccount adminAccount;
                readFields(
                    adminAccount,
                    readLineParts(
                        adminAccountLine
                    )
                );

                if (PRINT_TABLE) {
                    cout << "Is Found" << endl;

                    printAdminHeader(
                        ADMIN_TABLE_LINE
                    );

                    printBody(
                        foundAccount,
                        ADMIN_TABLE_LINE
                    );
                }

                return foundAccount;
            }
        }

        if (PRINT_TABLE)
            cout << "Isn't Found" << endl;

        file.close();
        return AdminAccount{};
    }

    if (PRINT_TABLE)
        cout << "Isn't Found" << endl;

    return AdminAccount{};
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

OwnerAccount findAccount(
    const OwnerAccount& TARGET_ACCOUNT,
    const bool& PRINT_TABLE
) {
    fstream file(
        OWNER_ACCOUNTS_PATH,
        ios::in
    );

    if (file.is_open()) {
        string ownerAccountLine;
        while (
            getline(
                file,
                ownerAccountLine
            )
        ) {
            const vector<string> ACCOUNT_PARTS = readLineParts(
                ownerAccountLine
            );

            OwnerAccount FOUND_ACCOUNT{
                ACCOUNT_PARTS[0],
                ACCOUNT_PARTS[1]
            };

            if (
                TARGET_ACCOUNT.username == FOUND_ACCOUNT.username
            ) {
                if (TARGET_ACCOUNT.password == FOUND_ACCOUNT.password) {
                    OwnerAccount ownerAccount;
                    readFields(
                        ownerAccount,
                        readLineParts(
                            ownerAccountLine
                        )
                    );

                    if (PRINT_TABLE) {
                        cout << "Is Found" << endl;

                        printClientHeader(
                            ADMIN_TABLE_LINE
                        );

                        printBody(
                            ownerAccount,
                            ADMIN_TABLE_LINE
                        );
                    }

                    return TARGET_ACCOUNT;
                }

                return OwnerAccount{
                    TARGET_ACCOUNT.username
                };
            }
        }

        if (PRINT_TABLE)
            cout << "Isn't Found" << endl;

        file.close();
        return OwnerAccount{};
    }

    if (PRINT_TABLE)
        cout << "Isn't Found" << endl;

    return OwnerAccount{};
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

void login(
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

AdminAccount findAccount(
    const AdminAccount& TARGET_ACCOUNT,
    const bool& PRINT_TABLE
) {
    fstream file(
        ADMIN_ACCOUNTS_PATH,
        ios::in
    );

    if (file.is_open()) {
        string adminAccountLine;
        while (
            getline(
                file,
                adminAccountLine
            )
        ) {
            const vector<string> ACCOUNT_PARTS = readLineParts(
                adminAccountLine
            );

            AdminAccount foundAccount{
                ACCOUNT_PARTS[0],
                ACCOUNT_PARTS[1],
                {
                    static_cast<bool>(
                        stoi(
                            ACCOUNT_PARTS[2]
                        )
                    ),
                    static_cast<bool>(
                        stoi(
                            ACCOUNT_PARTS[3]
                        )
                    ),
                    static_cast<bool>(
                        stoi(
                            ACCOUNT_PARTS[4]
                        )
                    ),
                    static_cast<bool>(
                        stoi(
                            ACCOUNT_PARTS[5]
                        )
                    ),
                    static_cast<bool>(
                        stoi(
                            ACCOUNT_PARTS[6]
                        )
                    ),
                    static_cast<bool>(
                        stoi(
                            ACCOUNT_PARTS[7]
                        )
                    )
                }
            };

            if (
                TARGET_ACCOUNT.username == foundAccount.username
            ) {
                if (TARGET_ACCOUNT.password == foundAccount.password) {
                    AdminAccount adminAccount;
                    readFields(
                        adminAccount,
                        readLineParts(
                            adminAccountLine
                        )
                    );

                    if (PRINT_TABLE) {
                        cout << "Is Found" << endl;

                        printClientHeader(
                            ADMIN_TABLE_LINE
                        );

                        printBody(
                            TARGET_ACCOUNT,
                            ADMIN_TABLE_LINE
                        );
                    }

                    return foundAccount;
                }

                return AdminAccount{
                    TARGET_ACCOUNT.username
                };
            }
        }

        if (PRINT_TABLE)
            cout << "Isn't Found" << endl;

        file.close();
        return AdminAccount{};
    }

    if (PRINT_TABLE)
        cout << "Isn't Found" << endl;

    return AdminAccount{};
}

void login(
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

void performAccountTypeLoginMenu() {
    do {
        displayAccountTypeLoginMenu();
        constexpr short START_NUMBER = 1,
                        END_NUMBER = 3;
        const short CHOICE = readNumber(
            START_NUMBER,
            END_NUMBER
        );
        if (static_cast<AccountTypeLoginMenuChoice>(CHOICE) != ExitProgram) {
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
        } else {
            cout << "Salam!";
            exit(
                0
            );
        }
    } while (true);
}

void startProgram() { performAccountTypeLoginMenu(); }

int main() { startProgram(); }