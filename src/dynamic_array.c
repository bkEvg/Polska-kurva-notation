#include <stdio.h>
#include <stdlib.h>

#include "dynamic_array.h"



void array_init(dynamic_array **arr_ptr) {
    dynamic_array *container;
    container = (dynamic_array *)malloc(sizeof(dynamic_array));
    if (!container) {
        printf("MEMORY ALLOC FAILED\n");
        exit(0);
    }
    container->size = 0;
    container->capacity = INIT_CAPACITY;
    container->array = (char *)malloc(sizeof(char) * INIT_CAPACITY);
    if (!container->array) {
        printf("MEMORY ALLOC FAILED\n");
        exit(0);
    }
    *arr_ptr = container;
}

// append value to the end of array
void append_item(dynamic_array *container, char item) {
    if (container->size == container->capacity) {
        char *tmp = container->array;
        container->capacity <<= 1;
        container->array = (char *)realloc(container->array, container->capacity * sizeof(char));
        if (!container->array) {
            printf("MEMORY REALLOC FAILED, CHECK COMP MEMORY CAPACITY\n");
            container->array = tmp; 
            return; 
        }
    }
    container->array[container->size++] = item;
}

char pop_item(dynamic_array *container) {
    if (container->size == 0)
    {
        printf("STACK IS EMPTY CAN NoT POP ITEM");
        return -1;
    }
    
    char last_value = container->array[container->size - 1];
    container->size--;
    return last_value;
}

void print_array(dynamic_array *container) {
    printf("Elements: "); 
    for (int i = 0; i < (char)container->size; i++) { 
        printf("%c ", container->array[i]); 
    } 
    printf("\nSize: "); 
    printf("%lu", container->size); 
    printf("\nCapacity: "); 
    printf("%lu\n", container->capacity); 
}

void free_array(dynamic_array *container) {
    free(container->array);
    free(container);
}

int is_empty(dynamic_array *container) {
    if (container->size == 0) {
        return 1;
    }
    return 0;
}

char peek(dynamic_array *container) {
    if (container->size == 0) {
        return '\0';
    }
    return container->array[container->size - 1];
}