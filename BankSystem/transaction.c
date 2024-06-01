#include "transaction.h"
#include <stdio.h>

void deposit(BankAccount *account, double amount) {
    if (amount > 0) {
        account->balance += amount;
    } else {
        printf("Deposit amount must be positive.\n");
    }
}

void withdraw(BankAccount *account, double amount) {
    if (amount > 0 && account->balance >= amount) {
        account->balance -= amount;
    } else {
        printf("Insufficient funds or invalid amount.\n");
    }
}

void transfer(BankAccount *source, BankAccount *destination, double amount) {
    if (amount > 0 && source->balance >= amount) {
        source->balance -= amount;
        destination->balance += amount;
    } else {
        printf("Insufficient funds or invalid amount.\n");
    }
}

