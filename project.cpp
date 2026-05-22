#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Student {
    int id;
    string name;
    int age;
    string address;
    string contactNo;
    string mailID;
    string parentName;
    string parentContact;
};

struct Professor {
    int id;
    string name;
    int age;
    string department;
    string contactNo;
    string mailID;
};

void addStudent() {
    Student s;
    cout << "Enter ID: ";
    cin >> s.id;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Enter Age: ";
    cin >> s.age;
    cin.ignore();
    cout << "Enter Address: ";
    getline(cin, s.address);
    cout << "Enter Contact No: ";
    getline(cin, s.contactNo);
    cout << "Enter Mail ID: ";
    getline(cin, s.mailID);
    cout << "Enter Parent Name: ";
    getline(cin, s.parentName);
    cout << "Enter Parent Contact No: ";
    getline(cin, s.parentContact);

    ofstream file("students.txt", ios::app); // append mode
    file << s.id << "," << s.name << "," << s.age << "," 
         << s.address << "," << s.contactNo << "," 
         << s.mailID << "," << s.parentName << "," 
         << s.parentContact << endl;
    file.close();
    cout << "Student added successfully!\n";
}

#include <iomanip>

void displayStudents() {
    ifstream file("students.txt");
    if (!file) {
        cout << "No student records found.\n";
        return;
    }

    vector<vector<string>> records;
    string line;

    // Column headers
    vector<string> headers = {"ID", "Name", "Age", "Address", "Contact", "Mail ID", "Parent Name", "Parent Contact"};
    size_t expectedCols = headers.size();

    // Read all records
    while (getline(file, line)) {
        vector<string> fields;
        size_t start = 0, end;
        while ((end = line.find(',', start)) != string::npos) {
            fields.push_back(line.substr(start, end - start));
            start = end + 1;
        }
        fields.push_back(line.substr(start));

        // 🔹 Ensure record has same number of columns as headers
        while (fields.size() < expectedCols) fields.push_back(""); // fill missing
        if (fields.size() > expectedCols) fields.resize(expectedCols); // trim extra

        records.push_back(fields);
    }
    file.close();

    if (records.empty()) {
        cout << "No student records found.\n";
        return;
    }

    // Find max width for each column
    vector<int> colWidth(headers.size(), 0);
    for (size_t i = 0; i < headers.size(); i++) {
        colWidth[i] = headers[i].size();
        for (auto &rec : records) {
            colWidth[i] = max(colWidth[i], (int)rec[i].size());
        }
        colWidth[i] += 2; // padding
    }

    auto printSeparator = [&]() {
        cout << "+";
        for (size_t i = 0; i < headers.size(); i++) {
            cout << string(colWidth[i], '-') << "+";
        }
        cout << endl;
    };

    // Print header
    cout << "\n--- Student Records ---\n";
    printSeparator();
    cout << "|";
    for (size_t i = 0; i < headers.size(); i++) {
        cout << left << setw(colWidth[i]) << headers[i] << "|";
    }
    cout << endl;
    printSeparator();

    // Print records
    for (auto &rec : records) {
        cout << "|";
        for (size_t i = 0; i < headers.size(); i++) {
            cout << left << setw(colWidth[i]) << rec[i] << "|";
        }
        cout << endl;
    }
    printSeparator();
}

void searchStudent() {
    int searchId;
    cout << "Enter ID to search: ";
    cin >> searchId;

    ifstream file("students.txt");
    if (!file) {
        cout << "No student records found.\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        vector<string> fields;
        size_t start = 0, end;
        while ((end = line.find(',', start)) != string::npos) {
            fields.push_back(line.substr(start, end - start));
            start = end + 1;
        }
        fields.push_back(line.substr(start));

        int id = stoi(fields[0]);
        if (id == searchId) {
            cout << "\n--- Student Found ---\n";
            cout << "ID: " << fields[0] 
                 << " | Name: " << fields[1] 
                 << " | Age: " << fields[2] 
                 << " | Address: " << fields[3] 
                 << " | Contact: " << fields[4] 
                 << " | Mail: " << fields[5] 
                 << " | Parent Name: " << fields[6] 
                 << " | Parent Contact: " << fields[7] << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Student with ID " << searchId << " not found.\n";
    }
    file.close();
}

void deleteStudentById() {
    int deleteId;
    cout << "Enter ID to delete: ";
    cin >> deleteId;

    ifstream file("students.txt");
    if (!file) {
        cout << "No student records found.\n";
        return;
    }

    vector<string> records;
    string line;
    bool deleted = false;

    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        int id = stoi(line.substr(0, pos1));

        if (id == deleteId) {
            deleted = true; // skip this record
        } else {
            records.push_back(line);
        }
    }
    file.close();

    ofstream outFile("students.txt", ios::trunc);
    for (const string &rec : records) {
        outFile << rec << endl;
    }
    outFile.close();

    if (deleted)
        cout << "Student with ID " << deleteId << " deleted successfully!\n";
    else
        cout << "Student with ID " << deleteId << " not found.\n";
}

