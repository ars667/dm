#pragma once

#include <vector>
#include <string>
#include <algorithm>

class Natural
{

    int n=0; // ����� ������� �������
    std::vector<int> digit = {};

public:
    Natural();
    Natural(std::string s);

    Natural operator+(const Natural& other); // �������� ����������� �����
    // ADD_NN_N

    Natural operator-(const Natural& other);

    Natural operator*(const Natural& digit); // ��������� ����������� �����
    // MUL_NN_N
    Natural operator/(const Natural& digit);

    Natural operator%(const Natural& digit);

    Natural gcd(const Natural& other); // ���

    Natural lcm(const Natural& other); // ���

    int operator>(const Natural& other);

    int isZero() const;

    int isOne();

    void print() const;

    void check();

    std::string str_() const;

    Natural add1();

    std::string getDigit();
};