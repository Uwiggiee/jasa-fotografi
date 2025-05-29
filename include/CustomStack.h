#ifndef CUSTOM_STACK_H
#define CUSTOM_STACK_H

#include "Booking.h"

template <typename T>
class CustomStack {
private:
    static const int MAX_SIZE = 10;  
    T *data;          
    int topIndex;     
    int capacity;     

public:
    CustomStack();
    ~CustomStack();

    bool push(const T& item);
    bool pop();
    T& top();
    const T& top() const; 
    bool isEmpty() const;
    int size() const;
    bool isFull() const;

    // Copy constructor & assignment operator
    CustomStack(const CustomStack& other);
    CustomStack& operator=(const CustomStack& other);  
};

#endif