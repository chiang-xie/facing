#ifndef CARD_OPERATIONS_H          // 防止头文件被重复包含
#define CARD_OPERATIONS_H

#include <string>

// ---- 系统常量 ----
const double FEE_RATE        = 0.02;
const double WARNING_BALANCE = 10.0;

// ---- 账户数据结构 ----
struct Card {
    int    id;
    std::string name;
    double balance;
    int    transactions;
};

// ---- 函数声明（只有声明，无定义）----
void printLine(char c = '-', int len = 60);
void title(const std::string& s);

Card* createCards(int n);
void  destroyCards(Card* p);
void  inputCards(Card* arr, int n);
void  outputCards(const Card* arr, int n);
void  printReport(const Card* arr, int n);

void deposit(Card& c, double amount, double fee = FEE_RATE);
bool spend(Card& c, double cost);
bool spend(Card& c, double cost, const std::string& item);
void showBalance(const Card& c);
void viewStudentID(const Card* p);

int  toCent(double amount);

#endif // CARD_OPERATIONS_H
