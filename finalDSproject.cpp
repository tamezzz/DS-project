#include <iostream>
#include <string>
#include <iomanip>
#include <stack>
#include <queue>

using namespace std;

struct BankAccount {
    int accountNumber;
    string customerName;
    double balance;
};

struct Node {
    BankAccount account;
    Node* next;
};

const int MAX_ACCOUNTS = 100;
BankAccount accounts[MAX_ACCOUNTS];
int accountCount = 0;
Node* listHead = NULL;

// Stack and Queue
stack<BankAccount> accountStack;
queue<BankAccount> accountQueue;

void showMenu() {
    cout << "\n===== MENU =====\n";
    cout << "1. Insert Account\n";
    cout << "   a. Insert in Sorted Array\n";
    cout << "   b. Insert in Linked List\n";
    cout << "   c. Push to Stack\n";
    cout << "   d. Enqueue to Queue\n";
    cout << "2. Delete Account\n";
    cout << "   a. Delete from Sorted Array\n";
    cout << "   b. Delete from Linked List\n";
    cout << "   c. Pop from Stack\n";
    cout << "   d. Dequeue from Queue\n";
    cout << "3. Search Account\n";
    cout << "   a. Search in Sorted Array\n";
    cout << "   b. Search in Linked List\n";
    cout << "   c. Search in Stack\n";
    cout << "   d. Search in Queue\n";
    cout << "4. Display All Accounts\n";
    cout << "   a. Display Sorted Array\n";
    cout << "   b. Display Linked List\n";
    cout << "   c. Display Stack\n";
    cout << "   d. Display Queue\n";
    cout << "5. Exit\n";
    cout << "Enter your choice (1-5): ";
}

BankAccount getAccountInfo() {
    BankAccount account;

    cout << "Enter Account Number: ";
    cin >> account.accountNumber;

    cin.ignore();

    cout << "Enter Customer Name: ";
    getline(cin, account.customerName);

    cout << "Enter Balance: $";
    cin >> account.balance;

    return account;
}

void showAccount(const BankAccount& account) {
    cout << "Account Number: " << account.accountNumber << endl;
    cout << "Customer Name: " << account.customerName << endl;
    cout << "Balance: $" << fixed << setprecision(2) << account.balance << endl;
}

//array implementation
// array insert
void addToArray() {
    if (accountCount >= MAX_ACCOUNTS) {
        cout << "Error: Cannot add more accounts. Sorted Array is full.\n";
        return;
    }

    BankAccount newAccount = getAccountInfo();

    int position = 0;
    while (position < accountCount && accounts[position].accountNumber < newAccount.accountNumber) {
        position++;
    }

    if (position < accountCount && accounts[position].accountNumber == newAccount.accountNumber) {
        cout << "Error: Account number already exists in Sorted Array.\n";
        return;
    }

    for (int i = accountCount; i > position; i--) {
        accounts[i] = accounts[i-1];
    }

    accounts[position] = newAccount;
    accountCount++;

    cout << "Account added to Sorted Array successfully.\n";
}

//array delete
void removeFromArray() {
    if (accountCount == 0) {
        cout << "Error: No accounts in Sorted Array to remove.\n";
        return;
    }

    int accountNumber;
    cout << "Enter Account Number to delete: ";
    cin >> accountNumber;

    int position = -1;
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            position = i;
            break;
        }
    }

    if (position == -1) {
        cout << "Error: Account not found in Sorted Array.\n";
        return;
    }

    for (int i = position; i < accountCount - 1; i++) {
        accounts[i] = accounts[i+1];
    }

    accountCount--;
    cout << "Account deleted from Sorted Array successfully.\n";
}

//array search
void findInArray() {
    if (accountCount == 0) {
        cout << "Error: No accounts in Sorted Array to search.\n";
        return;
    }

    int accountNumber;
    cout << "Enter Account Number to search: ";
    cin >> accountNumber;

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            cout << "Account found in Sorted Array at position " << i << ":\n";
            showAccount(accounts[i]);
            return;
        }
    }

    cout << "Account not found in Sorted Array.\n";
}
//array display
void showArrayAccounts() {
    if (accountCount == 0) {
        cout << "No accounts in Sorted Array.\n";
        return;
    }

    cout << "\n===== ACCOUNTS IN SORTED ARRAY =====\n";
    cout << left << setw(15) << "Account #" << setw(25) << "Name" << "Balance\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < accountCount; i++) {
        cout << left << setw(15) << accounts[i].accountNumber;
        cout << setw(25) << accounts[i].customerName;
        cout << "$" << fixed << setprecision(2) << accounts[i].balance << endl;
    }
}

