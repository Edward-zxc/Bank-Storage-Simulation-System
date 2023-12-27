#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义用户结构体
typedef struct Node {
    char username[50];
    int account_number;
    double balance;
    char password[20];
    struct Node* next;
} UserNode;

// 全局链表头指针
UserNode* head = NULL;

// 函数声明
void login();
void createNewUser();
void withdraw(UserNode* userNode);
void deposit(UserNode* userNode);
void transfer(UserNode* senderNode);
void displayBalance(UserNode* userNode);
void queryUser();
void userMenu(UserNode* userNode);

// 主函数
int main() {
    int choice;

    while (1) {
        printf("\nBank Management System\n");
        printf("1. Login\n");
        printf("2. Create New User\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                createNewUser();
                break;
            case 3:
                printf("Exiting program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// 登录函数
void login() {
    int loginChoice;
    char username[50];
    int accountNumber;
    char password[20];

    printf("\nLogin Options\n");
    printf("1. Username and Password\n");
    printf("2. Account Number and Password\n");
    printf("Enter your choice: ");
    scanf("%d", &loginChoice);

    if (loginChoice == 1) {
        printf("Enter Username: ");
        scanf("%s", username);
    } else if (loginChoice == 2) {
        printf("Enter Account Number: ");
        scanf("%d", &accountNumber);
    } else {
        printf("Invalid choice. Please try again.\n");
        return;
    }

    printf("Enter Password: ");
    scanf("%s", password);

    UserNode* currentUser = head;

    while (currentUser != NULL) {
        if ((loginChoice == 1 && strcmp(currentUser->username, username) == 0) ||
            (loginChoice == 2 && currentUser->account_number == accountNumber)) {
            if (strcmp(currentUser->password, password) == 0) {
                printf("Login successful. Welcome, %s!\n", currentUser->username);
                // 进入用户操作菜单
                userMenu(currentUser);
                return;
            } else {
                printf("Invalid password.\n");
                return;
            }
        }
        currentUser = currentUser->next;
    }

    printf("Login failed. Invalid username, account number, or password.\n");
}

// 新建用户函数
void createNewUser() {
    UserNode* newUser = (UserNode*)malloc(sizeof(UserNode));

    printf("\nEnter Username: ");
    scanf("%s", newUser->username);
    printf("Enter Account Number: ");
    scanf("%d", &newUser->account_number);
    printf("Enter Initial Balance: ");
    scanf("%lf", &newUser->balance);
    printf("Enter Password: ");
    scanf("%s", newUser->password);

    // 将新用户添加到链表头
    newUser->next = head;
    head = newUser;

    printf("User created successfully. Welcome, %s!\n", newUser->username);
}

// 取钱函数
void withdraw(UserNode* userNode) {
    double amount;

    printf("\nEnter amount to withdraw: ");
    scanf("%lf", &amount);

    if (amount > 0 && amount <= userNode->balance) {
        userNode->balance -= amount;
        printf("Withdrawal successful. Updated balance: %.2f\n", userNode->balance);
    } else {
        printf("Invalid withdrawal amount or insufficient balance.\n");
    }
}

// 存钱函数
void deposit(UserNode* userNode) {
    double amount;

    printf("\nEnter amount to deposit: ");
    scanf("%lf", &amount);

    if (amount > 0) {
        userNode->balance += amount;
        printf("Deposit successful. Updated balance: %.2f\n", userNode->balance);
    } else {
        printf("Invalid deposit amount.\n");
    }
}

// 转账函数
void transfer(UserNode* senderNode) {
    int targetAccountNumber;
    double amount;

    printf("\nEnter target account number: ");
    scanf("%d", &targetAccountNumber);

    UserNode* targetNode = head;

    while (targetNode != NULL) {
        if (targetNode->account_number == targetAccountNumber) {
            printf("Enter amount to transfer: ");
            scanf("%lf", &amount);

            if (amount > 0 && amount <= senderNode->balance) {
                senderNode->balance -= amount;
                targetNode->balance += amount;
                printf("Transfer successful. Updated balance: %.2f\n", senderNode->balance);
            } else {
                printf("Invalid transfer amount or insufficient balance.\n");
            }
            return;
        }
        targetNode = targetNode->next;
    }

    printf("Target account not found.\n");
}

// 查询余额函数
void displayBalance(UserNode* userNode) {
    printf("Current Balance: %.2f\n", userNode->balance);
}

// 查询用户函数
void queryUser() {
    int queryChoice;
    char username[50];
    int accountNumber;
    char password[20];

    printf("\nQuery Options\n");
    printf("1. Query by Username and Password\n");
    printf("2. Query by Account Number and Password\n");
    printf("Enter your choice: ");
    scanf("%d", &queryChoice);

    UserNode* queryUser = NULL;

    if (queryChoice == 1) {
        printf("Enter Username: ");
        scanf("%s", username);
        printf("Enter Password: ");
        scanf("%s", password);

        UserNode* currentUser = head;

        while (currentUser != NULL) {
            if (strcmp(currentUser->username, username) == 0 && strcmp(currentUser->password, password) == 0) {
                queryUser = currentUser;
                break;
            }
            currentUser = currentUser->next;
        }
    } else if (queryChoice == 2) {
        printf("Enter Account Number: ");
        scanf("%d", &accountNumber);
        printf("Enter Password: ");
        scanf("%s", password);

        UserNode* currentUser = head;

        while (currentUser != NULL) {
            if (currentUser->account_number == accountNumber && strcmp(currentUser->password, password) == 0) {
                queryUser = currentUser;
                break;
            }
            currentUser = currentUser->next;
        }
    } else {
        printf("Invalid choice. Please try again.\n");
        return;
    }

    if (queryUser != NULL) {
        printf("Query successful. User Details:\n");
        printf("Username: %s\n", queryUser->username);
        printf("Account Number: %d\n", queryUser->account_number);
        printf("Balance: %.2f\n", queryUser->balance);
    } else {
        printf("User not found.\n");
    }
}

// 用户操作菜单
void userMenu(UserNode* userNode) {
    int choice;

    while (1) {
        printf("\nUser Menu\n");
        printf("1. Withdraw\n");
        printf("2. Deposit\n");
        printf("3. Transfer\n");
        printf("4. Display Balance\n");
        printf("5. Query User\n");
        printf("6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                withdraw(userNode);
                break;
            case 2:
                deposit(userNode);
                break;
            case 3:
                transfer(userNode);
                break;
            case 4:
                displayBalance(userNode);
                break;
            case 5:
                queryUser();
                break;
            case 6:
                printf("Logout successful. Goodbye, %s!\n", userNode->username);
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
