#ifndef TRANSACTION_TYPE_H
#define TRANSACTION_TYPE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    enum TransactionType {
        EXPENSE = 1,
        PROFIT = 2
    };

    enum TransactionType translateToTransactionType();

#endif