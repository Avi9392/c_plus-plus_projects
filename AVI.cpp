// ExpenseManager//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base class for common attributes
class Transaction {
protected:
    int transactionID;
    float amount;
    string date;

public:
    Transaction(int id, float amt, string dt) : transactionID(id), amount(amt), date(dt) {}
    virtual void display() = 0; // Pure virtual function for polymorphism
    virtual ~Transaction() {}

    // Getter function for transactionID
    int getTransactionID() const {
        return transactionID;
    }
};

// Derived class for expenses
class Expense : public Transaction {
private:
    string category;

public:
    Expense(int id, float amt, string dt, string cat) : Transaction(id, amt, dt), category(cat) {}
    void display() override {
        cout << "Expense ID: " << transactionID << " | Category: " << category
             << " | Amount: " << amount << " | Date: " << date << endl;
    }
};

// Derived class for income transactions
class Income : public Transaction {
private:
    string source;

public:
    Income(int id, float amt, string dt, string src) : Transaction(id, amt, dt), source(src) {}
    void display() override {
        cout << "Income ID: " << transactionID << " | Source: " << source
             << " | Amount: " << amount << " | Date: " << date << endl;
    }
};

// Manager class to handle transactions
class ExpenseManager {
private:
    vector<Transaction *> transactions;
    int transactionCounter;

public:
    ExpenseManager() : transactionCounter(0) {}
    ~ExpenseManager() {
        for (Transaction *t : transactions) {
            delete t;
        }
    }
    
    void addExpense() {
        float amount;
        string date, category;
        cout << "Enter amount: ";
        while (!(cin >> amount)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Enter a valid amount: ";
        }
        
        cout << "Enter date (DD/MM/YYYY): ";
        cin >> date;
        
        cout << "Enter category: ";
        cin >> category;
        
        transactions.push_back(new Expense(++transactionCounter, amount, date, category));
        cout << "Expense added successfully!\n";
    }
    
    void addIncome() {
        float amount;
        string date, source;
        cout << "Enter amount: ";
        while (!(cin >> amount)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Enter a valid amount: ";
        }
        
        cout << "Enter date (DD/MM/YYYY): ";
        cin >> date;
        
        cout << "Enter source: ";
        cin >> source;
        
        transactions.push_back(new Income(++transactionCounter, amount, date, source));
        cout << "Income added successfully!\n";
    }
    
    void displayTransactions() {
        cout << "\nTransaction History:\n";
        for (Transaction *t : transactions) {
            t->display();
        }
    }
    
    void deleteTransaction(int id) {
        for (auto it = transactions.begin(); it != transactions.end(); ++it) {
            if ((*it)->getTransactionID() == id) { // Use getter function
                delete *it;
                transactions.erase(it);
                cout << "Transaction deleted successfully!\n";
                return;
            }
        }
        cout << "Transaction not found!\n";
    }
};

int main() {
    ExpenseManager manager;
    int choice, id;
    
    do {
        cout << "\nExpense Tracker Menu:\n";
        cout << "1. Add Expense\n2. Add Income\n3. View Transactions\n4. Delete Transaction\n5. Exit\nEnter your choice: ";
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number: ";
        }
        
        switch (choice) {
            case 1: manager.addExpense(); break;
            case 2: manager.addIncome(); break;
            case 3: manager.displayTransactions(); break;
            case 4: 
                cout << "Enter transaction ID to delete: ";
                while (!(cin >> id)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input! Enter a valid transaction ID: ";
                }
                manager.deleteTransaction(id);
                break;
            case 5: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
    
    return 0;
}







