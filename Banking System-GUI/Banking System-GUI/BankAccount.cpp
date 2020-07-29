#include "BankAccount.h"

#define MinBalance 500

struct InsufficientFunds {};

long BankAccount::NextAccountNumber = 0;

BankAccount::BankAccount(std::string FName, std::string LName, float Balance) {
    NextAccountNumber++;
    AccountNumber = NextAccountNumber;
    FirstName = FName;
    LastName = LName;
    this->Balance = Balance;
}

void BankAccount::Deposit(float Amount) {
    Balance += Amount;
}

void BankAccount::Withdraw(float Amount) {
    if (Balance - Amount < MinBalance)
        throw InsufficientFunds();
    Balance -= Amount;
}

void BankAccount::SetLAccountNumber(long AccountNumber) {
    NextAccountNumber = AccountNumber;
}

long BankAccount::GetLAccountNumber() {
    return NextAccountNumber;
}

std::ofstream& operator<<(std::ofstream& Ofstream, BankAccount& Account) {
    Ofstream << Account.AccountNumber << std::endl;
    Ofstream << Account.FirstName << std::endl;
    Ofstream << Account.LastName << std::endl;
    Ofstream << Account.Balance << std::endl;
    return Ofstream;
}

std::ifstream& operator>>(std::ifstream& Ifstream, BankAccount& Account) {
    Ifstream >> Account.AccountNumber;
    Ifstream >> Account.FirstName;
    Ifstream >> Account.LastName;
    Ifstream >> Account.Balance;
    return Ifstream;
}

std::ostream& operator<<(std::ostream& Ostream, BankAccount& Account) {
    Ostream << "First Name:" << Account.GetFName() << std::endl;
    Ostream << "Last Name:" << Account.GetLName() << std::endl;
    Ostream << "Account Number:" << Account.GetAccountNumber() << std::endl;
    Ostream << "Balance:" << Account.GetBalance() << std::endl;
    return Ostream;
}
