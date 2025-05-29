#include "CustomStack.h"
#include <stdexcept>

template <typename T>
CustomStack<T>::CustomStack() : topIndex(-1), capacity(MAX_SIZE)
{
    data = new T[capacity];
}

template <typename T>
CustomStack<T>::~CustomStack()
{
    delete[] data;
}

template <typename T>
bool CustomStack<T>::push(const T &item)
{
    if (isFull())
    {
        return false;
    }
    data[++topIndex] = item;
    return true;
}

template <typename T>
bool CustomStack<T>::pop()
{
    if (isEmpty())
    {
        return false;
    }
    --topIndex;
    return true;
}

template <typename T>
const T &CustomStack<T>::top() const
{
    if (isEmpty())
    {
        throw std::runtime_error("Stack Kosong!!!");
    }
    return data[topIndex];
}

template <typename T>
T &CustomStack<T>::top()
{
    if (isEmpty())
    {
        throw std::runtime_error("Stack Kosong!!!");
    }
    return data[topIndex];
}

template <typename T>
bool CustomStack<T>::isEmpty() const
{
    return topIndex == -1;
}

template <typename T>
int CustomStack<T>::size() const
{
    return topIndex + 1;
}

template <typename T>
bool CustomStack<T>::isFull() const
{
    return topIndex == capacity - 1;
}

template <typename T>
CustomStack<T>::CustomStack(const CustomStack &other) : topIndex(other.topIndex), capacity(other.capacity)
{
    data = new T[capacity];
    for (int i = 0; i <= topIndex; ++i)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
CustomStack<T> &CustomStack<T>::operator=(const CustomStack &other)
{
    if (this != &other)
    {
        delete[] data;

        topIndex = other.topIndex;
        capacity = other.capacity;
        data = new T[capacity];

        for (int i = 0; i <= topIndex; ++i)
        {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template class CustomStack<Booking>;