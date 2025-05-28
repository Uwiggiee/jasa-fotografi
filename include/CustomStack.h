#ifndef CUSTOM_STACK_H
#define CUSTOM_STACK_H

#include "Booking.h"

template <typename T>
class CustomStack {
private:
    T *data;          // Pointer ke array data
    int topIndex;    // Indeks elemen terataor

public:
    CustomStack(): topIndex(-1) {}

    bool push(const T& item);
    bool pop();
    T& top();
    bool isEmpty() const;
    int size() const;
    bool isFull() const;
};

#endif