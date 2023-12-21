#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include "Rational.h"
#include <utility>
#include <sstream>
#include <algorithm>
#include <cstring>

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
    Polynomial MUL_Pxk_P(int k) const;

    // Нахождение старшего коэффициента многочлена
    Rational LED_P_Q();

    // Нахождение степени многочлена
    int DEG_P_N() const;

    void nod_nok();

    //Нод полиномов
    Polynomial nod_polynom(Polynomial poly_m, Polynomial poly_n);


    //Преобразование многочлена — кратные корни в простые
    Polynomial NMR_P_P();
    // Упростить многочлен: объединить одинаковые степени и удалить нулевые коэффициент
    void visual();

    //сложение многочленов
    Polynomial add_polynom(Polynomial poly1, Polynomial poly2, bool minus);
    //умножение многочленов
    Polynomial MUL_PP_P(Polynomial poly1);
    //частное многочленов
    Polynomial DIV_PP_P(Polynomial poly);
    //производная многочлена
    Polynomial DER_P_P();

    Polynomial(const std::string& poly);
    Polynomial();
    Polynomial(const Rational& num, size_t deg);
    //проверка многочлена на тождественный 0
    bool poly_empty();
    //убирает незначащие нулевые коэффициенты при старших степенях
    void norm_polynom();

    //возвращает остаток при делении многочлена
    Polynomial MOD_PP_P(Polynomial poly);
};

