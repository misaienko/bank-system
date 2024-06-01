#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include "AccountManager.h"  

void saveAccounts(const BankAccountList *list);
void loadAccounts(BankAccountList *list);
void addAccount(BankAccountList *list, BankAccount account);
void saveAccountsToTextFile(const BankAccountList *list);
void loadAccountsFromTextFile(BankAccountList *list);

#endif


