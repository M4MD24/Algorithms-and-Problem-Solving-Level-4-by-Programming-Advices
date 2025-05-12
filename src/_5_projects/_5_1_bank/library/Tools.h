#pragma once
#include <vector>
#include <fstream>
#include <cmath>

using namespace Read;
using namespace Display;

namespace Tools {
    void readIdentifierNumber(
        string& identifierNumber,
        const bool& UPDATE
    );

    inline void readAccount(
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

    inline void readAccount(
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

    inline string convertFromRecordToLine(
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

    inline string convertFromRecordToLine(
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

    inline void saveLineToFile(
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

    inline void createNewAdminAccount() {
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

    inline vector<string> readLineParts(
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

    inline void readFields(
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

    inline void readFields(
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

    inline void readFields(
        OwnerAccount& ownerAccount,
        const vector<string>& FIELDS
    ) {
        if (FIELDS.size() == 2) {
            ownerAccount.username = FIELDS[0];

            ownerAccount.password = FIELDS[1];
        }
    }

    inline ClientAccount findAccount(
        const ClientAccount& TARGET_ACCOUNT,
        const bool& PRINT_TABLE
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
                const vector<string> ACCOUNT_PARTS = readLineParts(
                    clientAccountLine
                );

                ClientAccount foundAccount{
                    ACCOUNT_PARTS[0],
                    ACCOUNT_PARTS[1],
                    {

                        ACCOUNT_PARTS[2],
                        ACCOUNT_PARTS[3]
                    },
                    {
                        ACCOUNT_PARTS[4],
                        ACCOUNT_PARTS[5]
                    },
                    stold(
                        ACCOUNT_PARTS[6]
                    )
                };

                if (
                    TARGET_ACCOUNT.identifierNumber == foundAccount.identifierNumber
                ) {
                    if (TARGET_ACCOUNT.PIN_Code == foundAccount.PIN_Code) {
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

                    return ClientAccount{
                        TARGET_ACCOUNT.identifierNumber
                    };
                }
            }

            if (PRINT_TABLE)
                cout << "Isn't Found" << endl;

            file.close();
            return ClientAccount{};
        }

        if (PRINT_TABLE)
            cout << "Isn't Found" << endl;

        return ClientAccount{};
    }

    inline AdminAccount findAccount(
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

    inline void showClientAccountList() {
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

    inline void showAdminAccountList() {
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

    inline void updateClientAccount(
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

    inline vector<string> readLinePartsInFile(
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

    inline void updateClientAccountByIdentifierNumber(
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

    inline void updateAdminAccount(
        AdminAccount& adminAccount
    ) {
        readPassword(
            adminAccount.password
        );

        readAdminRole(
            adminAccount.adminRole
        );
    }

    inline void updateAdminAccountByUsername(
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

    inline void deleteAccount(
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

    inline void deleteAccount(
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

    inline void createNewClientAccount() {
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

    inline ClientAccount findClientAccountByIdentifierNumber(
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

    inline ClientAccount findClientAccountByIdentifierNumber(
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

    inline void withdraw(
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

    inline void deposit(
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

    inline void printTotalBalances(
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

    inline OwnerAccount findAccount(
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

    inline AdminAccount findAccount(
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

    inline void readIdentifierNumber(
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
                identifierNumber != findClientAccountByIdentifierNumber(
                    false,
                    identifierNumber
                ).identifierNumber
            );
    }
}