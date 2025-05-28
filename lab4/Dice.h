#pragma once
#include <string>
#include "../lab2/MyArray.h"
#include "random"



class Die
{
public:
    Die() = default;

    Die(const int& q, const int& f, const int& m) : quantity(q), faces(f), modifier(m)
    {
    }

    [[nodiscard]] int getFaces() const { return faces; }
    [[nodiscard]] int getQuantity() const { return quantity; }
    [[nodiscard]] int getModifier() const { return modifier; }

private:
    int quantity = 1, faces = 6, modifier = 0;
};

class Dice
{
public:
    void load(const std::string& string)
    {
        dice.clear();
        std::string die[3]{};
        int idx = 0;
        for (const auto& ch : string)
        {
            switch (ch)
            {
            case 'd':
                idx = 1;
                break;
            case '-':
            case '+':
                idx = 2;
                die[idx] += ch;
                break;
            case ',':
                if (die[2].empty()) die[2] = "0";
                dice.insert(Die(std::stoi(die[0]), std::stoi(die[1]), std::stoi(die[2])));
                die[0] = "";
                die[1] = "";
                die[2] = "";
                idx = 0;
                break;
            default:
                die[idx] += ch;
                break;
            }
        }
        if (die[2].empty()) die[2] = "0";
        dice.insert(Die(std::stoi(die[0]), std::stoi(die[1]), std::stoi(die[2])));
    }

    [[nodiscard]] int roll(const myArray<Die>& set) const
    {
        if (!dice.size()) return 0;
        std::random_device rd;
        std::mt19937 gen(rd());
        int result = 0;
        for (const auto& die : set)
        {
            std::uniform_int_distribution<> roll(1, die.getFaces());
            for (int i = 0; i < die.getQuantity(); ++i)
            {
                result += roll(gen);
            }
            result += die.getModifier();
        }
        return result;
    }

    [[nodiscard]] int roll() const
    {
        auto& set = this->dice;
        return roll(set);
    }

    std::string getSet()
    {
        std::string string{};
        if (dice.size() == 0)
            return string;
        for (const auto& die : dice)
        {
            string += std::to_string(die.getQuantity());
            string += 'd';
            string += std::to_string(die.getFaces());
            if (die.getModifier() != 0)
            {
                string += '+';
                string += std::to_string(die.getModifier());
            }
            string += ',';
        }
        string.pop_back();
        return string;
    }

    void insert(const int& q, const int& f, const int& m) { insert(Die(q, f, m)); }

    void insert(const Die& d)
    {
        this->dice.insert(d);
    }

    void printProbability(const int& quantity, const int& faces)
    {
        myArray<int> counter(quantity * faces);
        for (int i = 0; i < quantity * faces; i++)
        {
            counter.insert(0);
        }
        this->load(std::string(std::to_string(quantity) + "d" + std::to_string(faces)));
        for (int i = 0; i < 10000; ++i)
        {
            int test = roll();
            ++counter[test - 1];
        }
        for (int i = 0; i < quantity * faces; ++i)
        {
            std::cout << /*i + 1 << "\t" <<*/ counter[i] << std::endl;
        }
    }

    const myArray<Die>* getDice() const { return &dice; }

private:
    myArray<Die> dice = myArray<Die>(8);
};
