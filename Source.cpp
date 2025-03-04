#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

// Helper function to convert a string to lowercase
string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
        [](unsigned char c) { return tolower(c); });
    return lowerStr;
}

// Function to display the contents of the queue (without modifying it)
void displayQueue(const queue<string>& q) {
    queue<string> tempQueue = q; // Create a copy of the queue
    if (tempQueue.empty()) {
        cout << "Queue is empty." << endl;
        return;
    }
    while (!tempQueue.empty()) {
        cout << tempQueue.front() << endl;
        tempQueue.pop();
    }
}

// Function to search for a value by the given key (case-insensitive)
bool searchQueue(queue<string> q, const string& key) {
    string lowerKey = toLowerCase(key);
    while (!q.empty()) {
        if (toLowerCase(q.front()) == lowerKey) {
            return true;
        }
        q.pop();
    }
    return false;
}

// Function to add a new element at the end of the queue
void addElement(queue<string>& q, const string& element) {
    q.push(element);
}

// Function to add a new element at the beginning of the queue
void addElementAtBeginning(queue<string>& q, const string& element) {
    queue<string> tempQueue;
    tempQueue.push(element);
    while (!q.empty()) {
        tempQueue.push(q.front());
        q.pop();
    }
    q = tempQueue;
}

// Function to add an element after a specified element
void addElementAfter(queue<string>& q, const string& after, const string& element) {
    queue<string> tempQueue;
    bool added = false;
    while (!q.empty()) {
        tempQueue.push(q.front());
        if (q.front() == after && !added) {
            tempQueue.push(element);
            added = true;
        }
        q.pop();
    }
    q = tempQueue;
}

// Function to delete a specified element
void deleteElement(queue<string>& q, const string& element) {
    queue<string> tempQueue;
    while (!q.empty()) {
        if (q.front() != element) {
            tempQueue.push(q.front());
        }
        q.pop();
    }
    q = tempQueue;
}

int main() {
    queue<string> clientsQueue;
    ifstream file("clients.data");

    // Read data from the file into the queue
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            clientsQueue.push(line);
        }
        file.close();
    }
    else {
        cerr << "Unable to open file clients.data" << endl;
        return 1;
    }

    int choice;
    string input, afterElement;

    do {
        cout << "\nQueue Operations Menu:\n";
        cout << "1. Display Queue\n";
        cout << "2. Search for an Element\n";
        cout << "3. Add Element at End\n";
        cout << "4. Add Element at Beginning\n";
        cout << "5. Add Element After Specific Element\n";
        cout << "6. Delete Element\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To handle the newline character from previous input

        switch (choice) {
        case 1: // Display
            cout << "Queue contents:" << endl;
            displayQueue(clientsQueue);
            break;

        case 2: // Search
            cout << "Enter element to search: ";
            getline(cin, input);
            if (searchQueue(clientsQueue, input)) {
                cout << "Element found." << endl;
            }
            else {
                cout << "Element found." << endl;
            }
            break;

        case 3: // Add at end
            cout << "Enter element to add at end: ";
            getline(cin, input);
            addElement(clientsQueue, input);
            cout << "Element added." << endl;
            break;

        case 4: // Add at beginning
            cout << "Enter element to add at beginning: ";
            getline(cin, input);
            addElementAtBeginning(clientsQueue, input);
            cout << "Element added." << endl;
            break;

        case 5: // Add after
            cout << "Enter the element to add after: ";
            getline(cin, afterElement);
            cout << "Enter the new element: ";
            getline(cin, input);
            addElementAfter(clientsQueue, afterElement, input);
            cout << "Element added." << endl;
            break;

        case 6: // Delete
            cout << "Enter element to delete: ";
            getline(cin, input);
            deleteElement(clientsQueue, input);
            cout << "Element deleted if it existed." << endl;
            break;

        case 0: // Exit
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