//linked list insert
void addToList() {
    BankAccount newAccount = getAccountInfo();

    Node* newNode = new Node;
    newNode->account = newAccount;
    newNode->next = NULL;

    if (listHead == NULL || newAccount.accountNumber < listHead->account.accountNumber) {
        newNode->next = listHead;
        listHead = newNode;
        cout << "Account inserted to list successfully.\n";
        return;
    }

    if (listHead->account.accountNumber == newAccount.accountNumber) {
        cout << "Error: Account number already exists in list.\n";
        delete newNode;
        return;
    }

    Node* current = listHead;
    while (current->next != NULL && current->next->account.accountNumber < newAccount.accountNumber) {
        current = current->next;
    }

    if (current->next != NULL && current->next->account.accountNumber == newAccount.accountNumber) {
        cout << "Error: Account number already exists in list.\n";
        delete newNode;
        return;
    }

    newNode->next = current->next;
    current->next = newNode;

    cout << "Account inserted to list successfully.\n";
}

//linked list delete
void removeFromList() {
    if (listHead == NULL) {
        cout << "Error: No accounts in list to delete.\n";
        return;
    }

    int accountNumber;
    cout << "Enter Account Number to delete: ";
    cin >> accountNumber;

    if (listHead->account.accountNumber == accountNumber) {
        Node* temp = listHead;
        listHead = listHead->next;
        delete temp;
        cout << "Account deleted from list successfully.\n";
        return;
    }

    Node* current = listHead;
    while (current->next != NULL && current->next->account.accountNumber != accountNumber) {
        current = current->next;
    }

    if (current->next == NULL) {
        cout << "Error: Account not found in list.\n";
        return;
    }

    Node* temp = current->next;
    current->next = temp->next;
    delete temp;

    cout << "Account removed from list successfully.\n";
}

//linked list search
void findInList() {
    if (listHead == NULL) {
        cout << "Error: No accounts in list to search.\n";
        return;
    }

    int accountNumber;
    cout << "Enter Account Number to search: ";
    cin >> accountNumber;

    Node* current = listHead;
    int position = 0;

    while (current != NULL) {
        if (current->account.accountNumber == accountNumber) {
            cout << "Account found in list at position " << position << ":\n";
            showAccount(current->account);
            return;
        }
        current = current->next;
        position++;
    }

    cout << "Account not found in list.\n";
}
//linked list display
void showListAccounts() {
    if (listHead == NULL) {
        cout << "No accounts in list.\n";
        return;
    }

    cout << "\n===== ACCOUNTS IN LINKED LIST =====\n";
    cout << left << setw(15) << "Account #" << setw(25) << "Name" << "Balance\n";
    cout << "----------------------------------------\n";

    Node* current = listHead;
    while (current != NULL) {
        cout << left << setw(15) << current->account.accountNumber;
        cout << setw(25) << current->account.customerName;
        cout << "$" << fixed << setprecision(2) << current->account.balance << endl;
        current = current->next;
    }
}

// Stack insert
void pushToStack() {
    BankAccount newAccount = getAccountInfo();
    accountStack.push(newAccount);
    cout << "Account pushed to stack successfully.\n";
}
//stack delete
void popFromStack() {
    if (accountStack.empty()) {
        cout << "Error: Stack is empty.\n";
        return;
    }
    BankAccount topAccount = accountStack.top();
    cout << "Popping account from stack:\n";
    showAccount(topAccount);
    accountStack.pop();
}
//stack search
void findInStack() {
    if (accountStack.empty()) {
        cout << "Error: Stack is empty.\n";
        return;
    }

    int accountNumber;
    cout << "Enter Account Number to search: ";
    cin >> accountNumber;

    stack<BankAccount> tempStack = accountStack;
    int position = 0;
    bool found = false;

    while (!tempStack.empty()) {
        if (tempStack.top().accountNumber == accountNumber) {
            cout << "Account found in stack at position " << position << " (0 = top):\n";
            showAccount(tempStack.top());
            found = true;
            break;
        }
        tempStack.pop();
        position++;
    }

    if (!found) {
        cout << "Account not found in stack.\n";
    }
}
//stack diplay
void showStack() {
    if (accountStack.empty()) {
        cout << "Stack is empty.\n";
        return;
    }

    cout << "\n===== ACCOUNTS IN STACK (Top to Bottom) =====\n";
    cout << left << setw(15) << "Account #" << setw(25) << "Name" << "Balance\n";
    cout << "----------------------------------------\n";

    stack<BankAccount> tempStack = accountStack;

    while (!tempStack.empty()) {
        BankAccount acc = tempStack.top();
        cout << left << setw(15) << acc.accountNumber;
        cout << setw(25) << acc.customerName;
        cout << "$" << fixed << setprecision(2) << acc.balance << endl;
        tempStack.pop();
    }
}

// Queue insert
void enqueueToQueue() {
    BankAccount newAccount = getAccountInfo();
    accountQueue.push(newAccount);
    cout << "Account enqueued successfully.\n";
}

