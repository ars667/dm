#include "Natural.h"
#include "Integer.h"
#include "Rational.h"
#include "Polynomial.h"
#include <iostream>
#include <string>
#include <vector>
void nat_func();
void int_func();
void rat_func();
void poly_func();
int main()
{
    std::cout
        << "0 - natural" << '\n'
        << "1 - integer" << '\n'
        << "2 - rational" << '\n'
        << "3 - polynom" << '\n'
        << "enter, please: _" << '\b';

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
    case 2:
        rat_func();
        break;
    case 3:
        poly_func();
        break;
    default:
        break;
    }
    return 0;
}

Polynomial read_poly() {
    std::string s;
    std::cout << "Input polynom (enter the coefficient starting from the oldest; end of input character q):\n";
    std::cin >> s;
    return Polynomial(s);
}
Rational read_rational() {
    Rational coef;
    std::string s;
    std::cout << "Input rational:\n";
    std::cin >> s;
    return Rational(s);
}
void poly_func()
{
    std::cout << "There are 8 modules of class Polinamial:" << '\n'
        << "ADD_PP_P(+)" << '\n'
        << "SUB_PP_P(-)" << '\n'
        << "MUL_PQ_P(r)" << '\n'
        << "FAC_P_Q(f)" << '\n'
        << "MUL_PP_P(*)" << '\n'
        << "DIV_PP_P(/)" << '\n'
        << "MOD_PP_P(%)" << '\n'
        << "GCF_PP_P(g)" << '\n'
        << "NMR_P_P(k)" << '\n'
        << "DER_P_P(')" << '\n';
    char operation = 'o';
    while (operation != 'q')
    {
        std::cout << "Enter (___) value in brackets or Quit(q): _\b";
        std::cin >> operation;
        std::cout << "\n";
        switch (operation)
        {
        case '+':
        {
            std::cout << "Enter two polynomials:\n";
            Polynomial poly1 = read_poly();
            poly1.visual();
            Polynomial poly2 = read_poly();
            poly2.visual();
            Polynomial poly3 = poly1 + poly2;
            std::cout << "Result is ";
            poly3.visual();
            break;
        }
        case '-':
        {
            std::cout << "Enter two polynomials:\n";
            Polynomial poly1 = read_poly();
            poly1.visual();
            Polynomial poly2 = read_poly();
            poly2.visual();
            Polynomial poly3 = poly1 - poly2;
            std::cout << "Result is ";
            poly3.visual();
            break;
        }

        case '*':
        {
            std::cout << "Enter two polynomials:\n";
            Polynomial poly1 = read_poly();
            poly1.visual();
            Polynomial poly2 = read_poly();
            poly2.visual();
            Polynomial poly3 = poly1.MUL_PP_P(poly2);
            std::cout << "Result is ";
            poly3.visual();
            break;
        }
        case 'k':
        {
            std::cout << "Enter polynomial:\n";
            Polynomial poly = read_poly();
            poly.visual();
            Polynomial poly_res = poly.NMR_P_P();
            std::cout << "Result is ";
            poly_res.visual();
            break;
        }

        case '/':
        {
            std::cout << "Enter two polynomials:\n";
            Polynomial poly1 = read_poly();
            poly1.visual();
            Polynomial poly2 = read_poly();
            poly2.visual();
            Polynomial poly3 = poly1.DIV_PP_P(poly2);
            std::cout << "Result is ";
            poly3.visual();
            break;
        }

        case '\'':
        {
            std::cout << "Enter polynomial:\n";
            Polynomial poly = read_poly();
            poly.visual();
            Polynomial poly_res = poly.DER_P_P();
            std::cout << "Result is ";
            poly_res.visual();
            break;
        }
        case '%':
        {
            std::cout << "Enter two polynomials:\n";
            Polynomial poly1 = read_poly();
            poly1.visual();
            Polynomial poly2 = read_poly();
            poly2.visual();
            Polynomial poly3 = poly1.MOD_PP_P(poly2);
            std::cout << "Result is ";
            poly3.visual();
            break;
        }
        case 'r':
        {
            std::cout << "Enter polynomial:\n";
            Polynomial poly = read_poly();
            poly.visual();
            Rational coef = read_rational();

            Polynomial poly_res = poly * coef;
            std::cout << "Result is ";
            poly_res.visual();
            break;
        }
        case 'f':
        {
            std::cout << "Enter polynomial:\n";
            Polynomial poly = read_poly();
            poly.visual();
            poly.nod_nok();
            break;
        }
        case 'g':
        {
            std::cout << "Enter two polynomials:\n";
            Polynomial poly1 = read_poly();
            poly1.visual();
            Polynomial poly2 = read_poly();
            poly2.visual();
            Polynomial poly3 = poly1.nod_polynom(poly1, poly2);
            std::cout << "Result is ";
            poly3.visual();
            break;
        }
        default:
            break;
        }
    }

};
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
    std::cout << "There are 10 modules of class Integer:" << '\n'
        << "ABS_Z_N(b) \t get absolute value in Natural" << '\n'
        << "POZ_Z_D(p) \t positive or negative" << '\n'
        << "MUL_ZM_Z(-) \t change sign to opposite" << '\n'
        << "TRANS_N_Z(n) \t change Natural object to Integer" << '\n'
        << "TRANS_Z_N(z) \t change Integer object to Natural" << '\n'
        << "ADD_ZZ_Z(a) \t add one Integer to another" << '\n'
        << "SUB_ZZ_Z(s) \t substitute Inegers" << '\n'
        << "MUL_ZZ_Z(u) \t multiply Integers" << '\n'
        << "DIV_ZZ_Z(d) \t divide Integers" << '\n'
        << "MOD_ZZ_Z(m) \t get the remainder from division" << '\n';
    char operation = 'o';
    while (operation != 'q')
    {
        std::cout << "Enter (___) value in brackets or Quit(q): _\b";
        std::cin >> operation;
        std::cout << "\n";
        switch (operation)
        {
        case 'b':
        {
            std::cout << "You choose ABS_Z_N(b) - get absolute value in Natural!" << '\n'
                << "Enter one Integer: ___\b\b\b";
            std::string intAs;
            std::cin >> intAs;
            Integer intA = Integer(intAs);
            std::cout << "Result is " << intA.ABS_Z_N().str_() << "\n";
            break;
        }
        case 'p':
        {
            std::cout << "You choose POZ_Z_D(p) - positive or negative" << '\n'
                << "Enter one Integer: ___\b\b\b";
            std::string intAs;
            std::cin >> intAs;
            Integer intA = Integer(intAs);
            if (intA.POZ_Z_D() == 2)
                std::cout << intA.str_() << " - positive!" << "\n";
            else if (intA.POZ_Z_D() == 1)
                std::cout << intA.str_() << " - negative!" << "\n";
            else
                std::cout << intA.str_() << " - is null!" << "\n";
            break;
        }

        case '-':
        {
            std::cout << "You choose MUL_ZM_Z(-) - change sign to opposite" << '\n'
                << "Enter one Integer: ___\b\b\b";
            std::string intAs;
            std::cin >> intAs;
            Integer intA = Integer(intAs);
            std::cout << "Result is " << intA.MUL_ZM_Z().str_() << "\n";
            break;
        }

        case 'n':
        {
            std::cout << "You choose TRANS_N_Z(n) - change Natural object to Integer" << '\n'
                << "Enter one Natural: ___\b\b\b";
            std::string natAs;
            std::cin >> natAs;
            Natural natA = Natural(natAs);
            Integer intA;
            intA = intA.TRANS_N_Z(natA);
            std::cout << "Result is " << intA.str_() << "\n";
            break;
        }

        case 'z':
        {
            std::cout << "You choose TRANS_Z_N(z) - change Integer object to Natural" << '\n'
                << "Enter one Integer: ___\b\b\b";
            std::string intAs;
            std::cin >> intAs;
            Integer intA = Integer(intAs);
            if (intA.POZ_Z_D() == 1)
                std::cout << "Your integer is negative! Can't transform to Natural without sign loss!" << "\n";
            else
                std::cout << "Result is " << intA.TRANS_Z_N(intA).str_() << "\n";
            break;
        }
        case 'a':
        {
            std::cout << "You choose ADD_ZZ_Z(a) - add one Integer to another" << '\n'
                << "Enter one Integer: ___\b\b\b";
            std::string intAs;
            std::cin >> intAs;
            std::cout << "Enter another Integer: ___\b\b\b";
            std::string intBs;
            std::cin >> intBs;
            Integer intA = Integer(intAs);
            Integer intB = Integer(intBs);
            std::cout << intA.str_() << " + " << intB.str_() << " = " << intA.ADD_ZZ_Z(intB).str_() << "\n";
            break;
        }
        case 's':
        {
            std::cout << "You choose SUB_ZZ_Z(s) - substitute Inegers" << '\n'
                << "Enter one Integer: ___\b\b\b";
            std::string intAs;
            std::cin >> intAs;
            std::cout << "Enter another Integer: ___\b\b\b";
            std::string intBs;
            std::cin >> intBs;
            Integer intA = Integer(intAs);
            Integer intB = Integer(intBs);
            std::cout << intA.str_() << " - " << intB.str_() << " = " << intA.SUB_ZZ_Z(intB).str_() << "\n";
            break;
        }
        case 'u':
        {
            std::cout << "You choose MUL_ZZ_Z(u) - multiply Integers" << '\n'
                << "Enter one Integer: ___\b\b\b";
            std::string intAs;
            std::cin >> intAs;
            std::cout << "Enter another Integer: ___\b\b\b";
            std::string intBs;
            std::cin >> intBs;
            Integer intA = Integer(intAs);
            Integer intB = Integer(intBs);
            std::cout << intA.str_() << " * " << intB.str_() << " = " << intA.MUL_ZZ_Z(intB).str_() << "\n";
            break;
        }
        case 'd':
        {
            std::cout << "You choose DIV_ZZ_Z(d) - divide Integers" << '\n'
                << "Enter one Integer: ___\b\b\b";
            std::string intAs;
            std::cin >> intAs;
            std::cout << "Enter another Integer: ___\b\b\b";
            std::string intBs;
            std::cin >> intBs;
            Integer intA = Integer(intAs);
            Integer intB = Integer(intBs);
            std::cout << intA.str_() << " / " << intB.str_() << " = " << intA.DIV_ZZ_Z(intB).str_() << "\n";
            break;
        }
        case 'm':
        {
            std::cout << "You choose MOD_ZZ_Z(m) - get the remainder from division" << '\n'
                << "Enter one Integer: ___\b\b\b";
            std::string intAs;
            std::cin >> intAs;
            std::cout << "Enter another Integer: ___\b\b\b";
            std::string intBs;
            std::cin >> intBs;
            Integer intA = Integer(intAs);
            Integer intB = Integer(intBs);
            std::cout << intA.str_() << " / " << intB.str_() << " =(remainder) " << intA.MOD_ZZ_Z(intB).str_() << "\n";
            break;
        }
        default:
            break;
        }
    }

};

