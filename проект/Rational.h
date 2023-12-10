#pragma once

#include "Integer.h"
#include "Natural.h"


class Rational {
private:
    Integer nominator;
    Natural denominator;
public:
    //Конструктор, знаменатель не 0.
    Rational();
    Rational(Integer, Natural);
    Rational(std::string str);

    void print() const;
    std::string str_() const;
    Integer get_nominator();

    Rational RED_Q_Q(const Rational&);//Сокращение дроби || Ссылка на ABS_Z_N,  GCF_NN_N  и  DIV_ZZ_Z
    bool INT_Q_B(const Rational&);//Проверка сокращенного дробного на целое, если рациональное число является целым, то «да», иначе «нет»
    Rational TRANS_Z_Q(const  Integer&);//Преобразование целого в дробное
    Integer TRANS_Q_Z(const Rational&);//Преобразование сокращенного дробного в целое (если знаменатель равен 1)
    Rational ADD_QQ_Q(const Rational&);//Сложение дробей || Ссылка на LCM_NN_N и MUL_ZZ_Z, ADD_ZZ_Z
    Rational SUB_QQ_Q( const Rational&);//Вычитание дробей || Ссылка на LCM_NN_N, MUL_ZZ_Z и SUB_ZZ_Z
    Rational MUL_QQ_Q(const Rational&);//Умножение дробей || Ссылка на MUL_ZZ_Z
    Rational DIV_QQ_Q(const Rational&);//Деление дробей (делитель отличен от нуля) || Ссылка на MUL_ZZ_Z
};