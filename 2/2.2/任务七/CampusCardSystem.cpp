#include "card_operations.h"      // 调用模块接口
#include <iostream>
using namespace std;

int main() {
    title("Campus Card System");

    int n;
    cin >> n;

    Card* arr = createCards(n);
    inputCards(arr, n);
    printReport(arr, n);

    showBalance(arr[0]);
    deposit(arr[0], 100.0);
    spend(arr[0], 20.0, "Book");
    printReport(arr, n);

    destroyCards(arr);
    arr = nullptr;
    return 0;
}
