#include "SortingAlgorithm.h"
#include <iostream>

// comparing two bookings
bool SortingAlgorithm::compareBookings(const Booking& a, const Booking& b) {
    // compare pake waktu
    time_t timeA = a.getWaktuMulai();
    time_t timeB = b.getWaktuMulai();

    return timeA < timeB;
}

void SortingAlgorithm::merge(std::vector<Booking>& bookings, int left, int mid, int right){
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    std::vector<Booking> leftArray(leftSize);
    std::vector<Booking> rightArray(rightSize);
    
    // copy data
    for (int i = 0; i < leftSize; i++){
        leftArray[i] = bookings[left + i];
    }
    for (int j = 0; j < rightSize; j++)
    {
        rightArray[j] = bookings[mid + j + 1];
    }
    
    // merge the temp arrays back
    int i = 0, j = 0, k = left;

    while (i < leftSize && j < rightSize)
    {
        if(compareBookings(leftArray[i], rightArray[j])) {
            bookings[k] = leftArray[i];
            i++;
        } else {
            bookings[k] = rightArray[j];
            j++;
        }
        k++;
    }
    
    while (i < leftSize)
    {
        bookings[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < rightSize)
    {
        bookings[k] = rightArray[j];
        j++;
        k++;
    }
}

void SortingAlgorithm::mergeSort(std::vector<Booking>& bookings, int left, int right) {
    if(left<right){
        int mid = left + (right - left)/2;

        mergeSort(bookings, left, mid);
        mergeSort(bookings, mid+1, right);

        merge(bookings, left, mid, right);
    }
}