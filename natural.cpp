#include "natural.h"
#include <iostream>
#include <cmath>

Natural::Natural(std::string s)
{
    int len = s.length();
    for (int i = len - 1; i >= 0; i--)
    {
        char c = s[i];
        if (c >= '0' && c <= '9')
        {
            this->digit.push_back(c - '0');
        }
    }
    this->n = digit.size();
}

Natural Natural::operator+(const Natural &other)
{
    Natural result("");
    int carry = 0;

    for (int i = 0; i < std::max(n, other.n) || carry; ++i)
    {
        if (i == result.n)
            // result.digit.push_back(0);
            result.n++;
        int sum = carry + (i < n ? digit[i] : 0) + (i < other.n ? other.digit[i] : 0);
        result.digit.push_back(sum % 10);
        carry = sum / 10;
    }

    result.n = result.digit.size();
    return result;
}

Natural Natural::operator-(const Natural &other)
{
    if ((*this > other == 1) || (*this > other == 0))
    {
        return Natural("0");
    }

    Natural result("");
    int borrow = 0;

    for (int i = 0; i < std::max(n, other.n) || borrow; ++i)
    {
        int sub = (i < n ? digit[i] : 0) - borrow - (i < other.n ? other.digit[i] : 0);

        if (sub < 0)
        {
            sub += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        if (i == result.n)
        {
            // result.digit.push_back(0);
            result.n++;
        }

        result.digit.push_back(sub);
    }

    while (result.n > 1 && result.digit.back() == 0)
    {
        result.digit.pop_back();
        result.n--;
    }

    return result;
}

Natural Natural::operator*(const Natural &other)
{
    Natural result("");

    for (int i = 0; i < n; ++i)
    {
        int carry = 0;
        Natural temp("");

        for (int j = 0; j < other.n || carry; ++j)
        {
            if (j == temp.n)
                temp.digit.push_back(0);
            temp.n++;

            int product = carry + digit[i] * (j < other.n ? other.digit[j] : 0);
            temp.digit[j] = product % 10;
            carry = product / 10;
        }

        for (int j = 0; j < temp.n; ++j)
            temp.digit[j] *= pow(10, i);
        result = result + temp;
    }

    return result;
}

Natural Natural::operator/(const Natural &other)
{
    if (other.isZero())
    {
        throw std::invalid_argument("Division by zero");
    }
    Natural result("0"); // Инициализируем результат нулём

    Natural currentDividend = *this; // Создаем копию делимого

    while (currentDividend > other == 2 || currentDividend > other == 0)
    {
        currentDividend = currentDividend - other;
        result = result + Natural("1");
    }

    return result;
}

// Остаток от деления натуральных чисел
Natural Natural::operator%(const Natural &other)
{
    if (other.isZero())
    {
        throw std::invalid_argument("Division by zero");
    }
    Natural currentDividend = *this; // Создаем копию делимого

    while (currentDividend > other == 2 || currentDividend > other == 0)
    {
        currentDividend = currentDividend - other;
    }

    return currentDividend;
}

int Natural::operator>(const Natural &other)
{
    if (this->n > other.n)
    {
        return 2;
    }
    else if (this->n < other.n)
    {
        return 1;
    }
    else
    {
        for (int i = this->n; i >= 0; i--)
        {
            if (this->digit[i] > other.digit[i])
            {
                return 2;
            }
            else if (this->digit[i] < other.digit[i])
            {
                return 1;
            }
        }
        return 0;
    }
}

int Natural::isZero() const
{
    if (this->digit.empty())
    {
        return 1;
    }
    if ((this->n) == 1 && (this->digit[0]) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Natural::isOne()
{
    if ((this->n) == 1 && (this->digit[0]) == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Natural::print() const
{
    if (digit.empty())
    {
        std::cout << "0";
    }
    else
    {
        for (int i = n - 1; i >= 0; --i)
        {
            std::cout << digit[i];
        }
    }
    std::cout << std::endl;
}

Natural Natural::add1()
{
    Natural num("1");
    return *this + num;
}

std::string Natural::getDigit()
{
    std::string s;
    for (int i = 0; i < this->n; i++)
    {
        char c = static_cast<char>(i);
        s += c;
    }
    return s;
}
