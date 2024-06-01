#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <stddef.h>  
#include <stdlib.h>

#define INITIAL_SIZE 10

typedef struct {
    char name[100];
    int accountNumber;
    double balance;
} BankAccount;

typedef struct {
    BankAccount *accounts;
    size_t size;
    size_t capacity;
} BankAccountList;

void createAccount(BankAccount *account);
void displayAccount(const BankAccount *account);
void updateAccount(BankAccount *account, double newBalance);
void addAccount(BankAccountList *list, BankAccount account);
void saveAccounts(const BankAccountList *list);
void loadAccounts(BankAccountList *list);

void initAccountList(BankAccountList *list);
void displayAccounts(const BankAccountList *list);
void deleteAccount(BankAccountList *list, int accountNumber);
void updateAccountInList(BankAccountList *list, int accountNumber, double newBalance);
void freeAccountList(BankAccountList *list);

#endif





