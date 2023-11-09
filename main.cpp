#include <iostream>
#include <vector>
#include "polynom.h"
#include "mathFunc.h"
using namespace std;

Polynomial nod_polynom(Polynomial poly_m, Polynomial poly_n) {
    if (poly_m.degree() == 0) {
        return poly_n;
    }
    else if (poly_n.degree() == 0) {
        return poly_m;
    }
    return nod_polynom(poly_n, poly_m.ost_div_pp(poly_n));
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<pair<int, int>> coefficients1 = { {1, 1}, {6,1}, {11,1}, {6,1} };
    //vector<pair<int, int>> coefficients2 = { {1, 2}, {2, 1}, {4, 2} };
    vector<pair<int, int>> coefficients2 = { {1, 1}, {7,1}, {14,1}, {8,1} };
    //vector<pair<int, int>> coefficients2 = { {-2,1}, {-3, 1}, {-12,1}, {1,1} };
    Polynomial poly1(coefficients1);
    Polynomial poly2(coefficients2);
    Polynomial poly_ans = nod_polynom(poly1,poly2);//2x^2-x

    //cout << poly_ans.degree() << "\n";
    if (poly_ans.poly_empty()) {
        cout << "P(x) = 0" << "\n";
        return 0;
    }
    std::cout << "P(x) = " << poly_ans.visual() << "\n";
    //poly1.simplify();
    //poly2.simplify();
    //Polynomial poly3 = poly1 + poly2;
    //poly3.norm_polynom();
    //std::cout << poly3.visual() << "\n";
    //std::cout << poly3.degree() << "\n";
    //Polynomial poly3 = poly1.mul_pol(poly2);
    //std::cout << poly3.visual() << "\n";
    /*std::cout << poly1.visual() << "\n";
    poly1.simplify();
    std::cout << poly1.visual() << "\n";
    std::cout << poly2.visual() << "\n";
    Polynomial poly3 = poly1 + poly2;
    std::cout << poly3.visual() << "\n";
    std::cout << addFractions({ 1,2 }, { 2,4 }, false).first << "/" << addFractions({1,2}, {2,4}, false).second;
    */
    //poly1.nod_nok();
    return 0;
}