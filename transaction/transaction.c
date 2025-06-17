#include "transaction.h"

static int balance = 0;
struct Transaction *head = NULL;
struct Transaction *current = NULL;

void insertTransaction(int id, char *name, int amount, enum TransactionType type) {
    struct Transaction *newTransaction = (struct Transaction *)malloc(sizeof(struct Transaction));

    // id generator
    if (head == NULL) {
        id = 1;
    } else {
        id = current->id+1;
    }

    // data insertion
    newTransaction->id = id;
    strcpy(newTransaction->name, name);
    newTransaction->amount = amount;
    newTransaction->type = type;
    newTransaction->next = NULL;

    // balance update
    if (type == PROFIT) {
        balance += amount;
    } else {
        balance -= amount;
    }

    if (head == NULL) {
        // first insertion
        head = newTransaction;
        current = newTransaction;
    } else {
        current->next = newTransaction;
        current = newTransaction;
    }

    printf("\nTransação inserida com sucesso\n");
}

void showTransaction(struct Transaction *transaction) {
    char *color = (transaction->type == EXPENSE) ? "\033[1;31m" : "\033[1;32m";
    char *transactionType = (transaction->type == EXPENSE) ? "-" : "";
    printf("ID: %d, Nome: %s, Valor: %sR$ %s%.2f\033[0m\n", transaction->id, transaction->name, color, transactionType, (double)transaction->amount/100);  
}

void displayTransactions() {
    struct Transaction *temp = head;

    if (temp == NULL) {
        printf("Transações não encontradas\n");
    }

    while (temp != NULL) {
        showTransaction(temp);
        temp = temp->next;
    }

    char *color = (balance < 0) ? "\033[1;31m" : "\033[1;32m";

    printf("\nBalanço atual: %sR$ %.2f\033[0m\n", color, (double)balance/100);
}

struct Transaction *searchTransaction(int id) {
    struct Transaction *temp = head;

    while (temp->next != NULL && temp->id != id) {
        temp = temp->next;
    }

    if (temp->id != id) {
        return NULL;
    }
    
    return temp;
}

void updateTransaction(int id, char *name, int amount, enum TransactionType type, struct Transaction *transactionToUpdate) {
    if (transactionToUpdate == NULL) {
        printf("\nTransação não encontrada\n");
        return;
    }

    // previous value remove
    if (transactionToUpdate->type == PROFIT) {
        balance -= transactionToUpdate->amount;
    } else {
        balance += transactionToUpdate->amount;
    }
    
    // data update
    strcpy(transactionToUpdate->name, name);
    transactionToUpdate->amount = amount;
    transactionToUpdate->type = type;

    // balance update
    if (type == PROFIT)
        balance += amount;
    else
        balance -= amount;
    
    printf("\nTransação atualizada com sucesso\n");
}

void removeTransaction(int id) {
    struct Transaction *temp = head;
    struct Transaction *prev = NULL;

    // searches 
    while (temp->next != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp->id != id) {
        printf("\nTransação não encontrada\n");
        return;
    }

    // balance update
    if (temp->type == PROFIT) {
        balance -= temp->amount;
    } else {
        balance += temp->amount;
    }
    
    if (temp == head) {
        head = temp->next;
    } else {
        prev->next = temp->next;
        if (temp->next == NULL) {
            current = prev;
        }
    }

    free(temp);
    printf("\nTransação removida com sucesso\n");
}