#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

bool alarmTriggered = false;

void runAlarm() {
    while (!alarmTriggered) {
        this_thread::sleep_for(chrono::seconds(1));
    }

    cout << "Alarm! Time's up." << endl;
}

void setAlarm(int hours, int minutes) {
    time_t now = time(0);
    tm *alarmTimeStruct = localtime(&now);

    alarmTimeStruct->tm_hour = hours;
    alarmTimeStruct->tm_min = minutes;
    alarmTimeStruct->tm_sec = 0;

    time_t alarmTimestamp = mktime(alarmTimeStruct);

    // Create a separate thread to run the alarm
    thread alarmThread(runAlarm);

    while (time(0) < alarmTimestamp) {
        this_thread::sleep_for(chrono::seconds(1));
    }

    alarmTriggered = true;

    // Wait for the alarm thread to finish
    alarmThread.join();
}

time_t startStopwatch() {
    time_t startTime = time(0);
    cout << "Stopwatch started. Press Enter to stop." << endl;
    cin.ignore();
    return time(0) - startTime;
}

void startTimer(int duration) {
    cout << "Timer started for " << duration << " seconds." << endl;
    this_thread::sleep_for(chrono::seconds(duration));
    cout << "Time's up!" << endl;
}

int main() {
    int choice;

    do {
        cout << "1. Set Alarm\n2. Start Stopwatch\n3. Start Timer\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                int hours, minutes;
                cout << "Enter hours and minutes for the alarm: ";
                cin >> hours >> minutes;
                setAlarm(hours, minutes);
                break;
            }

            case 2: {
                time_t elapsedTime = startStopwatch();
                cout << "Stopwatch stopped. Elapsed time: " << elapsedTime << " seconds." << endl;
                break;
            }

            case 3: {
                int duration;
                cout << "Enter the duration for the timer (in seconds): ";
                cin >> duration;
                startTimer(duration);
                break;
            }

            case 4:
                cout << "Exiting the clock application. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 4);

    return 0;
}
