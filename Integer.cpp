#include "BigInt.h"
#include "Integer.h"

// конструкторы
Integer::Integer() : value("0") {}
Integer::Integer(BigInt val) : value(val) {}

// функции для работы с целыми числами
Integer Integer::DIV_ZZ_Z(const Integer& a, const Integer& b){ // деление целого на целое
    if (b != BigInt("0")){
        if (a.value >= b.value){
            BigInt result;
            if ((a.value < 0 && b.value > 0) || (a.value > 0 && b.value < 0)){
                BigInt absA = a.value.abs();
                BigInt absB = b.value.abs();

                result.value = -(absA.value / absB.value);
            }
            else{
                result.value = a.value / b.value;
            }

            return result;
        }
        else {
            return Integer(); 
        }
    }
    throw std::string{"Division by zero!"};
}

Integer Integer::MOD_ZZ_Z(const Integer& a, const Integer& b){ // остаток от деления целого на целое
    if (b.value != BigInt("0")){
        BigInt result;
        if ((a.value < 0 && b.value > 0) || (a.value > 0 && b.value < 0)){
            BigInt absA = a.value.abs();
            BigInt absB = b.value.abs();

            result.value = -(absA.value % absB.value);
        }
        else{
            result.value = a.value % b.value;
        }
        return result;
    }
    throw std::string{"Division by zero!"};
}

Integer Integer::MUL_ZM_Z(const Integer& a){ // умножение целого на -1
    BigInt result;
    result = a.value * (-1);
    return result;
}
