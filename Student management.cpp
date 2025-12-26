#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Structure to store record details
struct Record {
    int id;
    string name;
    int age;

    // Constructor to initialize a record
    Record(int i, string n, int a) : id(i), name(n), age(a) {}
};

// Database stack
stack<Record> dbStack;

// Function to add a record (PUSH)
void pushRecord(int id, string name, int age) {
    dbStack.push(Record(id, name, age));
    cout << "Record added successfully!" << endl;
}

// Function to remove a record (POP)
void popRecord() {
    if (dbStack.empty()) {
        cout << "Stack is empty! No records to delete." << endl;
        return;
    }
    cout << "Deleting Record: " << dbStack.top().id << " | " << dbStack.top().name << endl;
    dbStack.pop();
}

// Function to display all records
void displayRecords() {
    if (dbStack.empty()) {
        cout << "No records to display!" << endl;
        return;
    }

    stack<Record> tempStack = dbStack;
    cout << "ID\tName\tAge" << endl;
    cout << "------------------------" << endl;
    while (!tempStack.empty()) {
        Record rec = tempStack.top();
        cout << rec.id << "\t" << rec.name << "\t" << rec.age << endl;
        tempStack.pop();
    }
}

// Function to search a record by ID
void searchRecord(int searchId) {
    stack<Record> tempStack = dbStack;
    bool found = false;

    while (!tempStack.empty()) {
        Record rec = tempStack.top();
        if (rec.id == searchId) {
            cout << "Record Found: " << rec.id << " | " << rec.name << " | " << rec.age << endl;
            found = true;
            break;
        }
        tempStack.pop();
    }

    if (!found) {
        cout << "Record not found!" << endl;
    }
}

// Function to update a record by ID
void updateRecord(int updateId, string newName, int newAge) {
    stack<Record> tempStack;
    bool found = false;

    // Move records from dbStack to tempStack, searching for the record to update
    while (!dbStack.empty()) {
        Record rec = dbStack.top();
        dbStack.pop();

        if (rec.id == updateId) {
            cout << "Updating Record: " << rec.id << " | " << rec.name << endl;
            tempStack.push(Record(rec.id, newName, newAge)); // Push updated record to tempStack
            found = true;
        } else {
            tempStack.push(rec); // Push other records to tempStack
        }
    }

    // Move records back from tempStack to dbStack
    while (!tempStack.empty()) {
           dbStack.push(tempStack.top());
        tempStack.pop();
    }

    if (found) {
        cout << "Record updated successfully!" << endl;
    } else {
        cout << "Record not found for update!" << endl;
    }
}


// Main function
int main() {
    int choice, id, age;
    string name;

    while (true) {
        cout << "\n* DBMS using Stack *" << endl;
        cout << "1. Add Record" << endl;
        cout << "2. Delete Record" << endl;
        cout << "3. Display Records" << endl;
        cout << "4. Search Record" << endl;
        cout << "5. Update Record" << endl; // ADDED
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Consume newline character

        switch (choice) {
            case 1:
                cout << "Enter ID: ";
                cin >> id;
                cin.ignore();  // Consume newline character
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                pushRecord(id, name, age);
                break;
            case 2:
                popRecord();
                break;
            case 3:
                displayRecords();
                break;
            case 4:
                cout << "Enter ID to search: ";
                cin >> id;
                searchRecord(id);
                break;
            case 5: {  // ADDED: Update record
                int updateId, newAge;
                string newName;
                cout << "Enter ID of record to update: ";
                cin >> updateId;
                cin.ignore();  // Consume newline character
                cout << "Enter new Name: ";
                getline(cin, newName);
                cout << "Enter new Age: ";
                cin >> newAge;
                updateRecord(updateId, newName, newAge);
                break;
            }
            case 6:
                cout << "Exiting program..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    }
}