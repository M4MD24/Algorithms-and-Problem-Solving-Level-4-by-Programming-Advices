#pragma once

namespace Options {
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
}