#pragma once

using namespace std;

namespace Structure {
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
}