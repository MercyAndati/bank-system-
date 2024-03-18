Bank management system uig c++ 
This is a simple bank system that demonstrates some basic principles of object-oriented programing principles in c++ such as encapsulation, abstraction and providing a user interaction using a menu driven system.
Abstraction is achieved through the back class where internal details of account management are hidden from the user. The user interacts with the class through well-defined public member functions without the need to know the underlying implementation details.
Encapsulation is demonstrated by the bank class where data members are kept private and accessed or modified only through public member functions. This ensures data integrity and provides control access to the class properties.
The ‘Bank’ class encapsulates the following private data members: 
•	Name1, name2: strings for account holder names
•	Acc_type: string for account type (saving or current)
•	Password: float for account balance
•	Balance: float for account balance
•	Loan_amont: float for loan amount
•	Accno: integer for account number
The class provides the following public member functions
•	Open_account (): opens a new account and stores details in a file
•	Deposit_money (): deposits money into an existing account after password verification. 
•	Withdraw_money (): withdraws money into an existing account
•	Display_account (): displays all accounts stored in the file
•	Accounts (): displays account details for a specific user
•	Delete_account (): deletes an account based on user input
•	Modify_details (): modifies account details like, names, account type or password
•	Apply_loan (): applies for a loan and updates account balance
•	repay_loan (): repays a loan and updates the loan amount
All details are stored to a file account.txt for future reference or retrieval. 


