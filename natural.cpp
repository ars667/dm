#include "natural.h"
#include <iostream>
#include <cmath>

Natural::Natural(unsigned long long number) {
    while (number > 0) {
        digit.push_back(number % 10);
        number /= 10;
    }
    n = digit.size();
}

Natural Natural::operator+(const Natural &other) {
    Natural result(0); 
    int carry = 0; 

    for (int i = 0; i < std::max(n, other.n) || carry; ++i) {
        if (i == result.n)
            result.digit.push_back(0); 
            result.n++;
        int sum = carry + (i < n ? digit[i] : 0) + (i < other.n ? other.digit[i] : 0);
        result.digit[i] = sum % 10;
        carry = sum / 10;
    }

    result.n = result.digit.size();
    return result;
}

Natural Natural::operator*(const Natural &other) {
    Natural result(0);

    for (int i = 0; i < n; ++i) {
        int carry = 0;
        Natural temp(0);

        for (int j = 0; j < other.n || carry; ++j) {
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

void Natural::print() const {
    if (digit.empty()) {
        std::cout << "0";
    } else {
        for (int i = n - 1; i >= 0; --i) {
            std::cout << digit[i];
        }
    }
    std::cout << std::endl;
}