#include "transaction_type.h"

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