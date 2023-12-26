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
    std::vector<Rational> coef; // ������ ��� (���������, �����������)
    // ��������� ��� ������������ � ��� ����������
    Rational calculateLCMandGCD();
public:
    //�����������, ����: ������ ������������� �� n �� 0
    Polynomial(std::vector<Rational> coefficients);

    std::vector<Rational> get_coef();

    // �������� ���� �����������
    Polynomial operator+(const Polynomial& other);

    // ��������� ���� �����������
    Polynomial operator-(const Polynomial& other);

    //��������� �� ����� ������
    Polynomial operator*(Rational a) const;

    // ��������� ���������� �� x^k �����������: ���������� ����� �������, �� ����� �������
    Polynomial MUL_Pxk_P(int k) const;

    // ���������� �������� ������������ ����������
    Rational LED_P_Q();

    // ���������� ������� ����������
    int DEG_P_N() const;

    void nod_nok();

    //��� ���������
    Polynomial nod_polynom(Polynomial poly_m, Polynomial poly_n);


    //�������������� ���������� � ������� ����� � �������
    Polynomial NMR_P_P();
    // ��������� ���������: ���������� ���������� ������� � ������� ������� �����������
    void visual();

    //�������� �����������
    Polynomial add_polynom(Polynomial poly1, Polynomial poly2, bool minus);
    //��������� �����������
    Polynomial MUL_PP_P(Polynomial poly1);
    //������� �����������
    Polynomial DIV_PP_P(Polynomial poly);
    //����������� ����������
    Polynomial DER_P_P();

    Polynomial(const std::string& poly);
    Polynomial();
    Polynomial(const Rational& num, size_t deg);
    //�������� ���������� �� ������������� 0
    bool poly_empty();
    //������� ���������� ������� ������������ ��� ������� ��������
    void norm_polynom();

    //���������� ������� ��� ������� ����������
    Polynomial MOD_PP_P(Polynomial poly);
};

