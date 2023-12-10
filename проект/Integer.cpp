#include "Integer.h"
#include <iostream>
using namespace std;

Integer::Integer()
{
	sign = false;
	value = Natural("0");
}

Integer::Integer(string strInt) // Конструктор, если первый символ минус - знак записываем и перезаписываем строчку без минуса, иначе + и исп конструктор Natural
{
	if (strInt[0] == '-')
	{
		string minusStrInt = strInt.erase(0, 1);
		sign = true;
		value = minusStrInt;
	}
	else
	{
		sign = false;
		value = Natural(strInt);
	}
}

Integer::Integer(bool sign, Natural value)
{
	this->sign = sign;
	this->value = value;
}


bool Integer::getSign() const
{
	return sign;
}

void Integer::print() const
{
	if (sign == true)
		std::cout << '-';
	value.print();
}

std::string Integer::str_() const
{
	std::string ans;
	if (sign == true)
		ans.append("-");
	ans.append(value.str_());
	return ans;
}

std::string Integer::getValue() const // получить value, игнорируя знак
{
	if (sign == true)
		return str_().substr(1, str_().length() - 1);
	return str_().substr(0, str_().length());
}


// Абсолютная величина числа, результат - натуральное
Natural Integer::ABS_Z_N() {
	return value;
}

unsigned int Integer::POZ_Z_D() // Определение положительности числа (2 - положительное, 0 — равное нулю, 1 - отрицательное)
{								// прямая проверка значений sign
	Natural val = value;
	if ((val).isZero())
		return 0;
	if (sign == false)
		return 2;
	if (sign == true)
		return 1;
}

Integer Integer::MUL_ZM_Z() { // умножение целого на -1
	Integer ans;			// проверка знака, смена на противоположный
	ans.value = value;
	if (ans.value.isZero() == 1)
		return Integer("0");
	if (sign == true)
		ans.sign = false;
	else
		ans.sign = true;
	return ans;
}

//// Преобразование натурального в целое
Integer Integer::TRANS_N_Z(const Natural& natural) {
	return Integer(false, natural);
}

// Преобразование целого неотрицательного в натуральное
Natural Integer::TRANS_Z_N(const Integer& integer) { 
	if (sign == true)
		throw "Negative number"; // проверка на неотрицательность, выбрасывание исключения
	// return ABS_Z_N(integer); можно использовать ABS_Z_N, т.к. код далее повторяет эту функцию
	return Natural(integer.value);
}

Integer Integer::ADD_ZZ_Z(const Integer& intB) //Сложение целых чисел, ABS_Z_N - вернуть нат, COM_NN_D - сравнить 2 нат, ADD_NN_N SUB_NN_N MUL_ZM_Z - смена знака
{	//POZ_Z_D - опр положит(мешает для случаев с 0, так что не использую.)
	// ветвление нужно, так как невозможно получить результат сложения через натуральные, есть лишь возможность вычитания и сложения натуральных
	// В случае вычитания из меньшего натурально большее результатом должно быть целое - нельзя так реализовать, поэтому здесь используется 
	// сравнение по модулю числа, чтобы в случае вычитания из меньшего большего знак в конце менялся на обратный
	// Итого в случае одинаковых знаков используется простое сложение с сохранением исходного знака
	// В случае разных знаков сначала идёт сравнение по модулю и ветвление
	Natural sum;
	if (sign == false && intB.sign == false)
	{
		sum = (value + intB.value);
		return Integer(false, sum);
	}
	else if (sign == true && intB.sign == true)
	{
		sum = (value + intB.value);
		return Integer(true, sum);
	}
	else if (sign != intB.sign)
	{
		int bigger = value > intB.value;
		if (bigger == 0)
			return Integer(false, (value - intB.value));
		else if (bigger == 2)//A > B по мод
		{
			sum = (value - intB.value);
			return Integer(sign, sum);
		}
		else if (bigger == 1)//A < B по мод
		{
			Natural bVal = intB.value;
			sum = (bVal - value);
			return (Integer(!sign, sum));
		}
		else
			return Integer();
	}
	else
		return Integer();
}

Integer Integer::SUB_ZZ_Z(const Integer& intB) //Вычитание целых чисел, POZ_Z_D ABS_Z_N COM_NN_D ADD_NN_N SUB_NN_N MUL_ZM_Z
{												// сложение со сменой знака второго слагаемого
	Integer tempB = intB;
	Integer intRevB = tempB.MUL_ZM_Z();
	Integer result = ADD_ZZ_Z(intRevB);
	return result;
}

Integer Integer::MUL_ZZ_Z(const Integer& intB) // Умножение целых чисел, POZ_Z_D ABS_Z_N MUL_NN_N MUL_ZM_Z
{						// отдельно для знаков, отдельно для значений. Для знаков разные - минус, иначе +, для 0 прописано отдельно
	bool mulSign = false;
	Integer tempB = intB;
	if ((POZ_Z_D() != tempB.POZ_Z_D()) && (POZ_Z_D() != 0 && tempB.POZ_Z_D() != 0))
		mulSign = true;
	else if ((POZ_Z_D() == 0 || tempB.POZ_Z_D() == 0))
	{
		return Integer("0");
	}
	Natural mult = value * tempB.value;
	return Integer(mulSign, mult);
}

// функции для работы с целыми числами
Integer Integer::DIV_ZZ_Z(const Integer& b) { // деление целого на целое
												// узнать знак через арифметику знаков функции MUL и использовать деление натуральных
	Integer result;
	result.sign = MUL_ZZ_Z(b).sign;
	result.value = value / b.value;
	return result;
}

Integer Integer::MOD_ZZ_Z(const Integer& b) { // остаток от деления целого на целое (то же самое, что и натуральное, только сохранить знак)
	Integer div = DIV_ZZ_Z(b);
	return Integer(div.sign, value % b.value);
}
