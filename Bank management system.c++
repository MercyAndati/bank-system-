#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Bank {
    string name1;
    string name2;
    string acc_type;
    string password;
    float balance; 
    int accno;
	float loan_amount;

public:
    void open_account();
    void deposit_money();
    void withdraw_money();
    void display_account();
    void accounts();
    void delete_account();
    void modify_details();
    void apply_loan();
    void repay_loan(); 
};

void Bank::open_account() {
	float loan_amount=0;
	cout << "\t\t\tSet your password: ";
    cin >> password;
    cout << "\n\t\t\tEnter the Account No. : ";
    cin >> accno;
    cout << "\n\n\t\t\tEnter the two Names of the Account holder : ";
	cin>>name1; cin>>name2;
    cout << "What type of account you want to open saving or Current: ";
    cin >> acc_type;
    cout << "Enter How much money you want to deposit: ";
    cin >> balance;

    ofstream outputFile("accounts.txt", ios::app);
    if (outputFile.is_open()) {
        outputFile<< password << " " << accno << " " << name1 << " " << name2 << " " << acc_type << " " << balance << " " << loan_amount << endl;
        outputFile.close();
        cout << "Account Created Successfully" << endl;
    } else {
        cout << "Error opening file. Account creation failed." << endl;
    }
}

void Bank::deposit_money() {
    string input_password;
    cout << "Enter your password for verification: ";
    cin >> input_password;
    ifstream inputFile("accounts.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file. Unable to deposit money." << endl;
        return;
    }
    ofstream outputFile("temp.txt", ios::out);
    bool accountFound = false;
    while (inputFile >> password>> accno >> name1 >>name2 >> acc_type >> balance >> loan_amount ) {
        if (input_password == password) {
            accountFound = true;
            int amount;
            cout << "Enter how much money you want to deposit: ";
            cin >> amount;
            balance += amount;
            cout << "\nAvailable Balance: " << balance;
            outputFile<< password<< " " << accno << " " << name1 << " " << name2 << " "<< acc_type << " " << balance  << " " << loan_amount << endl;
        } else {
            outputFile<< password<< " " << accno << " " << name1 << " " << name2 << " "<< acc_type << " " << balance << " " << loan_amount << endl;
        }
    }
    inputFile.close();
    outputFile.close();
    if (accountFound) {
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
        cout << "\nBalance updated successfully in the file." << endl;
    } else {
        cout << "Password verification failed. Access denied." << endl;
    }
}

void Bank::withdraw_money() {
    string input_password;
    cout << "Enter your password for verification: ";
    cin >> input_password;
    ifstream inputFile("accounts.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file. Unable to withdraw money." << endl;
        return;
    }
    ofstream outputFile("temp.txt", ios::out);
    bool accountFound = false;
    while (inputFile >> password >> accno >> name1 >> name2 >> acc_type >> balance >> loan_amount  ) {
        if (input_password == password) {
            accountFound = true;
            int amount;
            cout << "Enter how much money you want to withdraw: ";
            cin >> amount;
            if (balance < amount) {
                cout << "Insufficient balance. Withdrawal failed." << endl;
            } else {
                balance -= amount;
                cout << "\nAvailable balance: " << balance;
                outputFile << password<< " " << accno << " " << name1 << " " << name2 << " "<< acc_type << " " << balance << " " << loan_amount  << endl;
            }
        } else {
            outputFile << password<< " "  << accno << " " << name1 << " " << name2 << " "<< acc_type << " " << balance << " " << loan_amount  << endl;
        }
    }
    inputFile.close();
    outputFile.close();
    if (accountFound) {
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
        cout << "\nBalance updated successfully in the file." << endl;
    } else {
        cout << "Password verification failed. Access denied." << endl;
    }
}

void Bank::display_account() {
    ifstream inputFile("accounts.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file. Unable to display accounts." << endl;
        return;
    }
    cout << "\nAll Accounts:" << endl;
    string line;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }
    inputFile.close();
}

