#include <iostream>
#include "system.h"
#include "auth.h"
using namespace std;

int main() {
    bootUp();

    if (authenticateUser()) {
        cout << "Access granted. Starting OS...\n";
        // Continue with additional OS simulation functions...
    }
    else {
        cout << "Access denied. Shutting down.\n";
    }
    return 0;
}
