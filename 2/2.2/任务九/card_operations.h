#ifndef CARD_OPERATIONS_H
#define CARD_OPERATIONS_H

#include <string>

const double FEE_RATE        = 0.02;
const double WARNING_BALANCE = 10.0;

struct Card {
    int         id;
    std::string name;
    double      balance;
    int         transactions;
};

void printLine(char c = '-', int len = 60);
void title(const std::string& s);

Card* createCards(int n);              // 抛 std::bad_alloc / std::invalid_argument
void  destroyCards(Card* p);
void  inputCards(Card* arr, int n);    // 内部捕获异常并要求重新输入
void  outputCards(const Card* arr, int n);
void  printReport(const Card* arr, int n);

void deposit(Card& c, double amount, double fee = FEE_RATE);
bool spend(Card& c, double cost);                          // 抛 invalid_argument / runtime_error
bool spend(Card& c, double cost, const std::string& item);
void showBalance(const Card& c);
void viewStudentID(const Card* p);

int toCent(double amount);

#endif // CARD_OPERATIONS_H