void Bank::accounts() {
    string input_password;
    cout << "Enter your password for verification: ";
    cin >> input_password;
    ifstream inputFile("accounts.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file. Unable to access account information." << endl;
        return;
    }
    bool accountFound = false;
    while (inputFile >> password>> accno >> name1 >> name2 >> acc_type >> balance >> loan_amount ) {
        if (input_password == password) {
            accountFound = true;
            cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
            cout << "=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=\n";
            cout << "A/c no.\t\t NAMES \t\tType\t\tBalance\tloan\n";
            cout << accno << "\t\t" << " " << name1 << "\t" << name2<< "\t" << acc_type << "\t\t" << balance << "\t" << loan_amount << endl;
            cout << "=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=\n";
            while (inputFile>> password >> accno >> name1 >> name2 >> acc_type >> balance >> loan_amount ) {
                if (accountFound) {
                    break;
                }
                if (accno == this->accno) {
                    accountFound = true;
                    cout << accno << "\t\t" << " " << name1 << "\t" << name2 << "\t"<< "  " << acc_type << "\t" << balance << "\t" << loan_amount << endl;
                }
            }
        }
    }
    inputFile.close();
    if (!accountFound) {
        cout << "Password verification failed. Access denied." << endl;
    }
}

void Bank::delete_account() {
    string input_password;
    cout << "Enter your password for verification: ";
    cin >> input_password;
    ifstream inputFile("accounts.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file. Unable to delete account." << endl;
        return;
    }
    int account_number;
    bool accountDeleted = false;
    cout << "Enter the account number: ";
    cin >> account_number;
    ofstream outputFile("temp.txt", ios::out);
    if (!outputFile.is_open()) {
        cout << "Error creating temporary file. Account deletion failed." << endl;
        inputFile.close();
        return;
    }
    while (inputFile>> password >> accno >> name1 >> name2 >> acc_type >> balance >> loan_amount  ) {
        if (input_password == password) {
            if (account_number == accno) {
                accountDeleted = true;
                cout << "\nAccount deleted successfully." << endl;
            } else {
                outputFile << password<< " " << accno << " " << name1 << " "  << name2 << " " << acc_type << " " << balance << " " << loan_amount  << endl;
            }
        } else {
            outputFile << password << " "  << accno << " " << name1 << " "  << name2 << " " << acc_type << " " << balance << " " << loan_amount << endl;
        }
    }
    inputFile.close();
    outputFile.close();
    if (accountDeleted) {
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    } else {
        cout << "Invalid account number or password. Account not deleted." << endl;
    }
}

void Bank::modify_details() {
    string input_password;
    cout << "Enter your password for verification: ";
    cin >> input_password;
    ifstream inputFile("accounts.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file. Unable to access account information." << endl;
        return;
    }
    ofstream tempFile("temp.txt");
    bool accountFound = false;
    while (inputFile>> password>> accno >> name1 >> name2 >> acc_type >> balance >> loan_amount  ) {
        if (input_password == password) {
            accountFound = true;
            int option;
            cout << "Select the detail you want to modify:" << endl;
            cout << "1. Names" << endl;
            cout << "2. Account Type" << endl;
            cout << "3. Password" << endl;
            cout << "4. Exit" << endl;
            cin >> option;
            switch (option) {
                case 1:
                    cout << "Enter new names: ";
					cin>>name1;
					cin>>name2;
                    break;
                case 2:
                    cout << "Enter new account type for saving or current): ";
                    cin >> acc_type;
                    break;
                case 3:
                    cout << "Enter new password: ";
                    cin >> password;
                    break;
                case 4:
                    cout << "Exiting modification menu." << endl;
                    break;
                default:
                    cout << "Invalid option. Please choose a valid option." << endl;
            }
            tempFile << password << " " << accno << " " << name1 << " "  << name2 << " " << acc_type << " " << balance << " " << loan_amount << endl;
        } else {
            tempFile << password<< " " << accno << " " << name1 << " "  << name2 << " " << acc_type << " " << balance  << " " << loan_amount << endl;
        }
    }
    inputFile.close();
    tempFile.close();
    if (!accountFound) {
        cout << "Password verification failed. Access denied." << endl;
    } else {
        // Replace the original file with the modified file
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
        cout << "Account details updated successfully." << endl;
    }
}

