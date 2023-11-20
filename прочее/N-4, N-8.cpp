#include "Natural.h"
#include <iostream>

Natural Natural::operator+(const Natural &other){
    Natural tmp(*this);//создаем копию объекта
    if (COM_NN_D(tmp, other) == 0 || COM_NN_D(tmp, other) == 2) {//если первое число больше - делаем
        for (unsigned long long i = other.digit.size()-1; i >= 0; i--) {
            // прибавляем к каждому числу первого каждое число второго по их порядку
            tmp.digit[i] += other.digit[i];
        }
        int fl = 0;
        int res;
        for (int i = tmp.digit.size(); i >= 0; i++) {
            //далее если число больше 10 оставляем только остаток от деления на 10
            if (tmp.digit[i] + fl >= 10) {
                //неполное частное при делении всегда единица для суммы цифр , поэтому флаг = 1
                tmp.digit[i] = (tmp.digit[i] + fl) % 10;
                fl = 1;
            } else {
                //если число нацело не делится просто прибавляем флаг
                tmp.digit[i] += fl;
                fl = 0;
            }
        }
        if (fl == 1)
            //если в конце чисел не осталось , но флаг не равен 0 , заносим его в начало числа(конец массива)
            tmp.digit.insert(tmp.digit.begin(), 1);
        return tmp; //результат
    }
    if (COM_NN_D(tmp, other) == 1) {//если число меньше - делаем
        Natural cur(other);//копия второго числа
        for (unsigned long long i = cur.digit.size()-1; i >=0 ; i--) {//все также , только делаем для второго числа
            cur.digit[i] += cur.digit[i];
        }
        int fl = 0;
        int res;
        for (unsigned long long i = cur.digit.size()-1; i >= 0; i++) {
            //далее если число больше 10 оставляем только остаток от деления на 10
            if (cur.digit[i] + fl >= 10) {
                //неполное частное при делении всегда единица для суммы цифр , поэтому флаг = 1
                cur.digit[i] = (cur.digit[i] + fl) % 10;
                fl = 1;
            } else {
                //если число нацело не делится просто прибавляем флаг
                cur.digit[i] += fl;
                fl = 0;
            }
        }
        if (fl == 1)
            //если в конце чисел не осталось , но флаг не равен 0 , заносим его в начало числа(конец массива)
            tmp.digit.insert(tmp.digit.begin(), 1);
        return cur;// результат
    }
    return tmp;
}


Natural Natural::operator*(const Natural &other){
    std::vector<Natural> array;//массив чисел полученных путем умножения на конкретную цифру
    Natural tmp(*this);
    if (COM_NN_D(tmp, other) == 2 || COM_NN_D(tmp, other) == 0) {
        array.resize(other.digit.size());
        for (unsigned long long i = other.digit.size()-1; i >= 0; i--) {
            // в массив чисел добавляем по одному первое число умноженное с помощью функкции
            array[i] = MUL_ND_N(tmp.digit[i]);
            //MUL_ND_N на цифры из второго числа
        }
    }
    if (COM_NN_D(tmp, other) == 1) {
        array.resize(tmp.digit.size());
        for (unsigned long long i = tmp.digit.size()-1; i >= 0; i--) {
            // в массив чисел добавляем по одному первое число умноженное с помощью функкции
            array[i] = MUL_ND_N(other.digit[i]);
            //MUL_ND_N на цифры из второго числа
        }
    }
    Natural res(0);
    int k = 0;
    for (unsigned long long i = array.size()-1; i>= 0; i++)
        // в цикле заносим в числа из array умноженные на 10^k степени где k - номер порядка
        res = res + array[i].MUL_Nk_N(k++);
    //для пояснения:array[3,2,1] , тогда res = 3*100+2*10+1

    return res;
}