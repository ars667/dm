#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>


class Polynomial {
private:
    std::vector<std::pair<int, int>> coef; // ������ ��� (���������, �����������)
    // ��������� ��� ������������ � ��� ����������
    std::pair<int, int> calculateLCMandGCD();
public:
    //�����������, ����: ������ ������������� �� n �� 0
    Polynomial(std::vector<std::pair<int, int>> coefficients);

    std::vector<std::pair<int, int>> get_coef();

    // �������� ���� �����������
    Polynomial operator+(const Polynomial& other);

    // ��������� ���� �����������
    Polynomial operator-(const Polynomial& other);

    // ��������� ���������� �� ������������ �����(������ ������)
    Polynomial operator*(int scalar) const;

    Polynomial operator*(std::pair<int, int> fraction) const;

    // ��������� ���������� �� x^k �����������: ���������� ����� �������, �� ����� �������
    Polynomial multiplyByXk(int k) const;

    // ���������� �������� ������������ ����������
    std::pair<int, int> leadingCoefficientPair();

    double leadingCoefficientNum();

    // ���������� ������� ����������
    size_t degree() const;

    void nod_nok();
    void simplify();

    // ��������� ���������: ���������� ���������� ������� � ������� ������� �����������
    std::string visual();

    //�������� �����������
    Polynomial add_polynom(Polynomial poly1, Polynomial poly2, bool minus);
    //��������� �����������
    Polynomial mul_pol(Polynomial poly1);
    //������� �����������
    Polynomial DIV_PP_P(Polynomial poly);
    //����������� ����������
    Polynomial DER_P_P();

    bool poly_empty();
    void norm_polynom();

    Polynomial ost_div_pp(Polynomial poly);

    //Polynomial nod_polynom(Polynomial poly);
};
