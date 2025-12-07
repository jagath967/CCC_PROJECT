#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

// ----------------------------------------------
// Patient Class
// ----------------------------------------------
class Patient {
public:
    string name;
    int priority;  // 1 = Emergency, 2 = Normal, 3 = Regular

    Patient(string n, int p) {
        name = n;
        priority = p;
    }
};

// ----------------------------------------------
// Hospital Class
// ----------------------------------------------
class Hospital {
private:
    vector<Patient> patients; // store patient list

public:
    // Add patient to vector
    void addPatient() {
        string name;
        int priority;

        cout << "\nEnter patient name: ";
        cin >> name;

        cout << "Case type:\n";
        cout << "1. Emergency\n";
        cout << "2. Normal\n";
        cout << "3. Regular Check-up\n";
        cout << "Enter priority: ";
        cin >> priority;

        if (priority < 1 || priority > 3) {
            cout << "Invalid priority! Try again.\n";
            return;
        }

        patients.push_back(Patient(name, priority));
        cout << "Patient added successfully!\n";
    }

    // Display all waiting patients
    void showPatients() {
        if (patients.empty()) {
            cout << "\nNo patients waiting.\n";
            return;
        }

        cout << "\n--- Waiting Patients ---\n";
        for (auto &p : patients) {
            cout << "Name: " << p.name 
                 << " | Priority: " << p.priority << "\n";
        }
    }

    // Sort by priority (1 -> highest)
    void sortByPriority() {
        sort(patients.begin(), patients.end(),
            [](Patient &a, Patient &b) {
                return a.priority < b.priority;
            }
        );
    }

    // Complete checkup (serve highest priority patient)
    void completeCheckup() {
        if (patients.empty()) {
            cout << "\nNo patients to serve.\n";
            return;
        }

        // Sort before serving
        sortByPriority();

        Patient p = patients[0];
        cout << "\nServing Patient: " << p.name
             << " (Priority: " << p.priority << ")\n";

        // Write history to file
        saveToHistory(p);

        // Remove from vector
        patients.erase(patients.begin());

        cout << "Checkup completed. Patient moved to history.\n";
    }

    // Save completed patient to file
    void saveToHistory(Patient p) {
        ofstream file("history.txt", ios::app);
        file << "Name: " << p.name 
             << ", Priority: " << p.priority << "\n";
        file.close();
    }
};

// ----------------------------------------------
// Main Function
// ----------------------------------------------
int main() {
    Hospital h;
    int choice;

    while (true) {
        cout << "\n========= Hospital Emergency Room =========\n";
        cout << "1. Add Patient\n";
        cout << "2. Show Waiting Patients\n";
        cout << "3. Complete Checkup (Serve Next Patient)\n";
        cout << "4. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1: h.addPatient(); break;
            case 2: h.showPatients(); break;
            case 3: h.completeCheckup(); break;
            case 4: 
                cout << "Exiting...\n"; 
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