void rat_func()
{
    std::cout << "There are 8 modules of class Rational:" << '\n'
        << "RED_Q_Q(r) \t shorten the fraction" << '\n'
        << "INT_Q_B(i) \t if shortened fraction is integer?" << '\n'
        << "TRANS_Z_Q(z) \t converting an integer to a fractional number" << '\n'
        << "TRANS_Q_Z(t) \t converting a fractional number to an integer" << '\n'
        << "ADD_QQ_Q(a) \t adding fractions" << '\n'
        << "SUB_QQ_Q(s) \t subtraction of fractions" << '\n'
        << "MUL_QQ_Q(u) \t multiplication of fractions" << '\n'
        << "DIV_QQ_Q(d) \t division of fractions" << '\n';
    char operation = 'o';
    while (operation != 'q')
    {
        std::cout << "Enter (___) value in brackets or Quit(q): _\b";
        std::cin >> operation;
        std::cout << "\n";
        switch (operation)
        {
        case 'r':
        {
            std::cout << "You choose RED_Q_Q(r) \t shorten the fraction" << '\n'
                << "Enter one fraction: ___\b\b\b";
            std::string ratAs;
            std::cin >> ratAs;
            Rational ratA = Rational(ratAs);
            std::cout << "Result is " << ratA.RED_Q_Q(ratA).str_() << "\n";
            break;
        }
        case 'i':
        {
            std::cout << "You choose INT_Q_B(i) \t if shortened fraction is integer?" << '\n'
                << "Enter one fraction: ___\b\b\b";
            std::string ratAs;
            std::cin >> ratAs;
            Rational ratA = Rational(ratAs);
            ratA = ratA.RED_Q_Q(ratA);
            if (ratA.INT_Q_B(ratA) == true)
                std::cout << ratA.str_() << " - integer!" << "\n";
            else
                std::cout << ratA.str_() << " - fraction!" << "\n";
            break;
        }

        case 'z':
        {
            std::cout << "TRANS_Z_Q(z) \t converting an integer to a fractional number" << '\n'
                << "Enter one integer: ___\b\b\b";
            std::string ratAs;
            std::cin >> ratAs;
            Rational ratA = Rational(ratAs);
            std::cout << "Result is " << ratA.TRANS_Q_Z(ratA).str_() << "\n";
            break;
        }

        case 't':
        {
            std::cout << "You choose TRANS_Q_Z(t) \t converting a fractional number to an integer" << '\n'
                << "Enter one fraction: ___\b\b\b";
            std::string ratAs;
            std::cin >> ratAs;
            Rational ratA = Rational(ratAs);
            ratA = ratA.RED_Q_Q(ratA);
            if (ratA.INT_Q_B(ratA) == false)
                std::cout << "Denominator is not one!" << "\n";
            else
                std::cout << "Result is " << ratA.TRANS_Q_Z(ratA).str_() << "\n";
            break;
        }

        case 'a':
        {
            std::cout << "You choose ADD_QQ_Q(a) \t adding fractions" << '\n'
                << "Enter one fraction: ___\b\b\b";
            std::string ratAs;
            std::cin >> ratAs;
            Rational ratA = Rational(ratAs);
            std::cout << "Enter another fraction: ___\b\b\b";
            std::string ratBs;
            std::cin >> ratBs;
            Rational ratB = Rational(ratBs);
            std::cout << ratA.str_() << " + " << ratB.str_() << " = " << ratA.ADD_QQ_Q(ratB).str_() << "\n";
            break;
        }
        case 's':
        {
            std::cout << "You choose SUB_QQ_Q(s) \t subtraction of fractions" << '\n'
                << "Enter one fraction: ___\b\b\b";
            std::string ratAs;
            std::cin >> ratAs;
            Rational ratA = Rational(ratAs);
            std::cout << "Enter another fraction: ___\b\b\b";
            std::string ratBs;
            std::cin >> ratBs;
            Rational ratB = Rational(ratBs);
            std::cout << ratA.str_() << " - " << ratB.str_() << " = " << ratA.SUB_QQ_Q(ratB).str_() << "\n";
            break;
        }
        case 'u':
        {
            std::cout << "You choose MUL_QQ_Q(u) \t multiplication of fractions" << '\n'
                << "Enter one fraction: ___\b\b\b";
            std::string ratAs;
            std::cin >> ratAs;
            Rational ratA = Rational(ratAs);
            std::cout << "Enter another fraction: ___\b\b\b";
            std::string ratBs;
            std::cin >> ratBs;
            Rational ratB = Rational(ratBs);
            std::cout << ratA.str_() << " * " << ratB.str_() << " = " << ratA.MUL_QQ_Q(ratB).str_() << "\n";
            break;
        }
        case 'd':
        {
            std::cout << "You choose DIV_QQ_Q(d) \t division of fractions" << '\n'
                << "Enter one fraction: ___\b\b\b";
            std::string ratAs;
            std::cin >> ratAs;
            Rational ratA = Rational(ratAs);
            std::cout << "Enter another fraction: ___\b\b\b";
            std::string ratBs;
            std::cin >> ratBs;
            Rational ratB = Rational(ratBs);
            std::cout << ratA.str_() << " / " << ratB.str_() << " = " << ratA.DIV_QQ_Q(ratB).str_() << "\n";
            break;
        }

        default:
            break;
        }
    }

};

