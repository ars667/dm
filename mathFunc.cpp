#include "mathFunc.h"

int GCF_NN_N(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int LCM_NN_N(int a, int b) {
    return (a * b) / GCF_NN_N(a, b);
}

// Функция для сокращения дроби (принимает значение по ссылке и меняет его)
void RED_Q_Q(std::pair<int, int>& fraction) {
    int& numerator = fraction.first;
    int& denominator = fraction.second;
    int commonDivisor = GCF_NN_N(numerator, denominator);

    numerator /= commonDivisor;
    denominator /= commonDivisor;
}

// Функция для сложения двух дробей
std::pair<int, int> ADD_QQ_Q(std::pair<int, int> fraction1, std::pair<int, int> fraction2, bool minus) {
    int numerator1 = fraction1.first;
    int denominator1 = fraction1.second;
    int numerator2 = fraction2.first;
    int denominator2 = fraction2.second;

    // Общий знаменатель для сложения дробей
    int commonDenominator = denominator1 * denominator2;

    // Приводим числители к общему знаменателю
    numerator1 *= denominator2;
    numerator2 *= denominator1;

    int resultNumerator;
    // Складываем числители
    if (minus) {
        resultNumerator = numerator1 - numerator2;
    }
    else {
        resultNumerator = numerator1 + numerator2;
    }

    // Формируем и возвращаем сокращенную дробь
    std::pair<int, int> resultFraction = std::make_pair(resultNumerator, commonDenominator);
    RED_Q_Q(resultFraction); // Сокращаем дробь

    return resultFraction;
}

std::pair<int, int> MUL_QQ_Q(std::pair<int, int> fraction1, std::pair <int, int> fraction2) {
    std::pair <int, int> new_fraction = std::make_pair(fraction1.first*fraction2.first, fraction1.second * fraction2.second);
    return new_fraction;
}

std::pair<int, int> DIV_QQ_Q(std::pair<int, int> fraction1, std::pair <int, int> fraction2) {
    std::pair <int, int> new_fraction = std::make_pair(fraction1.first * fraction2.second, fraction1.second * fraction2.first);
    RED_Q_Q(new_fraction);
    return new_fraction;
}