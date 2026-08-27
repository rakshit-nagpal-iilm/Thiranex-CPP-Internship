#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class BankAccount
{
private:
    int accountNumber;
    string customerName;
    string accountType;
    double balance;

public:
    BankAccount()
    {
        accountNumber = 0;
        balance = 0;
    }

    BankAccount(int accNo, string name, string type, double amount)
    {
        accountNumber = accNo;
        customerName = name;
        accountType = type;
        balance = amount;
    }

    int getAccountNumber()
    {
        return accountNumber;
    }

    string getCustomerName()
    {
        return customerName;
    }

    string getAccountType()
    {
        return accountType;
    }

    double getBalance()
    {
        return balance;
    }

    void setBalance(double newBalance)
    {
        balance = newBalance;
    }

    void display()
    {
        cout << "\n-------------------------------\n";
        cout << "Account Number : " << accountNumber << endl;
        cout << "Customer Name  : " << customerName << endl;
        cout << "Account Type   : " << accountType << endl;
        cout << "Balance        : Rs. " << balance << endl;
        cout << "-------------------------------\n";
    }
};


class BankManagement
{
private:
    string fileName = "accounts.txt";

    bool accountExists(int accountNumber)
    {
        ifstream file(fileName);

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string accNo;

            getline(ss, accNo, ',');

            if (stoi(accNo) == accountNumber)
            {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }


    void updateBalance(int accountNumber, double newBalance)
    {
        ifstream file(fileName);
        ofstream tempFile("temp.txt");

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string accNo;
            string name;
            string type;
            string balance;

            getline(ss, accNo, ',');
            getline(ss, name, ',');
            getline(ss, type, ',');
            getline(ss, balance);

            if (stoi(accNo) == accountNumber)
            {
                tempFile << accNo << ","
                         << name << ","
                         << type << ","
                         << newBalance << endl;
            }
            else
            {
                tempFile << line << endl;
            }
        }

        file.close();
        tempFile.close();

        remove(fileName.c_str());
        rename("temp.txt", fileName.c_str());
    }


public:

    void createAccount()
    {
        int accountNumber;
        string name;
        string type;
        double openingBalance;

        cout << "\n===== CREATE ACCOUNT =====\n";

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        if (accountExists(accountNumber))
        {
            cout << "\nAccount already exists.\n";
            return;
        }

        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, name);

        cout << "Enter Account Type (Savings/Current): ";
        getline(cin, type);

        cout << "Enter Opening Balance: ";
        cin >> openingBalance;

        if (openingBalance < 0)
        {
            cout << "\nOpening balance cannot be negative.\n";
            return;
        }

        BankAccount account(
            accountNumber,
            name,
            type,
            openingBalance
        );

        ofstream file(fileName, ios::app);

        file << account.getAccountNumber() << ","
             << account.getCustomerName() << ","
             << account.getAccountType() << ","
             << account.getBalance() << endl;

        file.close();

