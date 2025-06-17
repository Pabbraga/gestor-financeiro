#ifndef TRANSACTION_H
#define TRANSACTION_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "transaction_type.c"
    
    struct Transaction {
        int id;
        char name[30];
        int amount;
        enum TransactionType type;
        struct Transaction *next;
    };
    
    void insertTransaction(int id, char *name, int amount, enum TransactionType);
    void showTransaction(struct Transaction *transaction);
    void displayTransactions();
    struct Transaction *searchTransaction(int id);
    void updateTransaction(int id, char *name, int amount, enum TransactionType type, struct Transaction *transactionToUpdate);
    void removeTransaction(int id);

#endif