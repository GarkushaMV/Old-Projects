//
// Stack Calculator of Big Integers
//
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "BigInt.h"
#include "BIStack.h"

static void onAdd();
static void onSub();
static void onMul();
static void onDiv();
static void onMod();
static void onPow();
static void onPowMod();
static void onInvMod();
static void onGcd();
static void onEUA();
static void onPush(const char* line);
static void onPop();
static void onDup();
static void onExch();
static void onInit();
static void display();
static void printHelp();
static void onShow();
static void onGenerateRandom();
static void onTestPrime();
static void onGeneratePrime();

static BigIntStack *stack = 0;

int main() {
    //... lainit(10000);
    printHelp();
    srand((unsigned int) time(0));

    char line[256];
    stack = new BigIntStack();

    // gets(line);
    scanf("%s", line);
    while (*line != 0) {
        int linelen = strlen(line);
        try {
            if (strcmp(line, "+") == 0)
                onAdd();
            else if (strcmp(line, "-") == 0)
                onSub();
            else if (strcmp(line, "*") == 0)
                onMul();
            else if (strcmp(line, "/") == 0)
                onDiv();
            else if (strcmp(line, "%") == 0 || strcmp(line, "mod") == 0)
                onMod();
            else if (strcmp(line, "^") == 0 || strcmp(line, "pow") == 0)
                onPow();
            else if (strcmp(line, "powmod") == 0)
                onPowMod();
            else if (strcmp(line, "invmod") == 0)
                onInvMod();
            else if (strcmp(line, "gcd") == 0)
                onGcd();
            else if (strcmp(line, "eua") == 0 || strcmp(line, "EUA") == 0)
                onEUA();
            else if (strcmp(line, "rand") == 0)
                onGenerateRandom();
            else if (strcmp(line, "tstprime") == 0)
                onTestPrime();
            else if (strcmp(line, "genprime") == 0)
                onGeneratePrime();
            else if (strcmp(line, "=") == 0)
                display();
            else if (
                (linelen > 0 && isdigit(line[0])) ||
                (linelen > 1 && (line[0] == '-' || line[0] == '+') &&
                    isdigit(line[1]))
            )
                onPush(line);
            else if (strcmp(line, "pop") == 0)
                onPop();
            else if (strcmp(line, "dup") == 0)
                onDup();
            else if (strcmp(line, "exch") == 0)
                onExch();
            else if (strcmp(line, "init") == 0)
                onInit();
            else if (strcmp(line, "show") == 0)
                onShow();
            else if (
                strcmp(line, "") == 0 ||
                (linelen > 0 && (line[0] == 'q' || line[0] == 'Q'))
            )
                break;
            else
                printHelp();
        } catch (StackException& e) {
            printf("Stack Exception: %s\n", e.reason);
        }
        // gets(line);
        scanf("%s", line);
    }
    return 0;
}

static void onAdd() {
    BigInt y = stack->pop();
    BigInt x = stack->pop();
    stack->push(x + y);
    display();
}

static void onSub() {
    BigInt y = stack->pop();
    BigInt x = stack->pop();
    stack->push(x - y);
    display();
}

static void onMul() {
    BigInt y = stack->pop();
    BigInt x = stack->pop();
    stack->push(x * y);
    display();
}

static void onDiv() {
    BigInt y = stack->pop();
    BigInt x = stack->pop();
    stack->push(x / y);
    display();
}

static void onMod() {
    BigInt y = stack->pop();
    BigInt x = stack->pop();
    stack->push(x % y);
    display();
}

static void onPow() {
    int y = (int) stack->pop();
    BigInt x = stack->pop();
    stack->push(x.power(y));
    display();
}

static void onPowMod() {
    BigInt m = stack->pop();
    BigInt y = stack->pop();
    BigInt x = stack->pop();
    stack->push(x.powerMod(y, m));
    display();
}

static void onInvMod() {
    BigInt m = stack->pop();
    BigInt x = stack->pop();
    stack->push(x.inverseMod(m));
    display();
}

static void onGcd() {
    BigInt y = stack->pop();
    BigInt x = stack->pop();
    stack->push(BigInt::gcd(x, y));
    display();
}

static void onEUA() {
    BigInt u, v, d;
    BigInt y = stack->pop();
    BigInt x = stack->pop();
    BigInt::extEucl(x, y, u, v, d);
    stack->push(u);
    stack->push(v);
    stack->push(d);
    display();
}

static void onPush(const char* line) {
    BigInt x;
    x.fromString(line, strlen(line));
    stack->push(x);
}

static void onPop() {
    stack->pop();
}

static void onDup() {
    stack->push(stack->top());
}

static void onExch() {
    BigInt x = stack->pop();
    BigInt y = stack->pop();
    stack->push(x);
    stack->push(y);
}

static void onInit() {
    stack->init();
}

static char textLine[10000];

static void display() {
    if (!stack->empty()) {
        printf("=%s\n", stack->top().toString(textLine, 4094));
    } else {
        printf("stack empty\n");
    }
}

static void onShow() {
    int d = stack->depth();
    printf("Depth of stack = %d.", d);
    if (d > 0)
        printf(" Stack elements:\n");
    else
        printf("\n");

    for (int i = 0; i < d; i++) {
        printf("=%s\n", stack->elementAt(i).toString(textLine, 4094));
    }
}

static void onGenerateRandom() {
    int len = (int) stack->pop();
    if (len < 0)
        len = (-len);
    if (len > 10000) {
        printf("Length is too large. Using the value 10000.\n");
        len = 10000;
    }
    BigInt r;
    r.generateRandom(len);
    stack->push(r);
    display();
}

static void onTestPrime() {
    BigInt m = stack->pop();
    bool res = m.isProbablePrime(20);
    if (res) {
        printf("Number is probably prime.\n");
    } else {
        printf("Number is composite.\n");
    }

    if (res) {
        stack->push(BigInt::one());
    } else {
        stack->push(BigInt::zero());
    }
    display();
}

static void onGeneratePrime() {
    int len = (int) stack->pop();
    if (len < 0)
        len = (-len);
    if (len > 10000) {
        printf("Length is too large. Using the value 10000.\n");
        len = 10000;
    }
    BigInt r;
    r.generateRandomPrime(len);
    stack->push(r);
    display();
}

static void printHelp() {
    printf(
        "Stack Calculator commands:\n"
        "\t<number>\tPush to stack\n"
        "\t+, -, *, /, %%\tAriphmetic operations\n"
        "\t^\t\tInteger power\n"
        "\tpowmod\t\tPower modulo m\n"
        "\tinvmod\t\tInverse modulo m\n"
        "\tgcd\t\tGreatest Common Divisor\n"
        "\tEUA\t\tExt.Euclid Alg.: in: m,n; out: u,v,d: um+vn=d=gcd(m,n)\n"
        "\trand\t\tGenerate random integer (input: length in bits)\n"
        "\ttstprime\tProbabilistic prime test\n"
        "\tgenprime\tGenerate random prime (input: length in bits)\n"
        "\t=\t\tDisplay the stack top\n"
        "\tpop\t\tRemove the stack top\n"
        "\tdup\t\tDuplicate the stack top to the stack\n"
        "\texch\t\tExchange (swap) two upper elements in the stack top\n"
        "\tshow\t\tShow the stack\n"
        "\tinit\t\tErase the stack\n"
        "\tquit\t\tEnd the program\n"
    );
}
