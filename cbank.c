#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 100

typedef struct {
    int accountNumber;
    char name[50];
    float balance;
    int birthYear;
    int birthMonth;
    int birthDay;
    char address[100];
    char postalCode[10];
    char idDocument[20];
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

int calculateAge(int year, int month, int day) {
    int currentYear = 2024, currentMonth = 11, currentDay = 1;
    int age = currentYear - year;
    if (month > currentMonth || (month == currentMonth && day > currentDay)) {
        age--;
    }
    return age;
}

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Account limit reached. Cannot create a new account.\n");
        return;
    }
    
    Account newAccount;
    newAccount.accountNumber = accountCount + 1;

    // Get account holder's name
    printf("Enter account holder's name: ");
    scanf("%s", newAccount.name);

    // Get birthdate and check if age is 18 or older
    printf("Enter birth year (YYYY): ");
    scanf("%d", &newAccount.birthYear);
    printf("Enter birth month (MM): ");
    scanf("%d", &newAccount.birthMonth);
    printf("Enter birth day (DD): ");
    scanf("%d", &newAccount.birthDay);
    
    int age = calculateAge(newAccount.birthYear, newAccount.birthMonth, newAccount.birthDay);
    if (age < 18) {
        printf("Account holder must be at least 18 years old.\n");
        return;
    }

    // Get address and postal code
    printf("Enter address: ");
    scanf(" %[^\n]", newAccount.address);
    printf("Enter postal code: ");
    scanf("%s", newAccount.postalCode);

    // Get ID document type (e.g., Passport or ID)
    printf("Enter ID document type (Passport/ID): ");
    scanf("%s", newAccount.idDocument);

    // Initialize balance
    newAccount.balance = 0.0;

    // Store the new account in the accounts array
    accounts[accountCount++] = newAccount;
    printf("Account created successfully! Account Number: %d\n", newAccount.accountNumber);
}

void deposit() {
    int accNumber;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNumber);
    if (accNumber < 1 || accNumber > accountCount) {
        printf("Invalid account number!\n");
        return;
    }
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf("Error: You must enter a positive amount to deposit.\n");
        return;
    }
    accounts[accNumber - 1].balance += amount;
    printf("Amount deposited successfully! New Balance: %.2f\n", accounts[accNumber - 1].balance);
}

void withdraw() {
    int accNumber;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNumber);
    if (accNumber < 1 || accNumber > accountCount) {
        printf("Invalid account number!\n");
        return;
    }
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf("Error: You must enter a positive amount to withdraw.\n");
        return;
    }
    if (amount > accounts[accNumber - 1].balance) {
        printf("Insufficient balance!\n");
    } else {
        accounts[accNumber - 1].balance -= amount;
        printf("Amount withdrawn successfully! New Balance: %.2f\n", accounts[accNumber - 1].balance);
    }
}

void checkBalance() {
    int accNumber;
    printf("Enter account number: ");
    scanf("%d", &accNumber);
    if (accNumber < 1 || accNumber > accountCount) {
        printf("Invalid account number!\n");
        return;
    }
    printf("Account Balance for %s: %.2f\n", accounts[accNumber - 1].name, accounts[accNumber - 1].balance);
}

void menu() {
    int choice;
    while (1) {
        printf("\nBank System Menu:\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                checkBalance();
                break;
            case 5:
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
