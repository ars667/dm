#pragma once

#include <vector>
#include <string>
#include <algorithm>

class Natural
{

    int n;
    std::vector<int> digit;

public:
    Natural();
    Natural(std::string s);
    int operator>(const Natural &other);
    int isZero() const;
    void add1();
    Natural operator+(const Natural &other);
    Natural operator-(const Natural &other);
    Natural MUL_ND_N(int dig) const;
    Natural MUL_Nk_N(const Natural &k);
    Natural operator*(const Natural &digit);
    Natural SUB_NDN_N(const Natural &other, int dig);
    Natural DIV_NN_Dk(const Natural &other);
    Natural operator/(const Natural &digit);
    Natural operator%(const Natural &digit);
    Natural gcd(const Natural &other);
    Natural lcm(const Natural &other);
    int isOne();
    void print() const;
    void check();
    std::string str_() const;
    std::string getDigit();
};