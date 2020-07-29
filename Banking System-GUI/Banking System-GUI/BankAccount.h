#include <string>
#include <fstream>

struct BankAccount {
    BankAccount() : AccountNumber(0), Balance(0) {}
    BankAccount(std::string FName, std::string LName, float Balance);

    long GetAccountNumber() { return AccountNumber; }

    std::string GetFName() { return FirstName; }
    std::string GetLName() { return LastName; }

    float GetBalance() { return Balance; }
    void Deposit(float Amount);
    void Withdraw(float Amount);
    static void SetLAccountNumber(long AccountNumber);
    static long GetLAccountNumber();

    friend std::ofstream& operator<<(std::ofstream& Ofstream, BankAccount& Account);
    friend std::ifstream& operator>>(std::ifstream& Ifstream, BankAccount& Account);
    friend std::ostream& operator<<(std::ostream& Ostream, BankAccount& Account);
private:
    long AccountNumber;
    std::string FirstName;
    std::string LastName;
    float Balance;
    static long NextAccountNumber;
};