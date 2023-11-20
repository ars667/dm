#include "Integer.h"


// Умножение числа на 10^k
Natural Natural::MUL_Nk_N(const Natural & natural, int k) {
    string n_str = "";
    for(unsigned long long i = 0; i < natural.getSize(); i++)
        n_str += to_string(natural.getDigit(i)); // проходясь по каждой цифре добовляю ее в строку

    while (k) {
        n_str += "0";
        k--;
    }
    return Natural(n_str);
}


// Неполное частное от деления первого натурального числа на второе с остатком (делитель отличен от нуля)
Natural Natural::DIV_NN_N(const Natural & n, const Natural & m) {
    Natural result;
    if (COM_NN_D(n, m) == 2){ // n > m
        Natural div = n;
        while (COM_NN_D(div, m) != 1) {
            /* Ниже операция вычитания из делимого части делителя. Нашли первую цифру деления - DIV_NN_Dk(div, m),
            затем вычли из делимого делитель умноженный на эту цифру. Получили новый делитель. Повторяем,
            пока делимое больше делителя */
            Natural div_nn_dk = DIV_NN_Dk(div, m);
            result = ADD_NN_N(result, div_nn_dk);

            unsigned long long c = 0, size = div_nn_dk.getSize();
            for (unsigned long long i = 0; i < size; i++) // перевод числа из Natural в обычное
                c += div_nn_dk.getDigit(size - i - 1);

            div = SUB_NDN_N(div, c, m);
        }
    }
    else {
        if (COM_NN_D(n, m) == 1){ // n < m
            return Natural("0");
        }
        else { // n == m
            return Natural("1");
        }
    }
    return result;
}


// Абсолютная величина числа, результат - натуральное
Natural Integer::ABS_Z_N(const Integer & integer) {
    string n_str = "";
    for(unsigned long long i = 0; i < integer.getSize(); i++)
        n_str += to_string(integer.getDigit(i)); // проходясь по каждой цифре добовляю ее в строку
    return Natural(n_str);
}


// Преобразование натурального в целое
Integer Integer::TRANS_N_Z(const Natural & natural) {
    return Integer(0, natural);
}


// Преобразование целого неотрицательного в натуральное
Natural Integer::TRANS_Z_N(const Integer & integer) {
    if (integer.getSign())
        throw "Negative number"; // проверка на неотрицательность, выбрасывание исключения

    // return ABS_Z_N(integer); можно использовать ABS_Z_N, т.к. код далее повторяет эту функцию

    string n_str = "";
    for(unsigned long long i = 0; i < integer.getSize(); i++)
        n_str += to_string(integer.getDigit(i)); // проходясь по каждой цифре добовляю ее в строку
    return Natural(n_str);
}
