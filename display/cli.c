#include "cli.h"

void clear_buffer() {
    int character = 0;
    while ((character = getchar()) != '\n' && character != EOF) {}
    return;
}

void pause() {
    clear_buffer();
    printf("\nPressione [Enter] para continuar...\n");
    getchar();
}
