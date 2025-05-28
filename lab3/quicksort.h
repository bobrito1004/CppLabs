#pragma once
#include <algorithm>

template <typename T, typename Compare>
T median_of_three(T* first, T* middle, T* last, Compare comp) {
    if (comp(*middle, *first)) {
        auto temp = std::move(*middle);
        *middle = std::move(*first);
        *first = std::move(temp);
    }
    if (comp(*last, *first)) {
        auto temp = std::move(*last);
        *last = std::move(*first);
        *first = std::move(temp);
    }
    if (comp(*last, *middle)) {
        auto temp = std::move(*last);
        *last = std::move(*middle);
        *middle = std::move(temp);
    }
    return *middle;
}

template <typename T, typename Comp>
void qSortDefault(T* first, T* last, Comp comp) {
    while (first < last ) {
        if (last - first <= 1) {
            return;
        }
        auto left = first;
        auto right = last - 1;
        auto pivot = median_of_three(first, first + ((right - first) >> 1), right, comp);

        while (left <= right) {
            while (comp(*left, pivot)) {
                ++left;
            }
            while (comp(pivot, *right)) {
                --right;
            }

            if (left <= right) {
                auto temp = std::move(*left);
                *left = std::move(*right);
                *right = std::move(temp);
                ++left;
                --right;
            }
        }

        if (right - first < last - left) {
            qSortDefault(first, right + 1, comp);
            first = left;
        } else {
            qSortDefault(left, last, comp);
            last = right + 1;
        }
    }
}

template <typename T, typename Comp>
void insertionSort(T* first, T* last, Comp comp) {
    for (auto i = first + 1; i < last; ++i) {
        auto key = std::move(*i);
        auto prev = i;

        while (prev > first && comp(key, *(prev - 1))) {
            *prev = std::move(*(prev - 1));
            --prev;
        }

        *prev = std::move(key);
    }
}



template <typename T, typename Comp>
void qSortImproved(T* first, T* last, Comp comp) {
    constexpr int threshold = 40;
    while (first < last ) {
        if (last - first <= 1) {
            return;
        }

        if (last - first <= threshold){
            insertionSort(first, last, comp);
            return;
        }

        auto left = first;
        auto right = last - 1;
        auto pivot = median_of_three(first, first + ((right - first) >> 2), right, comp);

        while (left <= right) {
            while (comp(*left, pivot)) {
                ++left;
            }
            while (comp(pivot, *right)) {
                --right;
            }

            if (left <= right) {
                auto temp = std::move(*left);
                *left = std::move(*right);
                *right = std::move(temp);
                ++left;
                --right;
            }
        }

        if (right - first < last - left) {
            qSortImproved(first, right + 1, comp);
            first = left;
        } else {
            qSortImproved(left, last, comp);
            last = right + 1;
        }
    }
}

