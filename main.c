#include <stdlib.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <locale.h>
#include "transaction/transaction.c"

void pause() {
    printf("\nPressione [Enter] para continuar...\n");
    
    while(getchar()!='\n'); // waits enter key
    getchar();
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