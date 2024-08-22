#include <stdio.h>
#include <stdlib.h>

#define INIT_CAPACITY 8
// maybe problems with count if standart imports


typedef struct dynamic_array {
    size_t size;
    size_t capacity;
    char *array;
} dynamic_array;

void array_init(dynamic_array **arr_ptr);
void append_item(dynamic_array *container, char item);
char pop_item(dynamic_array *container);
void print_array(dynamic_array *container);
void free_array(dynamic_array *container);
int is_empty(dynamic_array *container);
char peek(dynamic_array *container);