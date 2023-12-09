#include "natural.h"
#include <iostream>
#include <string>

void nat_func()
{
    std::cout << "please, enter 2 numbers" << '\n';
    std::string a;
    std::string b;
    std::cin >> a;
    std::cin >> b;
    Natural nat1(a);
    Natural nat2(b);
    std::cout << "enter:" << '\n'
              << "+" << '\n'
              << "-"
              << '\n'
              << "*" << '\n'
              << "> (2 - >, 1 - <, 0 - =)"
              << '\n'
              << "/ (first num - result, second - mod)" << '\n';
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
};

void int_func()
{
    std::cout << "please, enter 2 numbers" << '\n';
    std::string a;
    std::string b;
    std::cin >> a;
    std::cin >> b;
    Natural nat1(a);
    Natural nat2(b);
    std::cout << "enter:" << '\n'
              << "+" << '\n'
              << "-"
              << '\n'
              << "*" << '\n'
              << "> (2 - >, 1 - <, 0 - =)"
              << '\n'
              << "/ (first num - result, second - mod)" << '\n';
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

};

int main()
{
    std::cout << "enter, please:\n"
              << "0 - natural\n"
              << "1 - integer\n"
              << "2 - rational\n"
              << "3 - polynom\n";

    int choose = 0;
    std::cin >> choose;
    switch (choose)
    {
    case 0:
        nat_func();
        break;
    case 1:
        int_func();
        break;
    /*
    case 2:
        rat_func();
        break;
    case 3:
        pol_func();
        break;
    */
    default:
        break;
    }
    return 0;
}
