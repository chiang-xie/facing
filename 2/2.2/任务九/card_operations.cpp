#include "card_operations.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <limits>
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
    if (n <= 0) throw invalid_argument("account count must be positive");
    return new Card[n];          // 内存不足时 new 抛 std::bad_alloc
}

void destroyCards(Card* p) {
    delete[] p;
}

// 格式错误或负数余额 -> 抛异常 -> 本函数捕获并提示重新输入
void inputCards(Card* arr, int n) {
    for (int i = 0; i < n; ++i) {
        while (true) {
            try {
                cout << "Student " << i + 1 << " (id name balance): ";
                int id;
                string name;
                double balance;

                if (!(cin >> id >> name >> balance)) {     // 非法字符/类型不匹配
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (cin.eof()) {
                        cout << "Input ended, stop reading.\n";
                        return;
                    }
                    throw runtime_error("invalid input format");
                }
                if (balance < 0) {                         // 负数余额
                    throw invalid_argument("balance cannot be negative");
                }

                arr[i].id = id;
                arr[i].name = name;
                arr[i].balance = balance;
                arr[i].transactions = 0;
                break;
            } catch (const exception& e) {
                cout << "Input error: " << e.what() << ". Please re-enter.\n";
            }
        }
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
    if (amount <= 0) throw invalid_argument("deposit amount must be positive");
    double real = amount * (1.0 - fee);
    c.balance += real;
    c.transactions++;
    cout << fixed << setprecision(2)
         << "Deposit " << amount << ", fee " << amount * fee
         << ", credited " << real << ", balance " << c.balance << '\n';
}

bool spend(Card& c, double cost) {
    if (cost < 0) {                              // 消费金额为负
        throw invalid_argument("spend amount cannot be negative");
    }
    if (cost > c.balance) {                      // 超过余额
        throw runtime_error("insufficient balance");
    }
    c.balance -= cost;
    c.transactions++;
    cout << fixed << setprecision(2)
         << "Spend " << cost << ", balance " << c.balance << '\n';
    return true;
}

bool spend(Card& c, double cost, const string& item) {
    cout << "Item: " << item << '\n';
    return spend(c, cost);                       // 异常向上传递
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
