#pragma once

namespace Constants {
    inline const std::string CLIENT_ACCOUNTS_PATH = "src/_5_projects/_5_1_bank/database/ClientAccounts.txt";
    inline const std::string ADMIN_ACCOUNTS_PATH = "src/_5_projects/_5_1_bank/database/AdminAccounts.txt";
    inline const std::string OWNER_ACCOUNTS_PATH = "src/_5_projects/_5_1_bank/database/OwnerAccounts.txt";

    inline const std::string CLIENT_TABLE_LINE = std::string(
        119,
        '-'
    );
    inline const std::string ADMIN_TABLE_LINE = std::string(
        243,
        '-'
    );
    inline const std::string TOTAL_BALANCES_TABLE_LINE = std::string(
        80,
        '-'
    );

    inline constexpr short BALANCE_PRECISION = 3;
}