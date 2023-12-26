#include "Natural.h"
#include <iostream>
#include <cmath>

Natural::Natural()
{
}

Natural::Natural(std::string s) // s - ����� � ���� ������, ������� ����� ������������� � �����
{
    int len = s.length();              // �������� ����� ������ � ��������� � � ���������� len
    for (int i = len - 1; i >= 0; i--) // �������� �� ������ s � �������� �������, ������� � ���������� �������. ��� �������� � ������� ����� for, ������� ����������� �� len - 1 �� 0.
    {
        char c = s[i];
        if (c >= '0' && c <= '9') // ���������, ���� ������ �������� ������, �� ����������� ������� � �����
        {
            this->digit.push_back(c - '0'); // ��������� � ������ digit
        }
    }
    this->n = digit.size(); // ������������� �������� n ������ ������� ������� digit. �������� n ������������ ����� ���������� ���� � �����.
}

Natural Natural::operator+(const Natural &other)
{
    Natural result("");
    int carry = 0; // carry - ��� �������� �������� ��� �������� ����

    for (int i = 0; i < std::max(n, other.n) || carry; ++i)
    {
        if (i == result.n) // ���� ������� ������ i ����� ���������� ���� � result, ��� ����������� ���������� ���� � result.
            // result.digit.push_back(0);
            result.n++;
        int sum = carry + (i < n ? digit[i] : 0) + (i < other.n ? other.digit[i] : 0); // ��� ��������� ����� �������� �������� � ������� ���� � ����� ������ (��� 0, ���� ���� �� ����� ��� ��������� ����������).
        result.digit.push_back(sum % 10);                                              // ��������� ������� �� ������� ����� �� 10 � ������ ���� result � ��������� �������, �������� ����� �� 10.
        carry = sum / 10;
    }

    result.n = result.digit.size(); // ��������� ���������� ���� � result � ���������� result.
    return result;
}

Natural Natural::operator-(const Natural &other)
{
    if ((*this > other == 1) || (*this > other == 0)) // ���������, ������ �� �������� ����� (*this) ��� ����� ����� other.
    {
        return Natural("0"); // �.�. ������ ������� ������� ����� �� ��������
    }

    Natural result("");
    int borrow = 0; // borrow - ��� �������� ����� ��� ��������� ����.

    for (int i = 0; i < std::max(n, other.n) || borrow; ++i) // �������� �������� �������� ����� � ������� ���� � ����� ������ (��� 0, ���� ���� �� ����� ��� ��������� ����������
    {
        int sub = (i < n ? digit[i] : 0) - borrow - (i < other.n ? other.digit[i] : 0);

        if (sub < 0) // ��������� 10 � �������� � ������������� ���� ������ 1.
        {
            sub += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0; // ������������� ���� ������ 0.
        }

        if (i == result.n) // ���� ������� ������ i ����� ���������� ���� � result
        {
            // result.digit.push_back(0);
            result.n++; // ����������� ���������� ���� � result
        }

        result.digit.push_back(sub);
    }

    while (result.n > 1 && result.digit.back() == 0) // ������� ��� ���������� ���� � ������ ����� (���� ��� ����)
    {
        result.digit.pop_back();
        result.n--;
    }

    return result;
}

Natural Natural::operator*(const Natural &other)
{
    Natural result("0");
    
    result.n = (this->n + other.n);
    result.digit.resize(this->n + other.n);

    for (int i = 0; i < this->n; i++)
    {
        int carry = 0;
        for (int j = 0; j < other.n || carry != 0; j++)
        {
            int cur = result.digit[i + j] + this->digit[i] * (j < other.digit.size() ? other.digit[j] : 0) + carry;
            result.digit[i + j] = cur % 10;
            carry = cur / 10;
        }
    } 
    while (result.digit.size() > 1 && result.digit.back() == 0) {
        result.digit.pop_back();
    }
    result.n = result.digit.size();

    return result;
}

Natural Natural::operator/(const Natural &other)
{
    if (other.isZero())
    {
        throw std::invalid_argument("Division by zero"); // ������� ����������� ����������, ��� ��� ������� �� ���� �� ����������.
    }
    Natural result("0");

    Natural currentDividend = *this; // currentDividend - ���������������� ��������� ��������� �������. ���� ������ ����� �������������� ��� �������� �������� �������� � �������� �������.

    while (currentDividend > other == 2 || currentDividend > other == 0) // ���� currentDividend ������ ��� ����� other
    {
        currentDividend = currentDividend - other; // �������� other �� currentDividend � ����������� result �� 1
        result = result + Natural("1");
    }

    return result;
}

Natural Natural::operator%(const Natural &other)
{
    if (other.isZero())
    {
        throw std::invalid_argument("Division by zero"); // ����������� ����������, ��� ��� ������� �� ���� �� ����������
    }
    if (*this > other == 1)
    {
        return *this; // ���������� �������� �����
    }
    Natural currentDividend = *this; // ��� �������� �������� �������� � �������� �������.

    while (currentDividend > other == 2 || currentDividend > other == 0) // �� ������ ���� ���������� �������� �� �������� ��������.
    {
        currentDividend = currentDividend - other;
    }

    return currentDividend; // currentDividend, ������� ������ �������� ������� �� ������� ��������� ����� �� other
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

Natural Natural::gcd(const Natural &other)
{
    Natural a = *this;
    Natural b = other;
    while (!b.isZero())
    {
        Natural temp_b = b;
        b = a % b;
        a = temp_b; // ��������� b �� ������� �� ������� a �� b � ��������� a �� �������� temp_b
    }

    return a; // a, ������� ������ �������� ��� ��������� ����� � other
}

Natural Natural::lcm(const Natural &other)
{
    Natural gcd_result = this->gcd(other); // ������� �������� ������ � ��������, � ����� ����� ���������� ������������ �� gcd_result

    Natural lcm_result = (*this * other) / gcd_result;

    return lcm_result; // lcm_result, ������� ������ �������� ��� ��������� ����� � other.
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