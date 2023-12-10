﻿#pragma once

#include <vector>
#include <string>
#include <algorithm>

class Natural
{

    int n = 0; // íîìåð ñòàðøåé ïîçèöèè
    std::vector<int> digit = {};

public:
    Natural();
    Natural(std::string s);

    Natural operator+(const Natural& other); // Ñëîæåíèå íàòóðàëüíûõ ÷èñåë
    // ADD_NN_N

    Natural operator-(const Natural& other);

    Natural operator*(const Natural& digit); // Óìíîæåíèå íàòóðàëüíûõ ÷èñåë
    // MUL_NN_N
    Natural operator/(const Natural& digit);

    Natural operator%(const Natural& digit);

    Natural gcd(const Natural& other); // íîä

    Natural lcm(const Natural& other); // íîê

    int operator>(const Natural& other);

    int isZero() const;

    int isOne();

    void print() const;

    void check();

    std::string str_() const;

    Natural add1();

    std::string getDigit();
};