#include "Natural.h"
#include <iostream>
#include <cmath>

Natural::Natural()
{
    this->n = 0;
    this->digit = {};
}

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
        for (int i = this->n - 1; i >= 0; i--)
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

void Natural::add1()
{
    int last = this->n - 1;
    while (this->digit[last] == 9)
    {
        last--;
    }
    if (last >= 0)
    {
        this->digit[last] += 1;
    }
    else
    {
        std::vector<int> newDigit = {1};
        newDigit.insert(newDigit.end(), this->digit.begin(), this->digit.end());
        this->digit = newDigit;
    }
}

Natural Natural::operator+(const Natural &other)
{
    Natural result;
    int carry = 0;

    for (int i = 0; i < std::max(n, other.n) || carry; ++i)
    {
        if (i == result.n)

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
    if ((*this > other == 1))
    {
        throw std::invalid_argument("second operand > first");
    }

    if (*this > other == 0)
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

Natural Natural::MUL_ND_N(int dig) const
{
    std::vector<int> newDigit = {};
    int carry = 0;
    for (int i = 0; i < this->n; i++)
    {
        int current = this->digit[i] * dig;
        newDigit.push_back(current % 10 + carry);
        carry = current / 10;
    }
    if (carry != 0)
    {
        newDigit.push_back(carry);
    }
    Natural result;
    result.digit = newDigit;
    result.n = newDigit.size();
    return result;
}

Natural Natural::MUL_Nk_N(const Natural &k)
{
    std::vector<int> newDigit = {};
    for (int i = 0; i < k.n; i++)
    {
        for (int j = 0; j < k.digit[i] * pow(10, i); j++)
        {
            newDigit.push_back(0);
        }
    }
    Natural result;
    result.digit = this->digit;
    result.digit.insert(result.digit.begin(), newDigit.begin(), newDigit.end());
    result.n = result.digit.size();
    return result;
}

Natural Natural::operator*(const Natural &other)
{
    Natural result("0");
    for (int i = 0; i < this->n; i++)
    {
        Natural current = other.MUL_ND_N(this->digit[i]);
        current = current.MUL_Nk_N(Natural(std::to_string(i)));
        result = result + current;
    }
    return result;
}

Natural Natural::SUB_NDN_N(const Natural &other, int dig)
{
    Natural subtrahend = other.MUL_ND_N(dig);
    return *this - subtrahend;
}

Natural Natural::DIV_NN_Dk(const Natural &other)
{
    if (*this > other == 1)
    {
        throw std::invalid_argument("second operand > first");
    }
    Natural large = *this;
    Natural small = other;
    int k = 1;
    while (large > small.MUL_Nk_N(Natural(std::to_string(k))) == 2)
    {
        k++;
    }
    k--;
    Natural divisor = small.MUL_Nk_N(Natural(std::to_string(k)));
    Natural first("0");
    while (large > divisor == 2 || large > divisor == 0)
    {
        large = large - divisor;
        first.add1();
    }
    return first.MUL_Nk_N(Natural(std::to_string(k)));
}

Natural Natural::operator/(const Natural &other)
{
    if (*this > other == 1)
    {
        throw std::invalid_argument("second operand > first");
    }
    if (other.isZero())
    {
        throw std::invalid_argument("Division by zero");
    }
    Natural result("0");
    Natural temp("0");
    Natural large = *this;
    Natural small = other;
    while (!(large > small == 1))
    {
        temp = large.DIV_NN_Dk(small);
        large = large - small * temp;
        result = result + temp;
    }
    return result;
}

Natural Natural::operator%(const Natural &other)
{
    if (other.isZero())
    {
        throw std::invalid_argument("Division by zero");
    }
    if (*this > other == 1)
    {
        return *this;
    }
    Natural currentDividend = *this;

    while (currentDividend > other == 2 || currentDividend > other == 0)
    {
        currentDividend = currentDividend - other;
    }

    return currentDividend;
}

Natural Natural::gcd(const Natural &other)
{
    Natural a = *this;
    Natural b = other;
    while (!b.isZero())
    {
        Natural temp_b = b;
        b = a % b;
        a = temp_b;
    }

    return a;
}

Natural Natural::lcm(const Natural &other)
{
    Natural gcd_result = this->gcd(other);

    Natural lcm_result = (*this * other) / gcd_result;

    return lcm_result;
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

void Natural::check()
{
    std::cout << this->n << std::endl;
    if (digit.empty())
    {
        std::cout << "EMP";
    }
    else
    {
        for (int i = n - 1; i >= 0; --i)
        {
            std::cout << digit[i] << std::endl;
        }
    }
}

std::string Natural::str_() const
{
    std::string ans;
    for (int i = n - 1; i >= 0; --i)
    {
        ans.append(std::to_string(digit[i]));
    }
    return ans;
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