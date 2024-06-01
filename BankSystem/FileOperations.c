#include <stdio.h>
#include "AccountManager.h"
#include "FileOperations.h"

void addAccount(BankAccountList *list, BankAccount account) {
    if (list->size >= list->capacity) {
        size_t newCapacity = (list->capacity == 0) ? 1 : list->capacity * 2;
        BankAccount *newBlock = realloc(list->accounts, newCapacity * sizeof(BankAccount));
        if (newBlock == NULL) {
            perror("Failed to allocate memory for accounts");
            exit(EXIT_FAILURE);
        }
        list->accounts = newBlock;
        list->capacity = newCapacity;
    }
    list->accounts[list->size++] = account;
}

void saveAccounts(const BankAccountList *list) {
    FILE *file = fopen("accounts.dat", "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    fwrite(list->accounts, sizeof(BankAccount), list->size, file);
    fclose(file);
}

void loadAccounts(BankAccountList *list) {
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        perror("Unable to read file");
        return;
    }

    BankAccount account;
    while (fread(&account, sizeof(account), 1, file) == 1) {
        addAccount(list, account);
    }
    fclose(file);
}

void loadAccountsFromTextFile(BankAccountList *list) {
    FILE *file = fopen("accounts.txt", "r");
    if (!file) {
        perror("Debug - Failed to open accounts.txt for reading");
        printf("Debug - No existing accounts file found. Starting with an empty account list.\n");
        return;
    }
    printf("Debug - accounts.txt opened successfully for reading.\n");

    BankAccount account;
    while (fscanf(file, "%99[^,],%d,%lf", account.name, &account.accountNumber, &account.balance) == 3) {
        addAccount(list, account);
    }
    fclose(file);
    printf("Debug - Finished loading accounts from text file.\n");
}

void saveAccountsToTextFile(const BankAccountList *list) {
    FILE *file = fopen("accounts.txt", "w");
    if (!file) {
        perror("Debug - Failed to open accounts.txt for writing");
        return;
    }
    printf("Debug - accounts.txt opened successfully for writing.\n");
    
    for (int i = 0; i < list->size; i++) {
        fprintf(file, "%s,%d,%.2f\n", list->accounts[i].name, list->accounts[i].accountNumber, list->accounts[i].balance);
    }
    fclose(file);
    printf("Debug - Accounts successfully saved to text file.\n");
}





