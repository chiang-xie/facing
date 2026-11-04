#include "card_operations.h"      // 包含自己的头文件，让编译器校验声明与定义一致
#include <iostream>
#include <iomanip>
using namespace std;

void printLine(char c, int len) {
    for (int i = 0; i < len; ++i) cout << c;
    cout << '\n';
}

void title(const string& s) {
    const int LEN = 60;
    printLine('=', LEN);
    int pad = (LEN - static_cast<int>(s.size())) / 2;
    if (pad < 0) pad = 0;
    cout << string(pad, ' ') << s << '\n';
    printLine('=', LEN);
}

Card* createCards(int n) {
    return new Card[n];
}

void destroyCards(Card* p) {
    delete[] p;
}

void inputCards(Card* arr, int n) {
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].id >> arr[i].name >> arr[i].balance;
        arr[i].transactions = 0;
    }
}

void outputCards(const Card* arr, int n) {
    cout << left << setw(10) << "ID" << setw(14) << "Name"
         << right << setw(12) << "Balance" << setw(14) << "Transactions" << '\n';
    cout << fixed << setprecision(2);
    for (int i = 0; i < n; ++i) {
        cout << left  << setw(10) << arr[i].id
                      << setw(14) << arr[i].name
             << right << setw(12) << arr[i].balance
                      << setw(14) << arr[i].transactions << '\n';
    }
}

void printReport(const Card* arr, int n) {
    printLine('-', 50);
    cout << left << setw(10) << "ID" << setw(14) << "Name"
         << right << setw(12) << "Balance" << setw(14) << "Transactions" << '\n';
    printLine('-', 50);
    cout << fixed << setprecision(2);
    for (int i = 0; i < n; ++i) {
        cout << left  << setw(10) << arr[i].id
                      << setw(14) << arr[i].name
             << right << setw(12) << arr[i].balance
                      << setw(14) << arr[i].transactions << '\n';
    }
    printLine('-', 50);
}

void deposit(Card& c, double amount, double fee) {
    double real = amount * (1.0 - fee);
    c.balance += real;
    c.transactions++;
    cout << fixed << setprecision(2)
         << "Deposit " << amount << ", fee " << amount * fee
         << ", credited " << real << ", balance " << c.balance << '\n';
}

bool spend(Card& c, double cost) {
    if (c.balance < cost) {
        cout << fixed << setprecision(2)
             << "Spend " << cost << " failed: balance " << c.balance << '\n';
        return false;
    }
    c.balance -= cost;
    c.transactions++;
    return true;
}

bool spend(Card& c, double cost, const string& item) {
    cout << "Item: " << item << '\n';
    return spend(c, cost);
}

void showBalance(const Card& c) {
    cout << fixed << setprecision(2)
         << c.name << " balance = " << c.balance << '\n';
}

void viewStudentID(const Card* p) {
    if (p == nullptr) return;
    cout << "Student ID: " << p->id << '\n';
}

int toCent(double amount) {
    return static_cast<int>(amount * 100.0 + 0.5);
}
