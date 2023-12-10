#include "Natural.h"
#include <iostream>
#include <cmath>

// Default constructor
Natural::Natural()
{
}

// Constructor from string representation of a natural number
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

// Addition of two natural numbers
Natural Natural::operator+(const Natural& other)
{
    Natural result("");
    int carry = 0;

    // Iterate over digits until there are no more digits in either number and no more carry
    for (int i = 0; i < std::max(n, other.n) || carry; ++i)
    {
        // If we reach the end of the result, add a new digit
        if (i == result.n)
            result.n++;
        // Calculate the sum for the current digit
        int sum = carry + (i < n ? digit[i] : 0) + (i < other.n ? other.digit[i] : 0);
        // Add the current digit to the result
        result.digit.push_back(sum % 10);
        // Set carry for the next iteration
        carry = sum / 10;
    }

    result.n = result.digit.size();
    return result;
}

// Subtraction of two natural numbers
Natural Natural::operator-(const Natural& other)
{
    // Check if the result would be negative
    if ((*this > other == 1) || (*this > other == 0))
    {
        return Natural("0");
    }

    Natural result("");
    int borrow = 0;

    // Iterate over digits until there are no more digits in either number and no more borrow
    for (int i = 0; i < std::max(n, other.n) || borrow; ++i)
    {
        // Calculate the difference for the current digit
        int sub = (i < n ? digit[i] : 0) - borrow - (i < other.n ? other.digit[i] : 0);

        // Handle borrowing if needed
        if (sub < 0)
        {
            sub += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        // If we reach the end of the result, add a new digit
        if (i == result.n)
        {
            result.n++;
        }

        // Add the current digit to the result
        result.digit.push_back(sub);
    }

    // Remove leading zeros
    while (result.n > 1 && result.digit.back() == 0)
    {
        result.digit.pop_back();
        result.n--;
    }

    return result;
}

// Multiplication of two natural numbers
Natural Natural::operator*(const Natural& other)
{
    Natural result("");

    // Iterate over digits of the first number
    for (int i = 0; i < n; ++i)
    {
        int carry = 0;
        Natural temp("");

        // Iterate over digits of the second number or carry
        for (int j = 0; j < other.n || carry; ++j)
        {
            // If we reach the end of the temporary result, add a new digit
            if (j == temp.n)
                temp.digit.push_back(0);
            temp.n++;

            // Calculate the product for the current digit
            int product = carry + digit[i] * (j < other.n ? other.digit[j] : 0);
            temp.digit[j] = product % 10;
            carry = product / 10;
        }

        // Multiply the temporary result by 10^i and add to the final result
        for (int j = 0; j < temp.n; ++j)
            temp.digit[j] *= pow(10, i);
        result = result + temp;
    }

    return result;
}

// Division of two natural numbers
Natural Natural::operator/(const Natural& other)
{
    // Check for division by zero
    if (other.isZero())
    {
        throw std::invalid_argument("Division by zero");
    }
    Natural result("0");

    // Iterate until the current dividend is greater than or equal to the divisor
    Natural currentDividend = *this;
    while (currentDividend > other == 2 || currentDividend > other == 0)
    {
        // Subtract the divisor from the current dividend and increment the result
        currentDividend = currentDividend - other;
        result = result + Natural("1");
    }

    return result;
}

// Modulus of two natural numbers
Natural Natural::operator%(const Natural& other)
{
    // Check for division by zero
    if (other.isZero())
    {
        throw std::invalid_argument("Division by zero");
    }
    // If the current number is greater than the divisor, return it as the result
    if (*this > other == 1)
    {
        return *this;
    }
    Natural currentDividend = *this;

    // Subtract the divisor until the current dividend is less than the divisor
    while (currentDividend > other == 2 || currentDividend > other == 0)
    {
        currentDividend = currentDividend - other;
    }

    return currentDividend;
}

// Comparison of two natural numbers (2 - greater, 1 - less, 0 - equal)
int Natural::operator>(const Natural& other)
{
    // Compare the number of digits first
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
        // Compare each digit from most significant to least significant
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
        return 0; // Numbers are equal
    }
}

// Greatest common divisor of two natural numbers
Natural Natural::gcd(const Natural& other)
{
    // Euclidean algorithm for finding the greatest common divisor
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

// Least common multiple of two natural numbers
Natural Natural::lcm(const Natural& other)
{
    // Calculate LCM using the formula: LCM(a, b) = (a * b) / GCD(a, b)
    Natural gcd_result = this->gcd(other);
    Natural lcm_result = (*this * other) / gcd_result;

    return lcm_result;
}

// Check if the natural number is zero
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

// Check if the natural number is one
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

// Print the natural number
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

// Debugging function to check the state of the natural number
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

// Convert the natural number to string representation
std::string Natural::str_() const
{
    std::string ans;
    for (int i = n - 1; i >= 0; --i)
    {
        ans.append(std::to_string(digit[i]));
    }
    return ans;
}

// Add 1 to the natural number
Natural Natural::add1()
{
    Natural num("1");
    return *this + num;
}

// Get a string representation of the digits in the natural number
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
