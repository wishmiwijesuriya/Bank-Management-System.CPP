#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Class to store bank account details
class BankAccount {
public:
    int accountNumber;
    string holderName;
    double balance;

    // Function to input details for a new account
    void createAccount() {
        cout<<"\nEnter Account Number: ";
        cin>>accountNumber;
        cout<<"Enter Account Holder Name: ";
        cin.ignore(); // To clear the input buffer
        getline(cin,holderName);
        cout<<"Enter Initial Deposit Amount: ";
        cin>>balance;
        cout<<"\nAccount Created Successfully!";
    }

    // Function to display details of an account
    void displayAccount() {
        cout<<"\nAccount No   : "<<accountNumber;
        cout<<"\nHolder Name  : "<<holderName;
        cout<<"\nYour Balance : $"<<balance<<endl;
    }
};

// Main function containing the program logic
int main() {
    int choice;
    BankAccount account; // Object of BankAccount class

    do {
        system("cls"); // Clears the console screen for a clean UI
        cout<<"\n=================================";
        cout<<"\n      SIMPLE BANKING SYSTEM      ";
        cout<<"\n=================================";
        cout<<"\n 1. Create New Account";
        cout<<"\n 2. Deposit Money";
        cout<<"\n 3. Withdraw Money";
        cout<<"\n 4. Check Balance";
        cout<<"\n 5. Exit";
        cout<<"\n=================================";
        cout<<"\nEnter your choice (1-5): ";
        cin>>choice;

        switch(choice) {
            case 1: {
                // Open file in append mode to add data without deleting old data
                ofstream outFile("bank_data.txt",ios::app);
                
                account.createAccount();
                
                // Writing data to the text file line by line
                outFile<<account.accountNumber<<endl;
                outFile<<account.holderName<<endl;
                outFile<<account.balance<<endl;
                
                outFile.close(); // Always close the file after use
                break;
            }
            case 2: {
                int accNo;
                double amount;
                cout<<"\nEnter Account Number: ";
                cin>>accNo;
                
                ifstream inFile("bank_data.txt");   // To read existing records
                ofstream tempFile("temp.txt");       // Temporary file to update records
                bool found=false;

                // Loop through the file to find the matching account number
                while(inFile>>account.accountNumber) {
                    inFile.ignore();
                    getline(inFile,account.holderName);
                    inFile>>account.balance;

                    // If account number matches, update the balance
                    if(account.accountNumber==accNo) {
                        cout<<"\nEnter Deposit Amount: ";
                        cin>>amount;
                        account.balance+=amount; // Add deposit amount to balance
                        found=true;
                        cout<<"\nAmount Deposited Successfully!";
                    }
                    // Copy all records (updated or untouched) to the temp file
                    tempFile<<account.accountNumber<<endl;
                    tempFile<<account.holderName<<endl;
                    tempFile<<account.balance<<endl;
                }
                inFile.close();
                tempFile.close();
                
                // Replace old data file with the updated temp file
                remove("bank_data.txt");
                rename("temp.txt","bank_data.txt");

                if(!found) cout<<"\nAccount Not Found!";
                break;
            }
            case 3: {
                int accNo;
                double amount;
                cout<<"\nEnter Account Number: ";
                cin>>accNo;

                ifstream inFile("bank_data.txt");
                ofstream tempFile("temp.txt");
                bool found=false;

                // Loop through the file to find the account for withdrawal
                while(inFile>>account.accountNumber) {
                    inFile.ignore();
                    getline(inFile,account.holderName);
                    inFile>>account.balance;

                    if(account.accountNumber==accNo) {
                        cout<<"\nEnter Withdrawal Amount: ";
                        cin>>amount;
                        
                        // Check if account has enough money
                        if(amount<=account.balance) {
                            account.balance-=amount; // Deduct money
                            cout<<"\nMoney Withdrawn Successfully!";
                        } else {
                            cout<<"\nInsufficient Balance!";
                        }
                        found=true;
                    }
                    tempFile<<account.accountNumber<<endl;
                    tempFile<<account.holderName<<endl;
                    tempFile<<account.balance<<endl;
                }
                inFile.close();
                tempFile.close();
                
                // Update file changes
                remove("bank_data.txt");
                rename("temp.txt","bank_data.txt");

                if(!found) cout<<"\nAccount Not Found!";
                break;
            }
            case 4: {
                int accNo;
                cout<<"\nEnter Account Number: ";
                cin>>accNo;

                ifstream inFile("bank_data.txt");
                bool found=false;

                // Search file to display specific account balance
                while(inFile>>account.accountNumber) {
                    inFile.ignore();
                    getline(inFile,account.holderName);
                    inFile>>account.balance;

                    if(account.accountNumber==accNo) {
                        account.displayAccount();
                        found=true;
                        break;
                    }
                }
                inFile.close();
                if(!found) cout<<"\nAccount Not Found!";
                break;
            }
            case 5:
                cout<<"\nThank you for using our Banking System!";
                break;
            default:
                cout<<"\nInvalid Choice!";
        }
        
        // Code to pause the screen until user hits Enter
        cout<<"\n\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        
    } while(choice!=5); // Loop runs until user chooses option 5 (Exit)

    return 0;
}
