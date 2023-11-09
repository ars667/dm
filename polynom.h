#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>


class Polynomial {
private:
    std::vector<std::pair<int, int>> coef; // Вектор пар (числитель, знаменатель)
    // Вынесение НОК знаменателей и НОД числителей
    std::pair<int, int> calculateLCMandGCD();
public:
    //Конструктор, ввод: вектор коэффициентов от n до 0
    Polynomial(std::vector<std::pair<int, int>> coefficients);

    std::vector<std::pair<int, int>> get_coef();

    // Сложение двух многочленов
    Polynomial operator+(const Polynomial& other);

    // Вычитание двух многочленов
    Polynomial operator-(const Polynomial& other);

    // Умножение многочлена на рациональное число(только справо)
    Polynomial operator*(int scalar) const;

    Polynomial operator*(std::pair<int, int> fraction) const;

    // Умножение многочлена на x^k Особенности: возвращает новый полином, не меняя текущий
    Polynomial multiplyByXk(int k) const;

    // Нахождение старшего коэффициента многочлена
    std::pair<int, int> leadingCoefficientPair();

    double leadingCoefficientNum();

    // Нахождение степени многочлена
    size_t degree() const;

    void nod_nok();
    void simplify();

    // Упростить многочлен: объединить одинаковые степени и удалить нулевые коэффициент
    std::string visual();

    //сложение многочленов
    Polynomial add_polynom(Polynomial poly1, Polynomial poly2, bool minus);
    //умножение многочленов
    Polynomial mul_pol(Polynomial poly1);
    //частное многочленов
    Polynomial DIV_PP_P(Polynomial poly);
    //производная многочлена
    Polynomial DER_P_P();

    bool poly_empty();
    void norm_polynom();

    Polynomial ost_div_pp(Polynomial poly);

    //Polynomial nod_polynom(Polynomial poly);
};
