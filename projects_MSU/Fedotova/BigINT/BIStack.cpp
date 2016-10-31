//
// Stack of Big Integers
//
#include "BIStack.h"

BigIntStack::BigIntStack():
    stack(0),
    max_size(STACK_MAXSIIZE),
    size(0)
{
    stack = new BigInt[max_size];
}

BigIntStack::BigIntStack(int maxSize):
    stack(0),
    max_size(maxSize),
    size(0)
{
    stack = new BigInt[max_size];
}

void BigIntStack::push(const BigInt& x) throw (StackException) {
    if (size >= max_size)
        throw StackException("Stack overflow");
    stack[size] = x;
    size++;
}

BigInt BigIntStack::pop() throw (StackException) {
    if (size == 0)
        throw StackException("Stack empty");
    BigInt x = stack[size - 1];
    size--;
    return x;
}

BigInt BigIntStack::top() const throw (StackException) {
    if (size == 0)
        throw StackException("Stack empty");
    return stack[size - 1];
}

int BigIntStack::depth() const {
    return size;
}

void BigIntStack::init() {
    size = 0;
}

bool BigIntStack::empty() const {
    return (size == 0);
}

BigInt BigIntStack::elementAt(int i) const {
    if (i >= size)
        throw StackException("Out of bounds");
    return stack[size - 1 - i];
}
