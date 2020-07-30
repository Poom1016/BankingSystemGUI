#include "BankAccount.h"
#include <map>
#include <string>

struct System {
    System();
    BankAccount OpenAccount(std::string FName, std::string LName, float Balance);
    BankAccount BalanceEnquiry(long AccountNumber);
    BankAccount Deposit(long AccountNumber, float Amount);
    BankAccount Withdraw(long AccountNumber, float Amount);
    void CloseAccount(long AccountNumber);
    void ShowAllAccounts();
    ~System();
private:
    std::map<long, BankAccount> AccountArr;
};