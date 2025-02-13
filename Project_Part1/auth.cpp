#include "auth.h"
#include <iostream>
#include <unordered_map>
#include <regex>
#include <functional>
using namespace std;

// For demonstration, we store users in an unordered_map with their hashed passwords.
static unordered_map<string, size_t> users = {
    {"admin", hash<string>{}("password123")}
};


bool authenticateUser() {
    string username;
    string password;

    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);


    auto it = users.find(username);
    if (it != users.end()) {
        size_t inputPasswordHash = hash<string>{}(password);
        if (inputPasswordHash == it->second) {
            cout << "Authentication successful! Welcome, " << username << ".\n";
            return true;
        }
    }
    cout << "Authentication failed for user: " << username << ".\n";
    return false;
}
