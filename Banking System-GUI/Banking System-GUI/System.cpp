#include "System.h"
#include <iostream>

System::System() {
    BankAccount account;
    std::ifstream GetFile;
    GetFile.open("System.data");
    if (!GetFile) {
        return;
    }
    while (!GetFile.eof()) {
        GetFile >> account;
        AccountArr.insert(std::pair<long, BankAccount>(account.GetAccountNumber(), account));
    }
    BankAccount::SetLAccountNumber(account.GetAccountNumber());
    GetFile.close();
}

BankAccount System::OpenAccount(std::string FName, std::string LName, float Balance) {
    std::ofstream ReadFile;
    BankAccount account(FName, LName, Balance);
    AccountArr.insert(std::pair<long, BankAccount>(account.GetAccountNumber(), account));
    ReadFile.open("System.data", std::ios::trunc);
    std::map<long, BankAccount>::iterator Iterator;
    for (Iterator = AccountArr.begin(); Iterator != AccountArr.end(); Iterator++) {
        ReadFile << Iterator->second;
    }
    ReadFile.close();
    return account;
}

BankAccount System::BalanceEnquiry(long AccountNumber) {
    std::map<long, BankAccount>::iterator Iterator = AccountArr.find(AccountNumber);
    return Iterator->second;
}

BankAccount System::Deposit(long AccountNumber, float Amount) {
    std::map<long, BankAccount>::iterator Iterator = AccountArr.find(AccountNumber);
    Iterator->second.Deposit(Amount);
    return Iterator->second;
}

BankAccount System::Withdraw(long AccountNumber, float Amount) {
    std::map<long, BankAccount>::iterator Iterator = AccountArr.find(AccountNumber);
    Iterator->second.Withdraw(Amount);
    return Iterator->second;
}

void System::CloseAccount(long AccountNumber) {
    std::map<long, BankAccount>::iterator Iterator = AccountArr.find(AccountNumber);
    
    AccountArr.erase(AccountNumber);
}

void System::ShowAllAccounts() {
    std::map<long, BankAccount>::iterator Iterator;
    for (Iterator = AccountArr.begin(); Iterator != AccountArr.end(); Iterator++) {
        std::cout << "Account " << Iterator->first << std::endl << Iterator->second << std::endl;
    }
}

System::~System() {
    std::ofstream ReadFile;
    ReadFile.open("System.data", std::ios::trunc);
    std::map<long, BankAccount>::iterator Iterator;
    for (Iterator = AccountArr.begin(); Iterator != AccountArr.end(); Iterator++) {
        ReadFile << Iterator->second;
    }
    ReadFile.close();
}