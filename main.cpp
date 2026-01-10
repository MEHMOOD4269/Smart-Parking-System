
#include <iostream>
using namespace std;
int main() {
    int choice;
    do {
        cout << "\n--- Smart Parking System ---\n";
        cout << "1. Request Parking\n";
        cout << "2. Cancel Request\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
    } while (choice != 3);  
    return 0;
}
