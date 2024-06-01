#include "AccountManager.h"
#include "transaction.h"
#include "FileOperations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main(void) {
    BankAccountList accountList;
    initAccountList(&accountList);
    
    printf("Attempting to load accounts from file...\n");
    loadAccountsFromTextFile(&accountList);
    if (accountList.size > 0) {
        printf("Accounts successfully loaded from file.\n");
    } else {
        printf("No accounts found or file not accessible.\n");
    }
    
    int choice, accountNumber, destAccountNumber;
    int done = 0;
    double transferAmount, depositAmount, withdrawAmount;
    
    while (!done) {
        printf("\nBank Account Management System\n\n");
        printf("1. Display All Accounts\n");
        printf("2. Proceed with an Account\n");
        printf("3. Add a New Account\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                displayAccounts(&accountList);
                break;
            case 2:
                printf("Enter an account number: ");
                scanf("%d", &accountNumber);
                clearInputBuffer();
                int index = -1;
                for (int i = 0; i < accountList.size; i++) {
                    if (accountList.accounts[i].accountNumber == accountNumber) {
                        index = i;
                        break;
                    }
                }
                if (index == -1) {
                    printf("Account not found.\n");
                    continue;
                }
                int transactionDone = 0;
                while (!transactionDone) {
                    printf("\nAccount Menu for #%d\n\n", accountNumber);
                    printf("For Exiting - Please Return to the Main Menu and Press 'Exit'\n");
                    printf("1. Deposit Money\n");
                    printf("2. Withdraw Money\n");
                    printf("3. Transfer Money\n");
                    printf("4. Display the Balance\n");
                    printf("5. Return to Main Menu\n\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    clearInputBuffer();
                    
                    switch (choice) {
                        case 1:
                            printf("Enter amount to deposit: ");
                            if (scanf("%lf", &depositAmount) == 1) {
                                deposit(&accountList.accounts[index], depositAmount);
                                printf("Deposited: $%.2f\n", depositAmount);
                            }
                            clearInputBuffer();
                            break;
                        case 2:
                            printf("Enter amount to withdraw: ");
                            if (scanf("%lf", &withdrawAmount) == 1) {
                                withdraw(&accountList.accounts[index], withdrawAmount);
                                printf("Withdrawn: $%.2f\n", withdrawAmount);
                            }
                            clearInputBuffer();
                            break;
                        case 3:
                            printf("Enter destination account number: ");
                            scanf("%d", &destAccountNumber);
                            clearInputBuffer();
                            printf("Enter amount to transfer: ");
                            if (scanf("%lf", &transferAmount) == 1 && accountList.accounts[index].balance >= transferAmount) {
                                transfer(&accountList.accounts[index], &accountList.accounts[destAccountNumber], transferAmount);
                                printf("Transferred $%.2f from account #%d to account #%d\n", transferAmount, accountNumber, destAccountNumber);
                                printf("New balance: $%.2f\n", accountList.accounts[index].balance);
                            } else {
                                printf("Insufficient funds to perform the transfer or invalid input.\n");
                            }
                            clearInputBuffer();
                            break;
                        case 4:
                            printf("Current balance of account #%d: $%.2f\n", accountNumber, accountList.accounts[index].balance);
                            break;
                        case 5:
                            transactionDone = 1;
                            break;
                        default:
                            printf("Invalid option! Please try again.\n");
                            break;
                    }
                }
                break;
            case 3:
            {
                BankAccount newAccount;
                printf("Enter the new account holder's name: ");
                fgets(newAccount.name, sizeof(newAccount.name), stdin);
                newAccount.name[strcspn(newAccount.name, "\n")] = 0;
                
                printf("Enter a new account number: ");
                if (scanf("%d", &newAccount.accountNumber) == 1) {
                    newAccount.balance = 0;
                    addAccount(&accountList, newAccount);
                    printf("New account added: %s, Account Number: %d, Balance: $%.2f\n", newAccount.name, newAccount.accountNumber, newAccount.balance);
                }
                clearInputBuffer();
            }
                break;
            case 4: // Exit
                done = 1;
                printf("Saving accounts to file...\n");
                saveAccountsToTextFile(&accountList);
                printf("Accounts saved.\n");
                break;
            default:
                printf("Invalid option! Please try again.\n");
                break;
        }
    }
    
    freeAccountList(&accountList);
    
    return 0;
}



