#include "system.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <filesystem>
using namespace std;

void bootUp() {
    cout << "Booting up the OS...\n";

    if (!filesystem::exists("system_config.cfg")) {
        cout << "System configuration file not found. Creating default config...\n";
        // You can add code here to create a config file if needed.
    }
    else {
        cout << "System configuration found.\n";
    }

    this_thread::sleep_for(chrono::seconds(2));
    cout << "Boot process complete.\n";
}
