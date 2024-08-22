#include <stdio.h>
#include <stdlib.h>

#include "dynamic_array.h"
#include "core.h"



int main() {
    char expression[MAX_EXPR_LEN];
    printf("Введите выражение: ");
    fgets(expression, MAX_EXPR_LEN, stdin);
    expression[strcspn(expression, "\n")] = '\0';

    output_graph(expression);

    return 0;
}