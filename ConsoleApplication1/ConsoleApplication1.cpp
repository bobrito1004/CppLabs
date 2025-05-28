#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../lab2/MyArray.h"


class Person
{
public:
    Person()
    {
        std::cout << age << " created v1\n";
    }

    Person(const std::string& n, const int a)
    {
        this->name = n;
        this->age = a;
        std::cout << age << " created v2\n";
    }

    Person(const Person& p)
    {
        name = p.name;
        age = p.age;
        std::cout << age << " created v3\n";
    }

    // Person& operator=(const Person& p)
    // {
    //     if (&p != this)
    //     {
    //         name = p.name;
    //         age = p.age;
    //         //Person(p.name, p.age);
    //     }
    //     return *this;
    // }

    ~Person()
    {
        std::cout << this->age << " destroyed\n";
    }

    void print(const std::vector<int>& array) const
    {
        for (auto& i : array)
            std::cout << i << " ";
    }


    std::string name = "Unknown";
    int age = 1;
};

// void myswap(int a, int b)
//// {
////     auto temp = a;
////     a = b;
////     b = temp;
////     
//// }

void myswap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void setToValue(int& a, const int& b)
{
    a = b;
}

void myswap(Person& a, Person& b) noexcept
{
    std::swap(a.name, b.name);
    std::swap(a.age, b.age);
}

int main()
{
    // Person p;
    // std::vector<Person> v;
    // v.insert(v.begin(), Person());
    // v.insert(v.end(),Person("22", 2));
    // v.insert(v.end(),Person("33", 3));
    // v.insert(v.end(),Person("44", 4));
    // v.insert(v.end(),Person("55", 5));
    // v.insert(v.end(),Person("66", 6));
    // // auto end = v.cend();
    // // auto begin = v.cbegin();
    // // std::shuffle(begin, end, std::mt19937(std::random_device()()));
    // // std::sort(v.begin(), v.end());
    // for (auto i : v)
    // {
    //     std::cout << i.age << '\n';
    // }
    //
    // for(auto i = v.cbegin(); i != v.cend(); ++i)
    // {
    //     i->age = 22;
    // }


    // std::vector<int> a {1,2,3,4,5};
    // for (const auto& i : a)
    // {
    //     i = 5;
    //     std::cout << i << " ";
    // }


    // Person p;
    // const std::vector<int> a{1, 2, 3, 4, 5};
    // p.print(a);
    // int a1 = 2;
    // cnst int a3 = 3;
    // int* a2(&a1);

    // myArray<Person> b(5);
    // Person b1("John", 30);
    // Person b2("John", 40);
    // Person b3("John", 50);
    // Person b4("John", 60);
    // Person b5("John", 70);
    // b.insert(b1);
    // b.insert(b2);
    // b.insert(b3);
    // b.insert(b4);
    // b.insert(b5);
    // for (const auto& i : b)
    // {
    //     b.insert(i);
    // }
    // for (auto i : a)
    // {
    //     std::cout << i << " ";
    // }
    // b.clear();
    // for (const auto& i : b) std::cout << i.age << " ";
    myArray<int> a(5);
    std::cout << "\n";
    for (int i = 0; i < 10; i++) a.insert(i);
    std::cout << "\n";
    for (auto& i : a)
    {
        a.insert(i);
        std::cout << i << "\n";
    }
}
