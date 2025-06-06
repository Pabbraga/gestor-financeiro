#include <stdlib.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <locale.h>

enum TransactionType {
    EXPENSE = 1,
    PROFIT = 2
};

struct Transaction {
    int id;
    char name[30];
    int amount;
    enum TransactionType type;
    struct Transaction *next;
};

struct Transaction *head = NULL;
struct Transaction *current = NULL;

void insertTransaction(int id, char *name, int amount, enum TransactionType type) {
    struct Transaction *newTransaction = (struct Transaction *)malloc(sizeof(struct Transaction));

    // data insertion
    newTransaction->id = id;
    strcpy(newTransaction->name, name);
    newTransaction->amount = amount;
    newTransaction->type = type;
    newTransaction->next = NULL;

    if (head == NULL) {
        // first insertion
        head = newTransaction;
        current = newTransaction;
    } else {
        current->next = newTransaction;
        current = newTransaction;
    }
}

void displayTransactions() {
    struct Transaction *temp = head;
    printf("\nResultado\n------------\n");
    if (temp == NULL) {
        printf("Transações não encontradas");
    }

    while (temp != NULL) {
        char *cor = (temp->type == EXPENSE) ? "\033[1;31m" : "\033[1;32m";
        printf("ID: %d, Nome: %s, Valor: %s%.2f\033[0m\n", temp->id, temp->name, cor, (double)temp->amount/100);
        temp = temp->next;
    }
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

void updateTransaction(int id, char *name, int amount, enum TransactionType type) {
    struct Transaction *temp = searchTransaction(id);

    if (temp == NULL) {
        printf("Transação não encontrada\n");
        return;
    }
    
    // data update
    strcpy(temp->name, name);
    temp->amount = amount;
    temp->type = type;
    
    printf("Transação atualizada com sucesso\n");
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
        printf("Transação não encontrada\n");
        return;
    }
    
    if (temp == head) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Transação removida com sucesso\n");
}

void pause() {
    printf("\nPressione [Enter] para continuar...\n");
    
    while(getchar()!='\n'); // waits enter key
    getchar();
}

enum TransactionType translateToTransactionType() {
    enum TransactionType type = 0;
    int typeNumber = 0;

    printf("Qual o tipo de transação a ser realizada?\n1- Despesa\n2- Ganho\n");
    printf("Escolha uma opção: ");
    scanf("%i", &typeNumber);
    
    // transaction type validation
    if (typeNumber == EXPENSE) {
        type = EXPENSE;
    } else if (typeNumber == PROFIT) {
        type = PROFIT;
    } else {
        printf("Tipo inválido! Usando DESPESA como padrão.\n");
        type = EXPENSE;
        pause();
        __fpurge(stdin);
    }

    return type;
}

void main() {
    int resp = -1;
    int id, amount = 0;
    double doubleAmount = 0;
    char name[30];
    enum TransactionType type = 0;

    // turns OS locale language
    setlocale(LC_ALL, "");

    while (resp != 0) {
        printf("Gestor Financeiro\n-----------------\n");
        printf("1- Adicionar transferência\n2- Alterar transferência\n3- Remover transferência\n4- Buscar transferência\n5- Mostrar todas as transferências\n0- Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &resp);
        switch (resp) {
            case 1:
                system("clear");
                type = translateToTransactionType();
                system("clear");
                
                printf("Insira uma descrição: ");
                __fpurge(stdin); // prevents getting \n from buffer
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // prevents \n after string
                
                printf("Insira um valor: ");
                scanf("%lf", &doubleAmount);
                // casting into int and turning it cents
                amount = (int)(doubleAmount * 100);

                if (head == NULL) {
                    id = 1;
                } else {
                    id = current->id+1;
                }

                insertTransaction(id, name, amount, type);
                break;
            case 2:
                system("clear");
                printf("Insira o ID: ");
                scanf("%i", &id);

                printf("Insira uma descrição: ");
                __fpurge(stdin); // prevents getting \n from buffer
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // prevents \n after string
                
                printf("Insira um valor: ");
                scanf("%lf", &doubleAmount);
                // casting into int and turning it cents
                amount = (int)(doubleAmount * 100);

                type = translateToTransactionType();

                updateTransaction(id, name, amount, type);
                break;
            case 3:
                system("clear");
                printf("Insira o ID: ");
                scanf("%i", &id);

                removeTransaction(id);
                break;
            case 4:
                system("clear");
                printf("Insira o ID: ");
                scanf("%i", &id);
                struct Transaction *search = searchTransaction(id);
                
                if (search == NULL) {
                    printf("Transação não encontrada\n");
                    break;
                }

                char *cor = (search->type == EXPENSE) ? "\033[1;31m" : "\033[1;32m";
                printf("ID: %d, Nome: %s, Valor: %s%.2f\033[0m\n", search->id, search->name, cor, (double)search->amount/100);
                pause();
                break;
            case 5:
                system("clear");
                displayTransactions();
                pause();
                break;
            default:
                break;
        }
    }
}