void addProfessor() {
    Professor p;
    cout << "Enter ID: ";
    cin >> p.id;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Enter Age: ";
    cin >> p.age;
    cin.ignore();
    cout << "Enter Department: ";
    getline(cin, p.department);
    cout << "Enter Contact No: ";
    getline(cin, p.contactNo);
    cout << "Enter Mail ID: ";
    getline(cin, p.mailID);

    ofstream file("professors.txt", ios::app);
    file << p.id << "," << p.name << "," << p.age << ","
         << p.department << "," << p.contactNo << ","
         << p.mailID << endl;
    file.close();
    cout << "Professor added successfully!\n";
}

void displayProfessors() {
    ifstream file("professors.txt");
    if (!file) {
        cout << "No professor records found.\n";
        return;
    }

    vector<vector<string>> records;
    string line;

    while (getline(file, line)) {
        vector<string> fields;
        size_t start = 0, end;
        while ((end = line.find(',', start)) != string::npos) {
            fields.push_back(line.substr(start, end - start));
            start = end + 1;
        }
        fields.push_back(line.substr(start));
        records.push_back(fields);
    }
    file.close();

    if (records.empty()) {
        cout << "No professor records found.\n";
        return;
    }

    vector<string> headers = {"ID", "Name", "Age", "Department", "Contact", "Mail ID"};
    vector<int> colWidth(headers.size(), 0);

    for (size_t i = 0; i < headers.size(); i++) {
        colWidth[i] = headers[i].size();
        for (auto &rec : records) {
            if (i < rec.size()) {
                colWidth[i] = max(colWidth[i], (int)rec[i].size());
            }
        }
        colWidth[i] += 2;
    }

    auto printSeparator = [&]() {
        cout << "+";
        for (size_t i = 0; i < headers.size(); i++) {
            cout << string(colWidth[i], '-') << "+";
        }
        cout << endl;
    };

    cout << "\n--- Professor Records ---\n";
    printSeparator();
    cout << "|";
    for (size_t i = 0; i < headers.size(); i++) {
        cout << left << setw(colWidth[i]) << headers[i] << "|";
    }
    cout << endl;
    printSeparator();

    for (auto &rec : records) {
        cout << "|";
        for (size_t i = 0; i < rec.size(); i++) {
            cout << left << setw(colWidth[i]) << rec[i] << "|";
        }
        cout << endl;
    }
    printSeparator();
}

void searchProfessor() {
    int searchId;
    cout << "Enter ID to search: ";
    cin >> searchId;

    ifstream file("professors.txt");
    if (!file) {
        cout << "No professor records found.\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        vector<string> fields;
        size_t start = 0, end;
        while ((end = line.find(',', start)) != string::npos) {
            fields.push_back(line.substr(start, end - start));
            start = end + 1;
        }
        fields.push_back(line.substr(start));

        int id = stoi(fields[0]);
        if (id == searchId) {
            cout << "\n--- Professor Found ---\n";
            cout << "ID: " << fields[0]
                 << " | Name: " << fields[1]
                 << " | Age: " << fields[2]
                 << " | Department: " << fields[3]
                 << " | Contact: " << fields[4]
                 << " | Mail: " << fields[5] << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Professor with ID " << searchId << " not found.\n";
    }
    file.close();
}

void deleteProfessorById() {
    int deleteId;
    cout << "Enter ID to delete: ";
    cin >> deleteId;

    ifstream file("professors.txt");
    if (!file) {
        cout << "No professor records found.\n";
        return;
    }

    vector<string> records;
    string line;
    bool deleted = false;

    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        int id = stoi(line.substr(0, pos1));

        if (id == deleteId) {
            deleted = true;
        } else {
            records.push_back(line);
        }
    }
    file.close();

    ofstream outFile("professors.txt", ios::trunc);
    for (const string &rec : records) {
        outFile << rec << endl;
    }
    outFile.close();

    if (deleted)
        cout << "Professor with ID " << deleteId << " deleted successfully!\n";
    else
        cout << "Professor with ID " << deleteId << " not found.\n";
}

int main() {
        int choice;
        do {
            cout << "\n--- Professor Menu ---\n";
            cout << "1. Add Professor\n2. Display Professors\n3. Search Professor\n4. Delete All Professors\n5. Delete Specific Professor\n6. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addProfessor(); break;
                case 2: displayProfessors(); break;
                case 3: searchProfessor(); break;
                case 4: { ofstream file("professors.txt", ios::trunc); file.close(); cout << "All professor records deleted!\n"; break; }
                case 5: deleteProfessorById(); break;
                case 6: cout << "Exiting Professor Menu...\n"; break;
                default: cout << "Invalid choice!\n";
            }
        } while (choice != 6);
        return 0;
    }