void Bank::apply_loan() {
    string input_password;
    cout << "Enter your password for verification: ";
    cin >> input_password;
    ifstream inputFile("accounts.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file. Unable to withdraw money." << endl;
        return;
    }
    ofstream outputFile("temp.txt", ios::out);
    bool accountFound = false;
    while (inputFile >> password >> accno >> name1 >> name2 >> acc_type >> balance >> loan_amount) {
        if (input_password == password) {
            accountFound = true;
            float loan_amount;
            cout << "Enter the loan amount you want to apply for: ";
            cin >> loan_amount;
            // Add loan amount to balance
            balance += loan_amount;
            // Write updated details to file
            outputFile << password << " " << accno << " " << name1 << " " << name2 << " " << acc_type << " " << balance << " " << loan_amount << endl;
            cout << "Loan applied successfully. Loan amount: " << loan_amount << endl;
        } else {
           outputFile << password << " " << accno << " " << name1 << " " << name2 << " " << acc_type << " " << balance << " " << loan_amount << endl;
        }
    }
    inputFile.close();
    outputFile.close();
    if (!accountFound) {
        cout << "Password verification failed. Access denied." << endl;
    } else {
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    }
}

void Bank::repay_loan() {
    string input_password;
    cout << "Enter your password for verification: ";
    cin >> input_password;
        ifstream inputFile("accounts.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file. Unable to deposit money." << endl;
        return;
    }
    ofstream outputFile("temp.txt", ios::out);
    bool accountFound = false;
    while (inputFile >> password >> accno >> name1 >> name2 >> acc_type >> balance >> loan_amount) {
        if (input_password == password) {
            accountFound = true;
            cout << "Enter the amount you want to repay: ";
            float repayment_amount;
            cin >> repayment_amount;
            if (repayment_amount <= loan_amount) {
                loan_amount -= repayment_amount;
                cout << "Loan repayment successful. Remaining loan amount: " << loan_amount << endl;
                outputFile << password << " " << accno << " " << name1 << " " << name2 << " " << acc_type << " " << balance << " " << loan_amount << endl;
            } else {
                cout<<"Repayment amount exceeds the loan amount. Please enter a valid amount."<<endl;
                outputFile << password << " " << accno << " " << name1 << " " << name2 << " " << acc_type << " " << balance << " " << loan_amount << endl;
            }
        } else {
           outputFile << password << " " << accno << " " << name1 << " " << name2 << " " << acc_type << " " << balance << " " << loan_amount << endl;
        }
    }
    inputFile.close();
    outputFile.close();
    if (!accountFound) {
        cout<<"Password verification failed. Access denied."<<endl;
    } else {
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    }
}

int main() {
    int choice;
    Bank customer;
    do {
        cout << "\n\n\t\t\t\t=*=*=*=*=*=*=*=*=*=*=*=*=\n";
        cout << "\t\t\t\tBANK MANAGEMENT SYSTEM";
        cout << "\n\t\t\t\t=*=*=*=*=*=*=*=*=*=*=*=*=\n";
        cout << "\t\t\t\t ||MAIN MENU||\n";
        cout << "\n\t\t\t\t1. OPEN ACCOUNT";
        cout << "\n\t\t\t\t2. DEPOSIT AMOUNT";
        cout << "\n\t\t\t\t3. WITHDRAW AMOUNT";
        cout << "\n\t\t\t\t4. CHECK BALANCE";
        cout << "\n\t\t\t\t5. USER ACCOUNTS";
        cout << "\n\t\t\t\t6. MODIFY DETAILS";
        cout << "\n\t\t\t\t7. DELETE ACCOUNT";
        cout << "\n\t\t\t\t8. BORROW LOAN";
		cout << "\n\t\t\t\t9. PAY LOAN";
        cout << "\n\t\t\t\t10. EXIT";
        cout << "\n\n\tSelect Your Option (1-10): ";
        cin >> choice;

        switch (choice) {
            case 1:
                customer.open_account();
                break;
            case 2:
                customer.deposit_money();
                break;
            case 3:
                customer.withdraw_money();
                break;
            case 4:
                customer.accounts();
                break;
            case 5:
                customer.display_account();
                break;
            case 6:
                customer.modify_details();
                break;
            case 7:
                customer.delete_account();
                break;
            case 8:
			    customer.apply_loan();
			    break;
			case 9:
			    customer.repay_loan();
			    break;
            case 10:
                cout << "Exit. See you later";
                break;
            default:
                cout << "Invalid choice. Please select again.";
                break;
        }
    } while (choice != 10);
    return 0;
}