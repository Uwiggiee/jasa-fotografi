#ifndef SORTING_ALGORITHM_H
#define SORTING_ALGORITHM_H

#include "Booking.h"
#include <vector>

class SortingAlgorithm{
public:
    static void mergeSort(std::vector<Booking>& bookings, int left, int right);
    static void merge(std::vector<Booking>& bookings, int left, int mid, int right);
    static bool compareBookings(const Booking& a, const Booking& b);
};

#endif