        cout << "\nAccount created successfully.\n";
    }


    void depositMoney()
    {
        int accountNumber;
        double amount;

        cout << "\n===== DEPOSIT MONEY =====\n";

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        ifstream file(fileName);

        string line;
        bool found = false;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string accNo;
            string name;
            string type;
            string balance;

            getline(ss, accNo, ',');
            getline(ss, name, ',');
            getline(ss, type, ',');
            getline(ss, balance);

            if (stoi(accNo) == accountNumber)
            {
                found = true;

                cout << "Current Balance: Rs. "
                     << stod(balance) << endl;

                cout << "Enter Deposit Amount: ";
                cin >> amount;

                if (amount <= 0)
                {
                    cout << "\nDeposit amount must be greater than zero.\n";
                    file.close();
                    return;
                }

                double newBalance = stod(balance) + amount;

                file.close();

                updateBalance(accountNumber, newBalance);

                cout << "\nDeposit successful.\n";
                cout << "New Balance: Rs. "
                     << newBalance << endl;

                return;
            }
        }

        file.close();

        if (!found)
        {
            cout << "\nAccount not found.\n";
        }
    }


    void withdrawMoney()
    {
        int accountNumber;
        double amount;

        cout << "\n===== WITHDRAW MONEY =====\n";

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        ifstream file(fileName);

        string line;
        bool found = false;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string accNo;
            string name;
            string type;
            string balance;

            getline(ss, accNo, ',');
            getline(ss, name, ',');
            getline(ss, type, ',');
            getline(ss, balance);

            if (stoi(accNo) == accountNumber)
            {
                found = true;

                double currentBalance = stod(balance);

                cout << "Current Balance: Rs. "
                     << currentBalance << endl;

                cout << "Enter Withdrawal Amount: ";
                cin >> amount;

                if (amount <= 0)
                {
                    cout << "\nWithdrawal amount must be greater than zero.\n";
                    file.close();
                    return;
                }

                if (amount > currentBalance)
                {
                    cout << "\nInsufficient balance.\n";
                    file.close();
                    return;
                }

                double newBalance = currentBalance - amount;

                file.close();

                updateBalance(accountNumber, newBalance);

                cout << "\nWithdrawal successful.\n";
                cout << "Remaining Balance: Rs. "
                     << newBalance << endl;

                return;
            }
        }

        file.close();

        if (!found)
        {
            cout << "\nAccount not found.\n";
        }
    }


    void checkBalance()
    {
        int accountNumber;

        cout << "\n===== BALANCE ENQUIRY =====\n";

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        ifstream file(fileName);

        string line;
        bool found = false;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string accNo;
            string name;
            string type;
            string balance;

            getline(ss, accNo, ',');
            getline(ss, name, ',');
            getline(ss, type, ',');
            getline(ss, balance);

            if (stoi(accNo) == accountNumber)
            {
                found = true;

                cout << "\nAccount Holder : "
                     << name << endl;

                cout << "Available Balance : Rs. "
                     << stod(balance) << endl;

                break;
            }
        }

        file.close();

        if (!found)
        {
            cout << "\nAccount not found.\n";
        }
    }


    void displayAccount()
    {
        int accountNumber;

        cout << "\n===== ACCOUNT DETAILS =====\n";

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        ifstream file(fileName);

        string line;
        bool found = false;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string accNo;
            string name;
            string type;
            string balance;

            getline(ss, accNo, ',');
            getline(ss, name, ',');
            getline(ss, type, ',');
            getline(ss, balance);

            if (stoi(accNo) == accountNumber)
            {
                BankAccount account(
                    stoi(accNo),
                    name,
                    type,
                    stod(balance)
                );

                account.display();

                found = true;
                break;
            }
        }

        file.close();

        if (!found)
        {
            cout << "\nAccount not found.\n";
        }
    }


    void displayAllAccounts()
    {
        ifstream file(fileName);

        if (!file)
        {
            cout << "\nNo accounts found.\n";
            return;
        }

        string line;
        bool found = false;

        cout << "\n===== ALL BANK ACCOUNTS =====\n";

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string accNo;
            string name;
            string type;
            string balance;

            getline(ss, accNo, ',');
            getline(ss, name, ',');
            getline(ss, type, ',');
            getline(ss, balance);

            BankAccount account(
                stoi(accNo),
                name,
                type,
                stod(balance)
            );

            account.display();

            found = true;
        }

        file.close();

        if (!found)
        {
            cout << "\nNo accounts available.\n";
        }
    }


    void menu()
    {
        int choice;

        do
        {
            cout << "\n====================================\n";
            cout << "       BANK MANAGEMENT SYSTEM\n";
            cout << "====================================\n";

            cout << "1. Create Account\n";
            cout << "2. Deposit Money\n";
            cout << "3. Withdraw Money\n";
            cout << "4. Check Balance\n";
            cout << "5. View Account Details\n";
            cout << "6. Display All Accounts\n";
            cout << "7. Exit\n";

            cout << "====================================\n";

            cout << "Enter your choice: ";
            cin >> choice;


            switch (choice)
            {
                case 1:
                    createAccount();
                    break;

                case 2:
                    depositMoney();
                    break;

                case 3:
                    withdrawMoney();
                    break;

                case 4:
                    checkBalance();
                    break;

                case 5:
                    displayAccount();
                    break;

                case 6:
                    displayAllAccounts();
                    break;

                case 7:
                    cout << "\nThank you for using the Bank Management System.\n";
                    break;

                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }

        } while (choice != 7);
    }
};


int main()
{
    BankManagement bank;

    bank.menu();

    return 0;
}