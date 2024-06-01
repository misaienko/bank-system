#include "AccountManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createAccount(BankAccount *account) {
    printf("Enter the account holder's name: ");
    fgets(account->name, sizeof(account->name), stdin);
    account->name[strcspn(account->name, "\n")] = 0; 

    printf("Enter the account number: ");
    scanf("%d", &account->accountNumber);

    printf("Enter the initial balance: ");
    scanf("%lf", &account->balance);

    // Clear input buffer
    while (getchar() != '\n');
}

void displayAccount(const BankAccount *account) {
    printf("Account Name: %s\n", account->name);
    printf("Account Number: %d\n", account->accountNumber);
    printf("Balance: $%.2f\n", account->balance);
}

void updateAccount(BankAccount *account, double newBalance) {
    account->balance = newBalance;
    printf("Updated Balance: $%.2f\n", account->balance);
}

void initAccountList(BankAccountList *list) {
    list->accounts = malloc(INITIAL_SIZE * sizeof(BankAccount));
    list->size = 0;
    list->capacity = INITIAL_SIZE;
}

void displayAccounts(const BankAccountList *list) {
    printf("Displaying all accounts:\n");
    for (int i = 0; i < list->size; i++) {
        displayAccount(&list->accounts[i]);
        printf("\n");
    }
}

void deleteAccount(BankAccountList *list, int accountNumber) {
    for (int i = 0; i < list->size; i++) {
        if (list->accounts[i].accountNumber == accountNumber) {
            for (int j = i; j < list->size - 1; j++) {
                list->accounts[j] = list->accounts[j + 1];
            }
            list->size--;
            return;
        }
    }
    printf("Account not found.\n");
}

void updateAccountInList(BankAccountList *list, int accountNumber, double newBalance) {
    for (int i = 0; i < list->size; i++) {
        if (list->accounts[i].accountNumber == accountNumber) {
            updateAccount(&list->accounts[i], newBalance);
            return;
        }
    }
    printf("Account not found.\n");
}

void freeAccountList(BankAccountList *list) {
    free(list->accounts);
}

