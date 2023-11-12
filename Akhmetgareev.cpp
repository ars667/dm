#include <iostream>
#include <vector>

// Функция для нахождения НОД двух чисел
int findGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Функция для нахождения НОД массива чисел
int findGCDArray(const std::vector<int>& numbers) {
    if (numbers.empty()) {
        // Возвращаем 0 в случае пустого массива
        return 0;
    }

    int result = numbers[0];

    for (size_t i = 1; i < numbers.size(); ++i) {
        result = findGCD(result, numbers[i]);
    }

    return result;
}


// Функция для нахождения остатка от деления
int findRemainder(int dividend, int divisor) {
    if (divisor == 0) {
        // Обработка деления на ноль
        std::cerr << "Ошибка: деление на ноль!" << std::endl;
        return -1; // Возвращаем -1 в случае ошибки
    }

    return dividend % divisor;
}

// Функция для сравнения натуральных чисел
int compareNaturalNumbers(const std::vector<int>& num1, const std::vector<int>& num2) {
    // Проверяем количество разрядов
    if (num1.size() > num2.size()) {
        return 2; // Первое число больше второго
    } else if (num1.size() < num2.size()) {
        return 1; // Второе число больше первого
    }

    // Если количество разрядов одинаково, сравниваем по разрядам
    for (size_t i = 0; i < num1.size(); ++i) {
        if (num1[i] > num2[i]) {
            return 2; // Первое число больше второго
        } else if (num1[i] < num2[i]) {
            return 1; // Второе число больше первого
        }
    }

    return 0; // Числа равны
}

std::string checkForZero(int number) {
    if (number != 0) {
        return "да"; // Число не равно нулю
    } else {
        return "нет"; // Число равно нулю
    }
}

// Функция для вычитания натуральных чисел
std::vector<int> subtractNaturalNumbers(const std::vector<int>& num1, const std::vector<int>& num2) {
    std::vector<int> result;

    int borrow = 0;

    // Выполняем вычитание по разрядам
    for (size_t i = 0; i < num1.size() || i < num2.size(); ++i) {
        int digit1 = (i < num1.size()) ? num1[i] : 0;
        int digit2 = (i < num2.size()) ? num2[i] : 0;

        int difference = digit1 - digit2 - borrow;

        if (difference < 0) {
            difference += 10; // Заем на предыдущем разряде
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.push_back(difference);
    }

    // Удаляем ведущие нули
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }

    return result;
}
