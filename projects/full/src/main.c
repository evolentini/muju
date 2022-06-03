#include "lib.h"
#include "simple.h"
#include "full.h"
#include <stdio.h>

int main(void) {
    printf("Iniciando el proyecto complejo\n");
    lib();
    simple();
    full();
    printf("Terminando el proyecto complejo\n");
}