//
// Created by zhou with zhu on 2023/12/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct for the linked list
typedef struct Account {
    int accountNumber;
    char accountHolder[50];
    double balance;
    struct Account *next;
} Account;

// Define a global variable to store the head of the linked list
// This variable is accessible from all functions
// The head is the first node of the linked list
Account *head = NULL;

// Function prototypes
void showMenu();
void createAccount();
void displayAccountsDetails();
void displayAccountDetailsByNumber();
void displayAccountDetailsByName();
void deposit();
void withdraw();
void deleteAccount();
void exitProgram();

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
                deleteAccount();
                break;
            case '6':
                exitProgram();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != '0');
    return 0;
}

// Main menu
void showMenu() {
    printf("\n\n");
    printf("1. Create new account\n");
    printf("2. Display account details\n");
    printf("3. Deposit\n");
    printf("4. Withdraw\n");
    printf("5. Delete account\n");
    printf("6. Exit\n");
}
// Create new account
void createAccount() {
    Account *newAccount = (Account *) malloc(sizeof(Account));
    printf("Enter account number: ");
    scanf("%d", &newAccount->accountNumber);
    printf("Enter account holder name: ");
    scanf("%s", newAccount->accountHolder);
    printf("Enter opening balance: ");
    scanf("%lf", &newAccount->balance);
    newAccount->next = NULL;
    if (head == NULL) {
        head = newAccount;
    } else {
        Account *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newAccount;
    }
    printf("Account created successfully.\n");
}
// Display account details
void displayAccountsDetails() {
   if(!head){
       printf("No account found.\n");
       return;
   }
    int choice;
    printf("1. Display all accounts\n");
    printf("2. Display account by account number\n");
    printf("3. Display account by account holder name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            displayAccountsDetails();
            break;
        case 2:
            displayAccountDetailsByNumber();
            break;
        case 3:
            displayAccountDetailsByName();
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}
// Display account details by account number
void displayAccountDetailsByNumber() {
    int accountNumber;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    Account *current = head;
    while (current != NULL) {
        if (current->accountNumber == accountNumber) {
            printf("Account number: %d\n", current->accountNumber);
            printf("Account holder name: %s\n", current->accountHolder);
            printf("Balance: %.2lf\n", current->balance);
            return;
        }
        current = current->next;
    }
    printf("Account not found.\n");
}
// Display account details by account holder name
void displayAccountDetailsByName() {
    char accountHolder[50];
    printf("Enter account holder name: ");
    scanf("%s", accountHolder);
    Account *current = head;
    while (current != NULL) {
        if (strcmp(current->accountHolder, accountHolder) == 0) {
            printf("Account number: %d\n", current->accountNumber);
            printf("Account holder name: %s\n", current->accountHolder);
            printf("Balance: %.2lf\n", current->balance);
            return;
        }
        current = current->next;
    }
    printf("Account not found.\n");
}
// Deposit
void deposit() {
    int accountNumber;
    double amount;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);
    Account *current = head;
    while (current != NULL) {
        if (current->accountNumber == accountNumber) {
            current->balance += amount;
            printf("Deposit successful.\n");
            return;
        }
        current = current->next;
    }
    printf("Account not found.\n");
}
// Withdraw
void withdraw() {
    int accountNumber;
    double amount;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);
    Account *current = head;
    while (current != NULL) {
        if (current->accountNumber == accountNumber) {
            if (current->balance >= amount) {
                current->balance -= amount;
                printf("Withdraw successful.\n");
                return;
            } else {
                printf("Insufficient balance.\n");
                return;
            }
        }
        current = current->next;
    }
    printf("Account not found.\n");
}
// Delete account
void deleteAccount() {
    int accountNumber;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    Account *current = head;
    Account *previous = NULL;
    while (current != NULL) {
        if (current->accountNumber == accountNumber) {
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Account deleted successfully.\n");
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Account not found.\n");
}
// Exit program
void exitProgram() {
    Account *current = head;
    while (current != NULL) {
        Account *temp = current->next;
        free(current);
        current = temp;
    }
    printf("Program terminated.\n");
}
