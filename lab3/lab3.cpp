#include <iostream>
#include <random>
#include <chrono>
#include "../lab2/MyArray.h"
#include "quicksort.h"

template <typename Func>
double benchmark(Func&& func)
{
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}


template <typename T>
void qsortDefault(T& arr)
{
    qSortDefault(arr.data(), arr.data() + arr.size(), std::less<>());
}

template <typename T>
void qsortImproved(T& arr)
{
    qSortImproved(arr.data(), arr.data() + arr.size(), std::less<>());
}

template <typename T>
void insertion(T& arr)
{
    insertionSort(arr.data(), arr.data() + arr.size(), std::less<>());
}

// template <typename T>
// void qsortDefaultReverse(T& arr)
// {
//     qSortDefault(arr.data() + arr.size() - 1, arr.data() , std::less<>());
// }

int main(int argc, char* argv[])
{
    std::random_device rd;
    std::mt19937 gen(rd());
    const int testCount = 1000;
    myArray<double> results(testCount);


    
    // for (int i = 1; i < testCount; ++i)
    // {
    //     myArray<int> array(i);
    //     for (int j = 0; j < i; ++j) {array.insert(j);}
    //     std::shuffle(array.data(), array.data() + array.size(), rd);
    //     results.insert(benchmark([&]()
    //     {
    //         qsortDefault(array);
    //     }) * 1e9);
    // }


    
    for (int i = 1; i < testCount; ++i)
    {
        myArray<int> array(i);
        for (int j = 0; j < i; ++j) {array.insert(j);}
        std::shuffle(array.data(), array.data() + array.size(), rd);
        results.insert(benchmark([&]()
        {
            qsortImproved(array);
        }) * 1e9);
    }

    // for (int i = 1; i < testCount; ++i)
    // {
    //     myArray<int> array(i);
    //     for (int j = 0; j < i; ++j) {array.insert(j);}
    //     std::shuffle(array.data(), array.data() + array.size(), rd);
    //     results.insert(benchmark([&]()
    //     {
    //         insertion(array);
    //     }) * 1e9);
    // }
    for (auto i : results) std::cout << i << "\n";

    return 0;
}
