#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include "Rational.h"


class Polynomial : public Rational {
private:
    std::vector<Rational> coef; // Вектор пар (числитель, знаменатель)
    // Вынесение НОК знаменателей и НОД числителей
    Rational calculateLCMandGCD();
public:
    //Конструктор, ввод: вектор коэффициентов от n до 0
    Polynomial(std::vector<Rational> coefficients);

    std::vector<Rational> get_coef();

    // Сложение двух многочленов
    Polynomial operator+(const Polynomial& other);

    // Вычитание двух многочленов
    Polynomial operator-(const Polynomial& other);

    //умножение на дробь справа
    Polynomial operator*(Rational a) const;

    // Умножение многочлена на x^k Особенности: возвращает новый полином, не меняя текущий
    Polynomial multiplyByXk(int k) const;

    // Нахождение старшего коэффициента многочлена
    Rational leadingCoefficientNum();

    // Нахождение степени многочлена
    int degree() const;

    void nod_nok();

    // Упростить многочлен: объединить одинаковые степени и удалить нулевые коэффициент
    void visual();

    //сложение многочленов
    Polynomial add_polynom(Polynomial poly1, Polynomial poly2, bool minus);
    //умножение многочленов
    Polynomial mul_pol(Polynomial poly1);
    //частное многочленов
    Polynomial DIV_PP_P(Polynomial poly);
    //производная многочлена
    Polynomial DER_P_P();

    //проверка многочлена на тождественный 0
    bool poly_empty();

    //убирает незначащие нулевые коэффициенты при старших степенях
    void norm_polynom();

    //возвращает остаток при делении многочлена
    Polynomial ost_div_pp(Polynomial poly);
};