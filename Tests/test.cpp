#include "pch.h"
#include "../lab2/MyArray.h"
#include "../lab3/quicksort.h"
#include "../lab4/Dice.h"
TEST(Dice, CapacityIncrease)
{
    Dice dice;
    //init capacity == 8, mult by 1.6 to increase [ int (8 * 1.6) == 12 ] 
    dice.load("1d6,1d6+2,2d8,10d6,1d6+2,2d8,10d6,1d6+2,2d8,10d6");
    EXPECT_EQ(dice.getDice()->capacity(), 12);
}

TEST(Dice, EmptyRollTest)
{
    Dice dice;
    std::cout << dice.roll() << std::endl;
    EXPECT_EQ(dice.roll(), 0);
}

TEST(Dice, InsertDie)
{
    Dice dice;
    dice.insert(Die(3,6,2));
    auto result = dice.roll();
    std::cout << result << std::endl;
    EXPECT_TRUE(result >= 5 && result <= 20);
}


TEST(Array, foreach)
{
    myArray<Die> arr{};
    for (int i = 0; i < arr.capacity(); ++i)
    {
        arr.insert(Die());
    }
    for (auto i : arr) std::cout << i.getQuantity()<< " " << i.getFaces() << " " << i.getModifier() << "\n";
}

TEST(Array, iter)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    myArray<int> arr{};
    for (int i = 0; i < arr.capacity(); ++i)
    {
        arr.insert(i);
    }
    std::shuffle(arr.begin(), arr.end(), rd);
    std::sort(arr.begin(), arr.end());
    for (auto i : arr) std::cout << i << " ";
    std::cout << "\n";
    EXPECT_EQ(arr[arr.size() - 1], arr.size() - 1);
    
}

TEST(Array, ConstIter)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    myArray<int> arr{};
    for (int i = 0; i < arr.capacity(); ++i)
    {
        arr.insert(i);
    }
    for (auto it = arr.cbegin(); it != arr.cend(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";
    EXPECT_EQ(arr[arr.size() - 1], arr.size() - 1);
}

TEST(Array, ReverseIter)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    myArray<int> arr{};
    for (int i = 0; i < arr.capacity(); ++i)
    {
        arr.insert(i);
    }
    auto it1 = arr.rbegin();
    auto it2 = arr.rend();
    std::shuffle(it1, it2, rd);
    std::sort(it1, it2);
    for (const auto& i : arr) std::cout << i << " ";
    std::cout << "\n";
    EXPECT_EQ(arr[arr.size() - 1], arr.size() - 1);
}

TEST(Array, ReverseConstIter)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    myArray<int> arr{};
    for (int i = 0; i < arr.capacity(); ++i)
    {
        arr.insert(i);
    }
    for (auto it = arr.crbegin(); it != arr.crend(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";
    EXPECT_EQ(arr[arr.size() - 1], arr.size() - 1);
}