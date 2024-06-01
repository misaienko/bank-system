// transaction.h
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "AccountManager.h"

void deposit(BankAccount *account, double amount);
void withdraw(BankAccount *account, double amount);
void transfer(BankAccount *source, BankAccount *destination, double amount);

#endif 

