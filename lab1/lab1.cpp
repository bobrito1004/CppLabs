#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>

int main()
{
    //random gen
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned short> acre_yield(1, 6);
    std::uniform_int_distribution<unsigned short> acre_price(17, 26);
    std::uniform_int_distribution<unsigned short> plague_chance(0, 99);


    int population = 100;
    int stock = 2800;
    int acres = 1000;
    int acrePrice = 26;
    int acreYield = 3;
    int populationStarved = 0;
    int populationNew = 5;
    int stockEaten = 200;
    int acresToBuy = 0;
    int acresToSell = 0;
    int stockToFeed = 0;
    int acresToSeed = 0;
    float starvedPercent = 0.0;
    short year = 0;
    bool plague = false;
    bool starvation = false;

    //ask to read save from file
    std::fstream fs("saveFile.txt");
    if (fs)
    {
        for (char i;;)
        {
            system("cls");
            std::cout << "load last game? y/n ";
            std::cin >> i;
            if (std::isalpha(i) && i == 'y')
            {
                fs >> population >> stock >> acres >> acrePrice >> acreYield >> populationStarved >>
                    populationNew >> stockEaten >> year >> plague >> starvedPercent;
                break;
            }
            if (std::isalpha(i) && i == 'n')
            {
                std::remove("saveFile.txt");
                break;
            }
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }
    }
    fs.close();
    while (year < 10)
    {
        system("cls");
        //turn output
        std::cout <<
            "HAMMURABI:I BEG TO REPORT TO YOU,\n"
            "IN YEAR " << ++year << ", " << populationStarved << " PEOPLE STARVED, "
            << populationNew << " CAME TO THE CITY.\n";
        if (plague)
        {
            std::cout << "A HORRIBLE PLAGUE STRUCK! HALF THE PEOPLE DIED.\n";
        }
        std::cout <<
            "POPULATION IS NOW " << population << ".\n"
            "THE CITY NOW OWNS " << acres << " ACRES.\n"
            "YOU HARVESTED " << acreYield << " BUSHELS PER ACRE.\n"
            "RATS ATE " << stockEaten << " BUSHELS.\n"
            "YOU NOW HAVE " << stock << " BUSHELS IN STORE.\n"
            "LAND IS TRADING AT " << acrePrice << " BUSHELS PER ACRE.\n";

        plague = false;
        ///input 
        for (;;)
        {
            std::cout << "\nHOW MANY ACRES DO YOU WISH TO BUY? ";
            std::cin >> acresToBuy;
            if (acresToBuy * acrePrice <= stock)
            {
                acres += acresToBuy;
                stock -= acresToBuy * acrePrice;
                break;
            }
            std::cout <<
                "HAMMURABI: THINK AGAIN. YOU HAVE ONLY\n"
                << stock << " BUSHELS OF GRAIN. NOW THEN,";
        }
        for (;;)
        {
            std::cout << "\nHOW MANY ACRES DO YOU WISH TO SELL? ";
            std::cin >> acresToSell;
            if (acresToSell <= acres)
            {
                acres -= acresToSell;
                stock += acresToSell * acrePrice;
                break;
            }
            std::cout << "HAMMURABI: THINK AGAIN. YOU HAVE ONLY " << acres << " ACRES. NOW THEN,";
        }
        for (;;)
        {
            std::cout << "\nHOW MANY BUSHELS DO YOU WISH TO FEED YOUR PEOPLE? ";
            std::cin >> stockToFeed;
            if (stockToFeed <= stock)
            {
                stock -= stockToFeed;
                break;
            }
            std::cout << "HAMMURABI: THINK AGAIN. YOU HAVE ONLY " << stock << " BUSHELS OF GRAIN. NOW THEN,";
        }
        for (;;)
        {
            std::cout << "\nHOW MANY ACRES DO YOU WISH TO PLANT WITH SEED? ";
            std::cin >> acresToSeed;
            if (acresToSeed <= acres)
            {
                if (acresToSeed >> 1 <= stock)
                {
                    stock -= acresToSeed >> 1;
                    break;
                }
                std::cout << "HAMMURABI: THINK AGAIN. YOU HAVE ONLY " << stock << " BUSHELS OF GRAIN. NOW THEN,";
                continue;
            }
            std::cout << "HAMMURABI: THINK AGAIN. YOU OWN ONLY " << acres << " ACRES. NOW THEN,";
        }
        //сборы бушелей
        acreYield = acre_yield(gen);
        stock += acreYield * std::min(population * 10, acres);
        //крысы
        std::uniform_int_distribution<unsigned short> stock_eaten(0, static_cast<uint16_t>(stock * 0.07));
        stockEaten = stock_eaten(gen);
        stock -= stockEaten;
        //жители кушают (или нет)
        if (stockToFeed / 20 < population)
        {
            populationStarved = population - stockToFeed / 20;
            starvedPercent += static_cast<float>(populationStarved) / static_cast<float>(population);
            if (populationStarved >= static_cast<int>(population * 0.45))
            {
                starvation = true;
                break;
            }

            population -= populationStarved;
        }
        else
        {
            populationStarved = 0;
        }
        //people came
        populationNew = std::min(50, std::max(
                                     0, (populationStarved >> 1) + acreYield * stock / 1000 + 1));
        population += populationNew;
        //чума
        plague = plague_chance(gen) < 15;
        if (plague) population = population >> 1;
        //save to file
        fs.open("saveFile.txt", std::ios::out);
        fs << population << " " << stock << " " << acres << " " << acrePrice << " " << acreYield << " "
            << populationStarved << " " << populationNew << " " << stockEaten << " " << year << " "
            << plague << " " << starvedPercent;
        fs.close();

        acrePrice = acre_price(gen);
    }
    if (starvation)
    {
        std::cout <<
            "\nYOU STARVED " << populationStarved << " IN ONE YEAR!!!"
            "\nDUE TO THIS EXTREME MISMANAGEMENT YOU HAVE NOT ONLY"
            "\nBEEN IMPEACHED AND THROWN OUT OF OFFICE BUT YOU HAVE"
            "\nALSO BEEN DECLARED NATIONAL FINK!!!\n\n";
        system("pause");
        return 0;
    }
    std::remove("saveFile.txt");
    system("cls");
    float P = starvedPercent / 10;
    int P_grade;
    if (P <= 0.03)
    {
        P_grade = 0;
    }
    else if (P <= 0.1)
    {
        P_grade = 1;
    }
    else if (P <= 0.33)
    {
        P_grade = 2;
    }
    else
    {
        P_grade = 3;
    }

    int L = acres / population;
    int L_grade = 10 - std::min(10, std::max(6, L));
    std::cout << "congratulations!\n" << "P = " << P << ", L = " << L << "\n";
    switch (std::max(L_grade, P_grade))
    {
    case 0:
        std::cout << "aaa\n";
        break;
    case 1:
        std::cout << "bbb\n";
        break;
    case 2:
    case 3:
        std::cout << "ccc\n";
        break;
    case 4:
        std::cout << "ddd\n";
        break;
    default:
        break;
    }
    system("pause");
    return 0;
}
