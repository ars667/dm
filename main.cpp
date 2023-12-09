#include "natural.h"
#include <iostream>
#include <string>

int main()
{
    std::cout << "???????:" << '\n'
              << "0 ??? ?????? ? ???????????? ???????"
              << '\n'
              << "1 ??? ?????? ? ?????? ???????" << '\n'
              << "2 ??? ?????? ? ????????????? ???????" << '\n'
              << "3 ??? ?????? ? ??????????";

    int choose = 0;
    std::cin >> choose;
    switch (choose)
    {
    case 0:
        std::cout << "??????? ??? ?????" << '\n';
        std::string a;
        std::string b;
        std::cin >> a;
        std::cin >> b;
        Natural nat1(a);
        Natural nat2(b);
        std::cout << "???????:" << '\n'
                  << "+ ??? ???????? ???? ?????" << '\n'
                  << "- ??? ????????? ???? ?????"
                  << '\n'
                  << "* ??? ????????? ???? ?????" << '\n'
                  << "> ??? ????????? ???? ?????"
                  << '\n'
                  << "/ ??? ??????? ? ???????? ???? ?????" << '\n';
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