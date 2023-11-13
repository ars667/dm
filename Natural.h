#ifndef Natural_h
#define Natural_h

#include <vector>

class Natural{

    int n; //номер старшей позиции
    std::vector<int> digit = {};
    public:

        Natural(unsigned long long number);

        Natural operator+(const Natural &other); //Сложение натуральных чисел
                                                 //ADD_NN_N

        Natural operator*(const Natural &digit); //Умножение натуральных чисел
                                                 //MUL_NN_N

        void print() const;
};
#endif