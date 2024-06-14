#include <string>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

class Transaction {
private:
    int customerId;
    int tellerId;

public:
    Transaction(int customerId, int tellerId) {
        this->customerId = customerId;
        this->tellerId = tellerId;
    }
    
    int getCustomerId() {
        return customerId;
    }
    
    int getTellerId() {
        return tellerId;
    }
    
    virtual string getTransactionDescription() = 0;
};

class Deposit : public Transaction {
private:
    int amount;

public:
    Deposit(int customerId, int tellerId, int amount) : Transaction(customerId, tellerId) {
        this->amount = amount;
    }
    
    string getTransactionDescription() {
        return "Teller " + to_string(getTellerId()) + " deposited " + to_string(amount) + " to account " + to_string(getCustomerId());
    }
};

class Withdrawal : public Transaction {
private:
    int amount;

public:
    Withdrawal(int customerId, int tellerId, int amount) : Transaction(customerId, tellerId) {
        this->amount = amount;
    }

    string getTransactionDescription() {
        return "Teller " + to_string(getTellerId()) + " withdrew " + to_string(amount) + " from account " + to_string(getCustomerId());
    }
};

class OpenAccount : public Transaction {
public:
    OpenAccount(int customerId, int tellerId) : Transaction(customerId, tellerId) {
    }
    
    string getTransactionDescription() {
        return "Teller " + to_string(getTellerId()) + " opened account " + to_string(getCustomerId());
    }
};

class BankTeller {
private:
    int id;

public:
    BankTeller(int id) {
        this->id = id;
    }

    int getId() {
        return id;
    }
};

class BankAccount {
private:
    int customerId;
    string name;
    int balance;

public:
    BankAccount(int customerId, string name, int balance) {
        this->customerId = customerId;
        this->name = name;
        this->balance = balance;
    }

    int getBalance() {
        return this->balance;
    }

    void deposit(int amount) {
        this->balance += amount;
    }

    void withdraw(int amount) {
        this->balance -= amount;
    }
};

class BankSystem {
private:
    vector<BankAccount*> accounts;
    vector<Transaction*> transactions;

public:
    BankSystem(vector<BankAccount*> accounts, vector<Transaction*> transactions) {
        this->accounts = accounts;
        this->transactions = transactions;
    }

    BankAccount* getAccount(int customerId) {
        return this->accounts[customerId];
    }

    vector<BankAccount*> getAccounts() {
        return this->accounts;
    }

    vector<Transaction*> getTransactions() {
        return this->transactions;
    }

    int openAccount(string customerName, int tellerId) {
        // Create account
        int customerId = this->accounts.size();
        BankAccount* account = new BankAccount(customerId, customerName, 0);
        this->accounts.push_back(account);

        // Log transaction
        OpenAccount* transaction = new OpenAccount(customerId, tellerId);
        this->transactions.push_back(transaction);
        return customerId;
    }

    void deposit(int customerId, int tellerId, int amount) {
        BankAccount* account = this->getAccount(customerId);
        account->deposit(amount);

        Deposit* transaction = new Deposit(customerId, tellerId, amount);
        this->transactions.push_back(transaction);
    }

    void withdraw(int customerId, int tellerId, int amount) {
        if (amount > this->getAccount(customerId)->getBalance()) {
            throw "Insufficient funds";
        }
        BankAccount* account = this->getAccount(customerId);
        account->withdraw(amount);

        Withdrawal* transaction = new Withdrawal(customerId, tellerId, amount);
        this->transactions.push_back(transaction);
    }
};

class BankBranch {
private:
    string address;
    int cashOnHand;
    BankSystem* bankSystem;
    vector<BankTeller> tellers;

public:
    BankBranch(string address, int cashOnHand, BankSystem* bankSystem) {
        this->address = address;
        this->cashOnHand = cashOnHand;
        this->bankSystem = bankSystem;
    }

    void addTeller(BankTeller teller) {
        this->tellers.push_back(teller);
    }

    BankTeller getAvailableTeller() {
        int index = (int) round((double) rand() / RAND_MAX * (this->tellers.size() - 1));
        return this->tellers[index];
    }

    int openAccount(string customerName) {
        if (this->tellers.size() == 0) {
            throw "Branch does not have any tellers";
        }
        BankTeller teller = this->getAvailableTeller();
        return this->bankSystem->openAccount(customerName, teller.getId());
    }

    void deposit(int customerId, int amount) {
        if (this->tellers.size() == 0) {
            throw "Branch does not have any tellers";
        }
        BankTeller teller = this->getAvailableTeller();
        this->bankSystem->deposit(customerId, teller.getId(), amount);
    }

    void withdraw(int customerId, int amount) {
        if (amount > this->cashOnHand) {
            throw "Branch does not have enough cash";
        }
        if (this->tellers.size() == 0) {
            throw "Branch does not have any tellers";
        }
        this->cashOnHand -= amount;
        BankTeller teller = this->getAvailableTeller();
        this->bankSystem->withdraw(customerId, teller.getId(), amount);
    }

    int collectCash(double ratio) {
        int cashToCollect = (int) round(this->cashOnHand * ratio);
        this->cashOnHand -= cashToCollect;
        return cashToCollect;
    }

    void provideCash(int amount) {
        this->cashOnHand += amount;
    }
};

class Bank {
private:
    vector<BankBranch> branches;
    BankSystem* bankSystem;
    int totalCash;

public:
    Bank(vector<BankBranch> branches, BankSystem* bankSystem, int totalCash) {
        this->branches = branches;
        this->bankSystem = bankSystem;
        this->totalCash = totalCash;
    }

    BankBranch addBranch(string address, int initialFunds) {
        BankBranch branch(address, initialFunds, this->bankSystem);
        this->branches.push_back(branch);
        return branch;
    }

    void collectCash(double ratio) {
        for (BankBranch branch : this->branches) {
            int cashCollected = branch.collectCash(ratio);
            this->totalCash += cashCollected;
        }
    }

    void printTransactions() {
        for (Transaction* transaction : this->bankSystem->getTransactions()) {
            cout << transaction->getTransactionDescription() << endl;
        }
    }
};

int main() {
    BankSystem bankSystem = BankSystem(vector<BankAccount*>(), vector<Transaction*>());
    Bank bank = Bank(vector<BankBranch>(), &bankSystem, 10000);

    string address = "123 Main St";
    string address2 = "456 Elm St";

    BankBranch branch1 = bank.addBranch(address, 1000);
    BankBranch branch2 = bank.addBranch(address2, 1000);

    branch1.addTeller(BankTeller(1));
    branch1.addTeller(BankTeller(2));
    branch2.addTeller(BankTeller(3));
    branch2.addTeller(BankTeller(4));

    string name1 = "John Doe";
    string name2 = "Bob Smith";
    string name3 = "Jane Doe";

    int customerId1 = branch1.openAccount(name1);
    int customerId2 = branch1.openAccount(name2);
    int customerId3 = branch2.openAccount(name3);

    branch1.deposit(customerId1, 100);
    branch1.deposit(customerId2, 200);
    branch2.deposit(customerId3, 300);

    branch1.withdraw(customerId1, 50);

    bank.printTransactions();
    /*  Possible Output:
        Teller 1 opened account 0
        Teller 2 opened account 1
        Teller 3 opened account 2
        Teller 1 deposited 100 to account 0
        Teller 2 deposited 200 to account 1
        Teller 4 deposited 300 to account 2
        Teller 2 withdrew 50 from account 0
    */

    bank.collectCash(0.5);
}
