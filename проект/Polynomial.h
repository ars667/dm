#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include "Rational.h"


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
    Polynomial multiplyByXk(int k) const;

    // ���������� �������� ������������ ����������
    Rational leadingCoefficientNum();

    // ���������� ������� ����������
    int degree() const;

    void nod_nok();

    // ��������� ���������: ���������� ���������� ������� � ������� ������� �����������
    void visual();

    //�������� �����������
    Polynomial add_polynom(Polynomial poly1, Polynomial poly2, bool minus);
    //��������� �����������
    Polynomial mul_pol(Polynomial poly1);
    //������� �����������
    Polynomial DIV_PP_P(Polynomial poly);
    //����������� ����������
    Polynomial DER_P_P();

    //�������� ���������� �� ������������� 0
    bool poly_empty();

    //������� ���������� ������� ������������ ��� ������� ��������
    void norm_polynom();

    //���������� ������� ��� ������� ����������
    Polynomial ost_div_pp(Polynomial poly);
};