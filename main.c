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
int balance = 0;

void insertTransaction(int id, char *name, int amount, enum TransactionType type) {
    struct Transaction *newTransaction = (struct Transaction *)malloc(sizeof(struct Transaction));

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

void pause() {
    printf("\nPressione [Enter] para continuar...\n");
    
    while(getchar()!='\n'); // waits enter key
    getchar();
}

enum TransactionType translateToTransactionType() {
    enum TransactionType type = 0;
    int typeNumber = 0;

    printf("\nQual o tipo de transação a ser realizada?\n1- Despesa\n2- Ganho\n");
    printf("Escolha uma opção: ");
    scanf("%i", &typeNumber);
    
    // transaction type validation
    if (typeNumber == EXPENSE) {
        type = EXPENSE;
    } else if (typeNumber == PROFIT) {
        type = PROFIT;
    } else {
        printf("\nTipo inválido! Usando Despesa como padrão\n");
        type = EXPENSE;
    }

    return type;
}

void main() {
    int resp = -1;
    int id, amount = 0;
    double doubleAmount = 0;
    char name[30];
    enum TransactionType type = 0;
    struct Transaction *search = NULL;

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
                
                printf("\nInsira uma descrição (limite 30 caracteres): ");
                __fpurge(stdin); // prevents getting \n from buffer
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // prevents \n after string
                
                __fpurge(stdin);
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
                pause();
                break;
            case 2:
                system("clear");
                printf("Insira o ID: ");
                scanf("%i", &id);

                search = searchTransaction(id);
                printf("\nResultado\n------------\n");
                showTransaction(search);

                printf("\nInsira uma descrição (limite 30 caracteres): ");
                __fpurge(stdin); // prevents getting \n from buffer
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // prevents \n after string
                
                printf("Insira um valor: ");
                scanf("%lf", &doubleAmount);
                // casting into int and turning it cents
                amount = (int)(doubleAmount * 100);

                type = translateToTransactionType();

                updateTransaction(id, name, amount, type, search);
                pause();
                break;
            case 3:
                char confirmation = '\0';
                system("clear");
                printf("Insira o ID: ");
                scanf("%i", &id);
                
                search = searchTransaction(id);
                printf("\nResultado\n------------\n");
                showTransaction(search);
                
                __fpurge(stdin);
                printf("\nVocê tem certeza disso? (s/n) ");
                scanf("%c", &confirmation);

                if(confirmation == 's') {
                    removeTransaction(id);
                    pause();
                    break;
                } else if(confirmation == 'n') {
                    printf("\nCancelando operação...");
                    pause();
                    break;
                }

                printf("\nEscolha inválida! Cancelando operação...");
                pause();
                break;
            case 4:
                system("clear");
                printf("Insira o ID: ");
                scanf("%i", &id);
                search = searchTransaction(id);
                
                if (search == NULL) {
                    printf("\nTransação não encontrada\n");
                    pause();
                    break;
                }

                printf("\nResultado\n------------\n");
                showTransaction(search);
                pause();
                break;
            case 5:
                system("clear");
                printf("\nResultado\n------------\n");
                displayTransactions();
                pause();
                break;
            default:
                break;
        }
    }
}