void dequeueFromQueue() {
    if (accountQueue.empty()) {
        cout << "Error: Queue is empty.\n";
        return;
    }
    BankAccount frontAccount = accountQueue.front();
    cout << "Dequeuing account from queue:\n";
    showAccount(frontAccount);
    accountQueue.pop();
}
//queue search
void findInQueue() {
    if (accountQueue.empty()) {
        cout << "Error: Queue is empty.\n";
        return;
    }

    int accountNumber;
    cout << "Enter Account Number to search: ";
    cin >> accountNumber;

    queue<BankAccount> tempQueue = accountQueue;
    int position = 0;
    bool found = false;

    while (!tempQueue.empty()) {
        if (tempQueue.front().accountNumber == accountNumber) {
            cout << "Account found in queue at position " << position << " (0 = front):\n";
            showAccount(tempQueue.front());
            found = true;
            break;
        }
        tempQueue.pop();
        position++;
    }

    if (!found) {
        cout << "Account not found in queue.\n";
    }
}
//queue display
void showQueue() {
    if (accountQueue.empty()) {
        cout << "Queue is empty.\n";
        return;
    }

    cout << "\n===== ACCOUNTS IN QUEUE (Front to Back) =====\n";
    cout << left << setw(15) << "Account #" << setw(25) << "Name" << "Balance\n";
    cout << "----------------------------------------\n";

    queue<BankAccount> tempQueue = accountQueue;

    while (!tempQueue.empty()) {
        BankAccount acc = tempQueue.front();
        cout << left << setw(15) << acc.accountNumber;
        cout << setw(25) << acc.customerName;
        cout << "$" << fixed << setprecision(2) << acc.balance << endl;
        tempQueue.pop();
    }
}

void cleanupList() {
    Node* current = listHead;
    while (current != NULL) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    listHead = NULL;
}

int main() {
    int choice;
    char subChoice;

    cout << "===== BANKING SYSTEM =====\n";

    //array
    accounts[0] = {1001, "John Smith", 5000.00};
    accounts[1] = {1003, "Emily Johnson", 7500.00};
    accounts[2] = {1005, "Michael Brown", 3200.00};
    accountCount = 3;

    // linked list
    Node* node1 = new Node;
    node1->account = {1002, "Sarah Williams", 4200.00};
    node1->next = NULL;
    listHead = node1;

    Node* node2 = new Node;
    node2->account = {1004, "David Miller", 6800.00};
    node2->next = NULL;
    node1->next = node2;

    Node* node3 = new Node;
    node3->account = {1006, "Jessica Davis", 2900.00};
    node3->next = NULL;
    node2->next = node3;

    // stack
    accountStack.push({1007, "Stack User 1", 1000.00});
    accountStack.push({1008, "Stack User 2", 2000.00});

    // queue
    accountQueue.push({1009, "Queue User 1", 3000.00});
    accountQueue.push({1010, "Queue User 2", 4000.00});

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "a. Insert in Sorted Array\n";
                cout << "b. Insert in Linked List\n";
                cout << "c. Push to Stack\n";
                cout << "d. Enqueue to Queue\n";
                cout << "Enter choice (a/b/c/d): ";
                cin >> subChoice;

                if (subChoice == 'a') {
                    addToArray();
                } else if (subChoice == 'b') {
                    addToList();
                } else if (subChoice == 'c') {
                    pushToStack();
                } else if (subChoice == 'd') {
                    enqueueToQueue();
                } else {
                    cout << "Invalid choice.\n";
                }
                break;

            case 2:
                cout << "a. Delete from Sorted Array\n";
                cout << "b. Delete from Linked List\n";
                cout << "c. Pop from Stack\n";
                cout << "d. Dequeue from Queue\n";
                cout << "Enter choice (a/b/c/d): ";
                cin >> subChoice;

                if (subChoice == 'a') {
                    removeFromArray();
                } else if (subChoice == 'b') {
                    removeFromList();
                } else if (subChoice == 'c') {
                    popFromStack();
                } else if (subChoice == 'd') {
                    dequeueFromQueue();
                } else {
                    cout << "Invalid choice.\n";
                }
                break;

            case 3:
                cout << "a. Search in Sorted Array\n";
                cout << "b. Search in Linked List\n";
                cout << "c. Search in Stack\n";
                cout << "d. Search in Queue\n";
                cout << "Enter choice (a/b/c/d): ";
                cin >> subChoice;

                if (subChoice == 'a') {
                    findInArray();
                } else if (subChoice == 'b') {
                    findInList();
                } else if (subChoice == 'c') {
                    findInStack();
                } else if (subChoice == 'd') {
                    findInQueue();
                } else {
                    cout << "Invalid choice.\n";
                }
                break;

            case 4:
                cout << "a. Display Sorted Array\n";
                cout << "b. Display Linked List\n";
                cout << "c. Display Stack\n";
                cout << "d. Display Queue\n";
                cout << "Enter choice (a/b/c/d): ";
                cin >> subChoice;

                if (subChoice == 'a') {
                    showArrayAccounts();
                } else if (subChoice == 'b') {
                    showListAccounts();
                } else if (subChoice == 'c') {
                    showStack();
                } else if (subChoice == 'd') {
                    showQueue();
                } else {
                    cout << "Invalid choice.\n";
                }
                break;

            case 5:
                cout << "Thank you for using the Banking System. Goodbye!\n";
                cleanupList();
                return 0;

            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    }

    return 0;
}

