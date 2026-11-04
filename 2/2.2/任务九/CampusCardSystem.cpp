#include "card_operations.h"
#include <iostream>
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    title("Campus Card System");

    cout << "Input number of students: ";
    int n;
    if (!(cin >> n)) {
        cout << "Invalid input, program exits.\n";
        return 1;
    }

    // ---- 内存申请异常 ----
    Card* arr = nullptr;
    try {
        arr = createCards(n);
    } catch (const bad_alloc&) {
        cout << "Error: memory allocation failed. Program exits safely.\n";
        return 1;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
        return 1;
    }

    inputCards(arr, n);

    // ---- 交易异常 ----
    try {
        deposit(arr[0], 100.0);
        spend(arr[0], 8.5, "食堂午餐");
    } catch (const exception& e) {
        cout << "Transaction error: " << e.what() << '\n';
    }

    showBalance(arr[0]);
    viewStudentID(&arr[0]);
    cout << "Balance in cent: " << toCent(arr[0].balance) << '\n';

    // ---- 非法消费被拦截 ----
    try { spend(arr[0], -5.0); }
    catch (const exception& e) { cout << "Caught: " << e.what() << '\n'; }

    try { spend(arr[0], 1000000.0); }
    catch (const exception& e) { cout << "Caught: " << e.what() << '\n'; }

    cout << '\n';
    printReport(arr, n);

    destroyCards(arr);
    arr = nullptr;
    return 0;
}
