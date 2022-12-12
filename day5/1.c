#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1000

typedef struct {
    void *data;
    int top;
    int element_size;
    //int (*compare)(const void *a, const void *b);
} Stack;
/*int char_compare(const void *a, const void *b) {
  return (*(char *)a - *(char *)b);
}*/
Stack* stackCreate(size_t size) {
    Stack *obj = malloc(sizeof(Stack));
    obj->data = malloc(MAX_SIZE * size);
    obj->top = -1;
    obj->element_size = size;
    //obj->compare = char_compare;
    return obj; 
}


void stackPush(Stack *stack, void *element) {
    if(stack->top == MAX_SIZE - 1) {
        printf("Error: stack full\n");
        return;
    }

    memcpy((char *) stack->data + (stack->top + 1) * stack->element_size, element, stack->element_size);
    stack->top++;
}
void *stackPeek(Stack *stack) {
    if(stack->top == -1) {
        printf("Error: stack empty\n");
        return NULL;
    }

    return (char*) stack->data + stack->top * stack->element_size;
}
void stackPop(Stack *stack, void *element) {

    if (stack->top == -1) {
        printf("Error: stack empty\n");
        return;
    }

    memcpy((char*) element, (char*) stack->data + stack->top * stack->element_size, stack->element_size);
    stack->top--;
}


int parse_string(const char* input, int* a, int* b, int* c) {
    static char move[20], from[20], to[20];
    if(sscanf(input, "%s %d %s %d %s %d\n", move, a, from, b, to, c) != 6) {
        return 0;
    }
    return 1;
}

void stackFree(Stack* stack) {
    free(stack->data);
}
int main() {
    FILE* file = fopen("input.txt", "r");
    FILE* initfile = fopen("init.txt", "r");
    static char line[20], init[20];
    int moves, poploc, pushloc;
    Stack stacks[9];
    int index = 0;
    char temp;
    Stack* crane = stackCreate(sizeof(char));
    while (fgets(init, sizeof(init), initfile) && index != 9) {
        stacks[index] = *stackCreate(sizeof(char));
        //printf("initLINE: %s\n", init);
        for (int i = 0; i < 10; i++) {
            if ((strcmp(&init[i], "") != 0 && strcmp(&init[i], "\n") != 0) && strncmp(&init[i], "X", 1) != 0){ 
                //printf("Pushing %c on stack %d\n", init[i], index);
                stackPush(&stacks[index], &init[i]);
            }
        }
        strcpy(init, "XXXXXXXXXXXXXXXXXXX");
        index++;
    }
    while (fgets(line, sizeof(line), file)) {
        //printf("Line: %s\n", line);

        if(parse_string(line, &moves, &poploc, &pushloc) == 1) {
            for(int i = 0; i < moves; i++) {
                stackPop(&stacks[poploc-1], &temp);
                stackPush(crane, &temp);
            }
            for (int i = 0; i < moves; i++) {
                stackPop(crane, &temp);
                stackPush(&stacks[pushloc-1], &temp); 
            }
        }
    }
    char top[9];
    for (int i = 0; i < 9; i++) {
        top[i] = *(char *) stackPeek(&stacks[i]);
        printf("stack %d: %c\n", i+1, top[i]);
        stackFree(&stacks[i]);
    }
}
