#ifndef Natural_h
#define Natural_h

#include <vector>
#include <string>
#include <algorithm>

class Natural
{

    int n; // номер старшей позиции
    std::vector<int> digit = {};

public:
    Natural();
    Natural(std::string s);

    Natural operator+(const Natural& other); // Сложение натуральных чисел
    // ADD_NN_N

    Natural operator-(const Natural& other);

    Natural operator*(const Natural& digit); // Умножение натуральных чисел
    // MUL_NN_N
    Natural operator/(const Natural& digit);

    Natural operator%(const Natural& digit);

    Natural gcd(Natural& other); // нод

    Natural lcm(Natural& other); // нок

    int operator>(const Natural& other);

    int isZero() const;

    int isOne();

    void print() const;

    void check();

    std::string str_() const;

    Natural add1();

    std::string getDigit();
};
#endif