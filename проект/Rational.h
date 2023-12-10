#pragma once

#include "Integer.h"
#include "Natural.h"


class Rational {
private:
    Integer nominator;
    Natural denominator;
public:
    //�����������, ����������� �� 0.
    Rational();
    Rational(Integer, Natural);
    Rational(std::string str);

    void print() const;
    std::string str_() const;
    Integer get_nominator();

    Rational RED_Q_Q(const Rational&);//���������� ����� || ������ �� ABS_Z_N,  GCF_NN_N  �  DIV_ZZ_Z
    bool INT_Q_B(const Rational&);//�������� ������������ �������� �� �����, ���� ������������ ����� �������� �����, �� ���, ����� ����
    Rational TRANS_Z_Q(const  Integer&);//�������������� ������ � �������
    Integer TRANS_Q_Z(const Rational&);//�������������� ������������ �������� � ����� (���� ����������� ����� 1)
    Rational ADD_QQ_Q(const Rational&);//�������� ������ || ������ �� LCM_NN_N � MUL_ZZ_Z, ADD_ZZ_Z
    Rational SUB_QQ_Q( const Rational&);//��������� ������ || ������ �� LCM_NN_N, MUL_ZZ_Z � SUB_ZZ_Z
    Rational MUL_QQ_Q(const Rational&);//��������� ������ || ������ �� MUL_ZZ_Z
    Rational DIV_QQ_Q(const Rational&);//������� ������ (�������� ������� �� ����) || ������ �� MUL_ZZ_Z
};