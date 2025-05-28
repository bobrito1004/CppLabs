#include <iostream>
#include <string>
#include <vector>
#include "MyArray.h"

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
    

    ~Person()
    {
        std::cout << this->age << " destroyed\n";
    }

    

    std::string name = "Unknown";
    int age = 1;
};


int main()
{

    // myArray<Person> array(5);
    // std::cout << "insert\n";
    // array.insert(Person());
    // array.insert(Person("22", 2));
    // array.insert(Person ("33", 3));
    // array.insert(Person ("44", 4));
    // array.insert(Person ("55", 5));
    // array.insert(Person ("66", 6));
    // std::cout << "remove\n";
    // array.remove(2);
    // std::cout << "sss\n";
    // array.insert(Person());
    // array.insert(Person("22", 2));
    // array.insert(Person ("33", 3));
    // array.insert(Person ("44", 4));
    // array.insert(Person ("55", 5));
    // array.insert(Person ("623", 6));
    // std::cout << "init second" << "\n";
    // myArray second(array);
    // std::cout <<"end\n";
    // auto it = second.cend();
    // std::cout << "it test " << it.get().age << "\n";
    //
    // //
    // for (auto i = array.cbegin(); i != array.cend(); i.next())
    // {
    //     std::cout << i->age<< "\n";
    // }
    //
    // for (auto& p : array)
    // {
    //     std::cout << p.age << " ";
    // }
    // std::cout << "\n";


    
    // for (auto i = second.rbegin(); i != second.rend(); i.next())
    // {
    //     std::cout << i->name << " ";
    // }
    // std::cout << "\n";
    // for (int i = 0; i < array.size(); i++)
    // {
    //     std::cout << array[i].age << " " << array[i].name << '\n';
    // }

    // for (const auto& a:second)
    // {
    //     std::cout << a.name << " ";
    // }
    // std::cout << "\n";
    //
    //
    // for (const auto& a:second)
    // {
    //     std::cout << a.age << " ";
    // }
    // std::cout << "\n";


    // array<int> arr(5);
    // for (int i = 0; i <= 8; ++i)
    // {
    //     arr.insert(i + 100);
    //     std::cout << arr[i]<< '\n';
    // }
    // std::cout << "\n\n";
    // arr.insert(4, 555);
    // std::cout << arr[4] << '\n';
    // arr.remove(4);
    // std::cout << arr[0] << '\n';

    //
    // myArray<int> a;
    // for (int i = 0; i < 10; ++i)
    //     a.insert(i + 1);
    // for (int i = 0; i < a.size(); ++i)
    //     a[i] *= 2;
    // for (auto it = a.begin(); it.hasNext(); it.next())
    //     std::cout << it.get() << '\n';
    // std::cout << "////////////" << '\n';
    // for (auto it : a)
    //     std::cout << it << '\n';

    myArray<myArray<int>> b(3);
    b.insert(myArray<int> (3));
    b.insert(myArray<int> (3));
    b.insert(myArray<int> (3));

    std::vector<std::vector<int>> v(3);
    
    b[0].insert(1);
    b[0].insert(2);
    b[0].insert(3);
    
    b[1].insert(1);
    b[1].insert(2);
    b[1].insert(3);

    
    b[2].insert(1);
    b[2].insert(2);
    b[2].insert(3);

    
    for (auto j : b)
    {
        std::cout << "1\n";
        for (const auto& i : b)
        {
            std::cout << "2 ";
  
        }
        std::cout << "\n";
    }


    

}
