#pragma once
#include "BigInt.h"

class Integer{
    private:
        BigInt value;

    public:
        Integer(); // по умолчанию 0
        Integer(BigInt val);

        // функции для работы с целыми числами
        static Integer DIV_ZZ_Z(const Integer& a, const Integer& b); // частное от деления целого на целое
        static Integer MOD_ZZ_Z(const Integer& a, const Integer& b); // остаток от деления целого на целое
        static Integer MUL_ZM_Z(const Integer& a); // умножение целого на -1
};
