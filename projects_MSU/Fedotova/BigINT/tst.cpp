#include <stdio.h>
#include "BigInt.h"

int main() {
    char line[256];
    int l;
    BigInt a, b, c;
    a.fromString("1111111111111111111111");
    b.fromString("22222222222222222");
    c = a + b;
    c.toString(line, 256, &l);
    printf("%s\n", line);

    c = 2 + a;
    // c = a + 2;
    c.toString(line, 256, &l);
    printf("%s\n", line);

    return 0;
}
