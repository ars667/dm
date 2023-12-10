#include <iostream>
#include <vector>
#include <fstream>
#include "polynomial.h"
using namespace std;

Polynomial nod_polynom(Polynomial poly_m, Polynomial poly_n) {
    if (poly_m.poly_empty()) {
        //cout << "poly_m = " << poly_m.visual() << "\n";
        return poly_n;
    }
    else if (poly_n.poly_empty()) {
        //cout << "poly_m = " << poly_m.visual() << "\n";
        //cout << "poly_n = " << poly_n.visual() << "\n";
        return poly_m;
    }
    return nod_polynom(poly_n, poly_n.ost_div_pp(poly_m));
}
Polynomial read_poly() {
    vector <Rational> coef;
    std::string s;
    std::cout << "Input polynom (enter the coefficient starting from the oldest; end of input character q):\n";
    std::cin >> s;
    while (s != "q") {
        coef.push_back(Rational(s));
        std::cin >> s;
    }
    return Polynomial(coef);
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
            Polynomial poly3 = poly1.mul_pol(poly2);
            std::cout << "Result is ";
            poly3.visual();
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
            Polynomial poly3 = poly1.ost_div_pp(poly2);
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
            poly.leadingCoefficientNum();
            break;
        }
        case 'g':
        {
            std::cout << "Enter two polynomials:\n";
            Polynomial poly1 = read_poly();
            poly1.visual();
            Polynomial poly2 = read_poly();
            poly2.visual();
            Polynomial poly3 = nod_polynom(poly1,poly2);
            std::cout << "Result is ";
            poly3.visual();
            break;
        }
        default:
            break;
        }
    }

};
int main() {
    setlocale(LC_ALL, "Russian");
    poly_func();
    return 0;
}