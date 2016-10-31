#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <fstream>
#include <assert.h>

#define PI 3.14159265358979323846264338328
#define domain_of_definition 1
#define POISON 124100

struct Stack_t
{
    int counter;
    int max_size;
    double* elements;
};

int Stack_not_OK (const Stack_t* stk)
{
    if (stk -> elements == 0) return 1; //code of error 1: zero pointer to stack
    if (stk -> counter < 0) return 2; //code of error 2: counter is negative
    if (stk -> counter > stk -> max_size) return 3; //code of error 3: pointer is more than max allowed
    if (stk -> elements == 0) return 4; //code of error 4: zero pointer to bufer
    else return 0; //everything is OK
}

void print_error_code (const Stack_t* stk);

void Stack_dump (const Stack_t* stk)
{
    printf ("Current status of stack:\n");
    print_error_code (stk);

    printf ("Size = %d\n", stk -> max_size);
    printf ("Counter = %d\n", stk -> counter);

    for (int i = 1; i < stk -> counter; i++)
    {
        if (stk -> elements[i] == POISON) break;
        printf ("elements[%d] = ", i);
        printf ("%lg\n", stk -> elements[i]);
    }
    for (int i = stk -> counter; i < stk -> max_size; i++)
    {
        if (stk -> elements[i] == POISON) break;
        printf ("*elements[%d] = ", i);
        printf ("%lg\n", stk -> elements[i]);
    }
    return;
}

void print_error_code (const Stack_t* stk)
{
    if (Stack_not_OK (stk) == 1) printf ("Code of error 1: zero pointer to stack\n");
    if (Stack_not_OK (stk) == 2) printf ("Code of error 2: counter is negative\n");
    if (Stack_not_OK (stk) == 3) printf ("Code of error 3: pointer is more than max allowed\n");
    if (Stack_not_OK (stk) == 4) printf ("Code of error 4: zero pointer to bufer\n");
    return;
}

int STACK_VERIFY (const Stack_t* stk)
{
    if (Stack_not_OK (stk))
    {
        Stack_dump (stk);
        return 0;
    }
    else return 1;
}

void Stack_push (Stack_t* stk, double value)
{
    assert (STACK_VERIFY (stk));

    stk -> counter ++;
    stk -> elements [stk -> counter] = value;

    assert (STACK_VERIFY (stk));
    return;
}

double Stack_pop (Stack_t* stk)
{
    assert (STACK_VERIFY (stk));

    double value = stk -> elements [stk -> counter];
    stk -> elements [stk -> counter] = POISON;
    stk -> counter--;

    assert (STACK_VERIFY (stk));
    return value;
}

void Stack_destruct (Stack_t* stk)
{
    assert (STACK_VERIFY (stk));
    free (stk -> elements);
}

Stack_t* Stack_construct (int Max_size)
{
    Stack_t* stk = (Stack_t*) calloc (1, sizeof(Stack_t));

    stk -> max_size = Max_size;
    stk -> elements = (double*) calloc (Max_size, sizeof(double));

    for (int i = 0; i < Max_size; i++)
        stk -> elements [i] = POISON;

    stk -> counter = 0;

    return stk;
}
