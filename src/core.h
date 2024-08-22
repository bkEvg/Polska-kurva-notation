#ifndef CORE_HEADER
#define CORE_HEADER

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_EXPR_LEN 1000
#define WIDTH 80
#define HEIGHT 25
#define X_MIN 0
#define X_MAX (4 * M_PI)
#define Y_MIN -1
#define Y_MAX 1

int is_number(char op);
int is_operator(char op);
int priority(char op);
void infix_to_postfix(char *infix, char *postfix);
double processing(char *postfix, double x);
void output_graph(char *infix);

#endif // CORE_HEADER