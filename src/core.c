#include "core.h"
#include "dynamic_array.h"



// приоритет
int priority(char op) {
    switch (op) {
        case '+': case '-':
            return 1;
        case '*': case '/':
            return 2;
        case 's': case 'c': case 't': case 'g': case 'q': case 'l':
            return 3;
        default:
            return 0;
    }
}

// тригонометрия ?
int is_trigonometric(char *str, int start) {
    return (
        strncmp(&str[start], "sin", 3) == 0 ||
        strncmp(&str[start], "cos", 3) == 0 ||
        strncmp(&str[start], "tan", 3) == 0 ||
        strncmp(&str[start], "ctg", 3) == 0 ||
        strncmp(&str[start], "sqrt", 4) == 0 ||
        strncmp(&str[start], "ln", 2) == 0
    );
}

// оператор ?
int is_operator(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/';
}

// число ?
int is_number(char op) {
    return (op >= '0' && op <= '9') || op == '.';
}

// минусы ?
int is_unary_minus(char *infix, int i) {
    return infix[i] == '-' && (i == 0 || infix[i - 1] == '(');
}

// Длина тригонометрической функции
int trig_func_len(const char *str, int start) {
    int len = 0;
    for (; str[start + len] != '(' && str[start + len] != '\0'; len++);
    return len;
}

// преобразования
void infix_to_postfix(char *infix, char *postfix) {
    dynamic_array *stack = NULL;
    array_init(&stack);
    int j = 0;
    for (int i = 0; infix[i]; i++) {
        if (infix[i] == ' ')
            continue;
        if (is_number(infix[i]) || infix[i] == 'x') {
            while (is_number(infix[i]) || infix[i] == 'x') {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        } else if (infix[i] == '(') {
            append_item(stack, infix[i]);
        } else if (infix[i] == ')') {
            while (!is_empty(stack) && peek(stack) != '(') {
                postfix[j++] = pop_item(stack);
                postfix[j++] = ' ';
            }
            // Убираем скобку со стека
            pop_item(stack);
        } else if (is_unary_minus(infix, i)) {
            append_item(stack, '~');
        } else if (is_operator(infix[i])) {
            while (!is_empty(stack) && priority(peek(stack)) >= priority(infix[i])) {
                postfix[j++] = pop_item(stack);
                postfix[j++] = ' ';
            }
            append_item(stack, infix[i]);
        } else if (is_trigonometric(infix, i)) {
            if (strncmp(&infix[i], "sin", 3) == 0) {
                append_item(stack, 's');
                i += 2;
            } else if (strncmp(&infix[i], "cos", 3) == 0) {
                append_item(stack, 'c');
                i += 2;
            } else if (strncmp(&infix[i], "tan", 3) == 0) {
                append_item(stack, 't');
                i += 2;
            } else if (strncmp(&infix[i], "ctg", 3) == 0) {
                append_item(stack, 'g');
                i += 2;
            } else if (strncmp(&infix[i], "sqrt", 4) == 0) {
                append_item(stack, 'q');
                i += 3;
            } else if (strncmp(&infix[i], "ln", 2) == 0) {
                append_item(stack, 'l');
                i += 1;
            }
        }
    }
    while (!is_empty(stack)) {
        postfix[j++] = pop_item(stack);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
    free_array(stack);
}

// Операции
double operation(double operand1, double operand2, char op) {
    double res = 0;
    switch (op) {
        case '+': res = operand1 + operand2; break;
        case '-': res = operand2 - operand1; break;
        case '/': res = operand2 / operand1; break;
        case '*': res = operand1 * operand2; break;
        case '~': res = -operand1; break;
    }
    return res;
}

// Обработка тригонометрических функций
double process_trigonometric(char op, double operand) {
    switch (op) {
        case 's': return sin(operand);
        case 'c': return cos(operand);
        case 't': return tan(operand);
        case 'g': return 1.0 / tan(operand);
        case 'q': return sqrt(operand);
        case 'l': return log(operand);
        default: return 0;
    }
}

// вычисления
double processing(char *postfix, double x) {
    dynamic_array *stack = NULL;
    array_init(&stack);
    for (int i = 0; postfix[i]; i++) {
        if (postfix[i] == ' ')
            continue;
        if (is_number(postfix[i])) {
            double num = 0;
            int decimal_point = 0;
            double decimal_place = 1;
            while (is_number(postfix[i])) {
                if (postfix[i] == '.') {
                    decimal_point = 1; // флаг что число decimal
                } else {
                    if (decimal_point) {
                        decimal_place *= 0.1;
                        num += (postfix[i] - '0') * decimal_place;
                    } else {
                        num = num * 10 + (postfix[i] - '0');
                    }
                }
                i++;
            }
            i--;
            append_item(stack, num);
        } else if (postfix[i] == 'x') {
            append_item(stack, x);
        } else if (strchr("sctgql", postfix[i])) {
            double val = pop_item(stack);
            printf("Processing trigonometric function '%c' with operand %lf\n", postfix[i], val); // Отладка
            append_item(stack, process_trigonometric(postfix[i], val));
        } else {
            double val1 = pop_item(stack);
            double val2 = is_empty(stack) ? 0 : pop_item(stack);
            printf("Processing operation '%c' with operands %lf and %lf\n", postfix[i], val2, val1); // Отладка
            append_item(stack, operation(val1, val2, postfix[i]));
        }
    }
    double result = pop_item(stack);
    free_array(stack);
    return result;
}

void output_graph(char *infix) {
    char postfix[MAX_EXPR_LEN];
    infix_to_postfix(infix, postfix);

    printf("Постфиксное выражение: %s\n", postfix);

    char graph[HEIGHT][WIDTH];
    memset(graph, ' ', sizeof(graph));

    for (int i = 0; i < WIDTH; i++) {
        double x = X_MIN + i * (X_MAX - X_MIN) / (WIDTH - 1);
        double y = processing(postfix, x);

        printf("x = %lf, y = %lf\n", x, y);

        int y_pos = HEIGHT - 1 - round((y - Y_MIN) * (HEIGHT - 1) / (Y_MAX - Y_MIN));
        if (y_pos >= 0 && y_pos < HEIGHT) {
            graph[y_pos][i] = '*';
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", graph[i][j]);
        }
        printf("\n");
    }
}