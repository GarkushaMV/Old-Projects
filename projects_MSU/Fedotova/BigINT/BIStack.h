//
// Stack of real numbers
//
#ifndef BI_STACK_H
#define BI_STACK_H

#include "BigInt.h"

const int STACK_MAXSIIZE = 1024;

class StackException {
public:
    const char *reason;
    StackException():
        reason("")
    {}

    StackException(const char *cause):
        reason(cause)
    {}
};

class BigIntStack {
private:
    BigInt* stack;
    int max_size;
    int size;
public:
    BigIntStack();
    BigIntStack(int maxSize);
    void push(const BigInt&) throw (StackException);
    BigInt pop() throw (StackException);
    BigInt top() const throw (StackException);
    int depth() const;
    void init();
    bool empty() const;
    BigInt elementAt(int i) const;
};

#endif
