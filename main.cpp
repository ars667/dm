#include "natural.h"
#include <iostream>
#include <string>

int main()
{
    std::cout << "Введите:" << '\n'
              << "0 для работы с натуральными числами"
              << '\n'
              << "1 для работы с целыми числами" << '\n'
              << "2 для работы с рациональными числами" << '\n'
              << "3 для работы с полиномами";

    int choose = 0;
    std::cin >> choose;
    switch (choose)
    {
    case 0:
        std::cout << "Введите два числа" << '\n';
        std::string a;
        std::string b;
        std::cin >> a;
        std::cin >> b;
        Natural nat1(a);
        Natural nat2(b);
        std::cout << "Введите:" << '\n'
                  << "+ для сложения двух чисел" << '\n'
                  << "- для вычитания двух чисел"
                  << '\n'
                  << "* для умножения двух чисел" << '\n'
                  << "> для сравнения двух чисел"
                  << '\n'
                  << "/ для деления с остатком двух чисел" << '\n';
        char operation;
        std::cin >> operation;
        switch (operation)
        {
        case '+':
        {

            Natural nat3 = nat1 + nat2;
            nat3.print();
            break;
        }
        case '-':
        {

            Natural nat3 = nat1 - nat2;
            nat3.print();
            break;
        }

        case '*':
        {
            Natural nat3 = nat1 * nat2;
            nat3.print();
            break;
        }

        case '>':
        {
            int nat3 = nat1 > nat2;
            std::cout << nat3;
            break;
        }

        case '/':
        {
            Natural nat3 = nat1 / nat2;
            Natural nat4 = nat1 % nat2;
            nat3.print();
            nat4.print();
            break;
        }
        default:
            break;
        }
        break;

    //default:
      //  break;
    }

    return 0;
}
