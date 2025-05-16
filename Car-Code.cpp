#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_CASES = 100;
const int MAX_MANAGERS = 50;

struct Manager {
    int id;
    string name;
};

struct Case {
    int id;
    string title;
    string date;
    string time;
    string source;
    string notes;
    int managerIds[5];
    int managerCount;
};

Manager managers[MAX_MANAGERS];
int managerCount = 0;

Case cases[MAX_CASES];
int caseCount = 0;

bool login() {
    string user, pass;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;
    return (user == "admin" && pass == "1234");
}

// === File Functions ===

void saveManagerToFile(const Manager& m) {
    ofstream file("managers.txt", ios::app);
    if (file) {
        file << m.id << "\n" << m.name << "\n";
    }
    file.close();
}

void saveAllCasesToFile() {
    ofstream file("cases.txt");
    for (int i = 0; i < caseCount; i++) {
        file << cases[i].id << "\n"
             << cases[i].title << "\n"
             << cases[i].date << "\n"
             << cases[i].time << "\n"
             << cases[i].source << "\n"
             << cases[i].notes << "\n"
             << cases[i].managerCount << "\n";
        for (int j = 0; j < cases[i].managerCount; j++) {
            file << cases[i].managerIds[j] << " ";
        }
        file << "\n";
    }
    file.close();
}

void saveCaseToFile(const Case& c) {
    ofstream file("cases.txt", ios::app);
    if (file) {
        file << c.id << "\n"
            << c.title << "\n"
            << c.date << "\n"
            << c.time << "\n"
            << c.source << "\n"
            << c.notes << "\n"
            << c.managerCount << "\n";
        for (int i = 0; i < c.managerCount; i++) {
            file << c.managerIds[i] << " ";
        }
        file << "\n";
    }
    file.close();
}

void loadManagersFromFile() {
    ifstream file("managers.txt");
    if (!file) return;

    while (file >> managers[managerCount].id && managerCount < MAX_MANAGERS) {
        file.ignore();
        getline(file, managers[managerCount].name);
        managerCount++;
    }

    file.close();
}

void loadCasesFromFile() {
    ifstream file("cases.txt");
    if (!file) return;

    while (file >> cases[caseCount].id && caseCount < MAX_CASES) {
        file.ignore();
        getline(file, cases[caseCount].title);
        getline(file, cases[caseCount].date);
        getline(file, cases[caseCount].time);
        getline(file, cases[caseCount].source);
        getline(file, cases[caseCount].notes);
        file >> cases[caseCount].managerCount;
        for (int i = 0; i < cases[caseCount].managerCount; i++) {
            file >> cases[caseCount].managerIds[i];
        }
        string dummy;
        getline(file, dummy); // consume newline
        caseCount++;
    }

    file.close();
}

// === App Functions ===

void viewCases() {
    for (int i = 0; i < caseCount; i++) {
        cout << "Case ID: " << cases[i].id << "\nTitle: " << cases[i].title << "\n";
    }
}

void addCase() {
    if (caseCount >= MAX_CASES) {
        cout << "Case limit reached.\n";
        return;
    }

    Case c;
    cout << "Enter Case ID: ";
    cin >> c.id;
    for (int i = 0; i < caseCount; i++) {
        if (cases[i].id == c.id) {
            cout << "Case ID already exists.\n";
            return;
        }
    }
    cin.ignore();
    cout << "Enter Title: "; getline(cin, c.title);
    cout << "Enter Date: "; getline(cin, c.date);
    cout << "Enter Time: "; getline(cin, c.time);
    cout << "Enter Source: "; getline(cin, c.source);
    cout << "Enter Notes: "; getline(cin, c.notes);
    do {
        cout << "Enter number of managers assigned (0-5): ";
        cin >> c.managerCount;
    } while (c.managerCount < 0 || c.managerCount > 5);

    for (int i = 0; i < c.managerCount; i++) {
        cout << "Enter Manager ID #" << i + 1 << ": ";
        cin >> c.managerIds[i];
    }

    cases[caseCount++] = c;
    saveCaseToFile(c);
}

void editCase() {
    int id;
    cout << "Enter case ID to edit: ";
    cin >> id;
    for (int i = 0; i < caseCount; i++) {
        if (cases[i].id == id) {
            cin.ignore();
            cout << "Enter new title: ";
            getline(cin, cases[i].title);
            cout << "Enter new notes: ";
            getline(cin, cases[i].notes);
            saveAllCasesToFile();
            cout << "Updated.\n";
            return;
        }
    }
    cout << "Case not found.\n";
}

void deleteCase() {
    int id;
    cout << "Enter case ID to delete: ";
    cin >> id;
    for (int i = 0; i < caseCount; i++) {
        if (cases[i].id == id) {
            for (int j = i; j < caseCount - 1; j++) {
                cases[j] = cases[j + 1];
            }
            caseCount--;
            saveAllCasesToFile();
            cout << "Deleted.\n";
            return;
        }
    }
    cout << "Not found.\n";
}

void viewManagers() {
    for (int i = 0; i < managerCount; i++) {
        cout << "Manager ID: " << managers[i].id << " | Name: " << managers[i].name << "\n";
    }
}

void addManager() {
    if (managerCount >= MAX_MANAGERS) {
        cout << "Manager limit reached.\n";
        return;
    }

    Manager m;
    cout << "Enter Manager ID: ";
    cin >> m.id;
    for (int i = 0; i < managerCount; i++) {
        if (managers[i].id == m.id) {
            cout << "Manager ID already exists.\n";
            return;
        }
    }
    cin.ignore();
    cout << "Enter Manager Name: ";
    getline(cin, m.name);
    managers[managerCount++] = m;
    saveManagerToFile(m);
}

void showMenu() {
    int choice;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. View Cases\n";
        cout << "2. Add Case\n";
        cout << "3. Edit Case\n";
        cout << "4. Delete Case\n";
        cout << "5. View Managers\n";
        cout << "6. Add Manager\n";
        cout << "7. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: viewCases(); break;
        case 2: addCase(); break;
        case 3: editCase(); break;
        case 4: deleteCase(); break;
        case 5: viewManagers(); break;
        case 6: addManager(); break;
        case 7: cout << "Logging out...\n"; break;
        default: cout << "Invalid choice.\n"; break;
        }
    } while (choice != 7);
}

int main() {
    loadCasesFromFile();
    loadManagersFromFile();
    while (!login()) {
        cout << "Invalid credentials, try again.\n";
    }
    showMenu();
    return 0;
}