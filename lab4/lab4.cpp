#include <iostream>
#include <ostream>
#include <random>
#include <string>
#include "dice.h"


int main(int argc, char* argv[])
{
    Dice test;
    // std::cout << test.roll() << "\n";
    // test.insert(Die(3, 6, 2));
    // test.insert(Die(3, 6, 2));
    // test.insert(Die());
    // std::cout << test.getSet() << '\n';
    // test.load(std::string("1d6"));
    // std::cout << test.getSet() << '\n';
    // std::cout << test.roll() << "\n";
    test.printProbability(3, 10);
    return 0;
}
