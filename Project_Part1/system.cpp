#include "system.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <filesystem>
using namespace std;

void bootUp() {
    cout << "Booting up the OS...\n";
    this_thread::sleep_for(chrono::milliseconds(1580));

    cout << "[BOOT] Initializing system... \n";
    this_thread::sleep_for(chrono::milliseconds(120));
    cout << "[BOOT] Performing startup checks... \n";
    this_thread::sleep_for(chrono::milliseconds(250));
    cout << "[BOOT] Checking memory...";
    this_thread::sleep_for(chrono::milliseconds(80));
    cout << " OK \n[BOOT] Checking storage...";
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << " OK \n[BOOT] Verifying boot sector...";
    this_thread::sleep_for(chrono::milliseconds(60));

    cout << " OK \n[LOADER] Loading core system files... \n";
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "[LOADER] Mounting file system... \n";
    this_thread::sleep_for(chrono::milliseconds(140));
    cout << "[LOADER] Configuring system services... \n";
    this_thread::sleep_for(chrono::milliseconds(420));

    cout << "[KERNEL] Starting system processes... \n";
    this_thread::sleep_for(chrono::milliseconds(680));
    cout << "[KERNEL] Initializing drivers... \n";
    this_thread::sleep_for(chrono::milliseconds(900));
    cout << "[KERNEL] Establishing network connection...\n";
    this_thread::sleep_for(chrono::milliseconds(120));

    cout << "[SYSTEM] Launching user interface... \n";
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "[SYSTEM] Finalizing startup... \n";
    this_thread::sleep_for(chrono::milliseconds(600));

    cout << "Boot process complete.\n";
}
