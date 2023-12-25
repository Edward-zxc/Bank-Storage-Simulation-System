//
// Created by zhou with zhu on 2023/12/25.
//
#include <stdio.h>

typedef struct{
    int accountNumber;
    char accountHolder[50];
    double balance;
} Account;

Account accounts[100];
int accountCount = 0;

void showMenu();
void createAccount();
void displayAccountsDetails();
void deposit();
void withdraw();

int main() {
    char choice;
    do {
        showMenu();
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        switch (choice) {
            case '1':
                createAccount();
                break;
            case '2':
                displayAccountsDetails();
                break;
            case '3':
                deposit();
                break;
            case '4':
                withdraw();
                break;
            case '5':
                printf("Thank you for using our service.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != '0');
    return 0;
}

    //Main menu
void showMenu() {
    printf("\n\n");
    printf("1. Create new account\n");
    printf("2. Display account details\n");
    printf("3. Deposit\n");
    printf("4. Withdraw\n");
    printf("5. Exit\n");
}

    //Create new account
    void createAccount() {
        Account account;
        printf("Enter account number: ");
        scanf("%d", &account.accountNumber);
        printf("Enter account holder name: ");
        scanf("%s", account.accountHolder);
        printf("Enter opening balance: ");
        scanf("%lf", &account.balance);
        accounts[accountCount] = account;
        accountCount++;
    }
    //Display account details
    void displayAccountsDetails() {
        int accountNumber;
        printf("Enter account number: ");
        scanf("%d", &accountNumber);
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i].accountNumber == accountNumber) {
                printf("Account Number: %d\n", accounts[i].accountNumber);
                printf("Account Holder Name: %s\n", accounts[i].accountHolder);
                printf("Balance: %.2lf\n", accounts[i].balance);
                return;
            }
        }
        printf("Account not found.\n");
    }
    //deposit
    void deposit() {
        int accountNumber;
        double amount;
        printf("Enter account number: ");
        scanf("%d", &accountNumber);
        printf("Enter amount to deposit: ");
        scanf("%lf", &amount);
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i].accountNumber == accountNumber) {
                accounts[i].balance += amount;
                printf("Deposit successful.\n");
                return;
            }
        }
        printf("Account not found.\n");
    }
    //Withdraw
    void withdraw() {
        int accountNumber;
        double amount;
        printf("Enter account number: ");
        scanf("%d", &accountNumber);
        printf("Enter amount to withdraw: ");
        scanf("%lf", &amount);
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i].accountNumber == accountNumber) {
                if (accounts[i].balance >= amount) {
                    accounts[i].balance -= amount;
                    printf("Withdraw successful.\n");
                    return;
                } else {
                    printf("Insufficient balance.\n");
                    return;
                }
            }
        }
        printf("Account not found.\n");
    }