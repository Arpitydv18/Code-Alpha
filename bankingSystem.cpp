#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Transaction {
public:
    string accountNo, type;
    double amount;
    void save() {
        ofstream file("transactions.txt", ios::app);
        file << accountNo << " " << type << " " << amount << endl;
    }
};

class Account {
public:
    string accountNo;
    string customerName;
    double balance;

    void createAccount() {
        cout << "Enter Account No: ";
        cin >> accountNo;
        cout << "Enter Customer Name: ";
        cin >> customerName;
        cout << "Enter Initial Balance: ";
        cin >> balance;

        ofstream file("accounts.txt", ios::app);
        file << accountNo << " " << customerName << " " << balance << endl;
        cout << "Account created successfully!\n";
    }

    void deposit(double amt) {
        balance += amt;
        updateAccount();
        Transaction t{accountNo, "Deposit", amt};
        t.save();
        cout << "Deposited " << amt << " successfully.\n";
    }

    void withdraw(double amt) {
        if (amt > balance) {
            cout << "Insufficient balance!\n";
            return;
        }
        balance -= amt;
        updateAccount();
        Transaction t{accountNo, "Withdraw", amt};
        t.save();
        cout << "Withdrawn " << amt << " successfully.\n";
    }

    void updateAccount() {
        ifstream in("accounts.txt");
        vector<string> lines;
        string acc, name;
        double bal;
        while (in >> acc >> name >> bal) {
            if (acc == accountNo) bal = balance;
            lines.push_back(acc + " " + name + " " + to_string(bal));
        }
        in.close();

        ofstream out("accounts.txt");
        for (auto &l : lines) out << l << endl;
    }

    void showTransactions() {
        ifstream file("transactions.txt");
        string acc, type;
        double amt;
        cout << "\nTransactions for Account " << accountNo << ":\n";
        while (file >> acc >> type >> amt) {
            if (acc == accountNo)
                cout << type << " : " << amt << endl;
        }
    }
};

int main() {
    Account acc;
    int choice;
    do {
        cout << "\n1. Create Account\n2. Deposit\n3. Withdraw\n4. View Transactions\n5. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) acc.createAccount();
        else if (choice == 2) {
            string accNo; double amt;
            cout << "Enter Account No: "; cin >> accNo;
            cout << "Enter Amount: "; cin >> amt;
            acc.accountNo = accNo; acc.balance = amt; // Example
            acc.deposit(amt);
        }
        else if (choice == 3) {
            string accNo; double amt;
            cout << "Enter Account No: "; cin >> accNo;
            cout << "Enter Amount: "; cin >> amt;
            acc.accountNo = accNo; acc.balance = amt;
            acc.withdraw(amt);
        }
        else if (choice == 4) {
            string accNo;
            cout << "Enter Account No: "; cin >> accNo;
            acc.accountNo = accNo;
            acc.showTransactions();
        }

    } while (choice != 5);

    return 0;
}
