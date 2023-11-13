#include "Integer.h"

Integer::Integer()
{
}

Integer::Integer(string strInt)//доделать наследование
{
	this->value = Natural();
}

Integer::Integer(bool sign, Natural value)
{
	this->sign = sign;
	this->value = value;
}

long long int Integer::getValue() const//напишу после Natural
{
	return 0;
}

int Integer::getDigit(unsigned int rank) const//нужен аналог от Natural
{
	return 0;
}

int Integer::getRank() const//нужен аналог от Natural
{
	return 0;
}

bool Integer::getSign() const
{
	return sign;
}

// Абсолютная величина числа, результат - натуральное
//делала Бараева Е.Н.
Natural Integer::ABS_Z_N(const Integer& integer) {
	string n_str = "";
	for (unsigned long long i = 0; i < integer.getRank(); i++)
		n_str += to_string(integer.getDigit(i)); // проходясь по каждой цифре добовляю ее в строку
	return Natural(n_str);
}

unsigned int Integer::POZ_Z_D(const Integer& Int) // Определение положительности числа (2 - положительное, 0 — равное нулю, 1 - отрицательное)
{
	if (Int.sign == false)
		return 2;
	if (Int.sign == true)
		return 1;
	if (!(Int.value.getDigit(0) == 0 && Int.value.getSize() == 1))
		return 0;
}

// делала Анищенко А.И.
Integer Integer::MUL_ZM_Z(const Integer& a) { // умножение целого на -1
	Integer result;
	result = a.value * (-1);
	return result;
}

// Преобразование натурального в целое
//делала Бараева Е.Н.
Integer Integer::TRANS_N_Z(const Natural& natural) {
	return Integer(true, natural);
}

// Преобразование целого неотрицательного в натуральное
//делала Бараева Е.Н.
Natural Integer::TRANS_Z_N(const Integer& integer) {
	if (integer.getSign())
		throw "Negative number"; // проверка на неотрицательность, выбрасывание исключения

	// return ABS_Z_N(integer); можно использовать ABS_Z_N, т.к. код далее повторяет эту функцию

	string n_str = "";
	for (unsigned long long i = 0; i < integer.getRank(); i++)
		n_str += to_string(integer.getDigit(i)); // проходясь по каждой цифре добовляю ее в строку
	return Natural(n_str);
}

Integer Integer::ADD_ZZ_Z(const Integer& intA, const Integer& intB) //Сложение целых чисел, ABS_Z_N - вернуть нат, COM_NN_D - сравнить 2 нат, ADD_NN_N SUB_NN_N MUL_ZM_Z - смена знака
{	//POZ_Z_D - опр положит(мешает для случаев с 0, так что не использую.)
	Natural sum;
	if (intA.sign == false && intB.sign == false)
	{
		sum = ADD_NN_N(intA.value, intB.value);
		return Integer(false, sum);
	}
	else if (intA.sign == true && intB.sign == true)
	{
		sum = ADD_NN_N(intA.value, intB.value);
		return Integer(true, sum);
	}
	else if (intA.sign != intB.sign)
	{
		int bigger = COM_NN_D(intA.value, intB.value);
		if (bigger == 0)
			return(false, SUB_NN_N(intA.value, intB.value));
		else if (bigger == 2)//A > B по мод
		{
			sum == SUB_NN_N(intA.value, intB.value);
			if (intA.sign == true)
			{
				return Integer(true, sum);
			}
			else
				return Integer(false, sum);
		}
		else if (bigger == 1)//A < B по мод
			sum == SUB_NN_N(intB.value, intA.value);
			if (intA.sign == true)
			{
				return Integer(false, sum);
			}
			else
				return Integer(true, sum);
		return Integer();
	}
	else
		return Integer();
}

Integer Integer::SUB_ZZ_Z(const Integer& intA, const Integer& intB) //Вычитание целых чисел, POZ_Z_D ABS_Z_N COM_NN_D ADD_NN_N SUB_NN_N MUL_ZM_Z
{
	Integer intRevB = MUL_ZM_Z(intB);
	Integer result = ADD_ZZ_Z(intA, intRevB);
	return result;
}

Integer Integer::MUL_ZZ_Z(const Integer& intA, const Integer& intB) // Умножение целых чисел, POZ_Z_D ABS_Z_N MUL_NN_N MUL_ZM_Z
{
	bool mulSign = false;
	if ((POZ_Z_D(intA) != POZ_Z_D(intA)) && (POZ_Z_D(intA) != 0 && POZ_Z_D(intA) != 0))
		mulSign = true;
	Natural mult = MUL_NN_N(intA.value, intB.value);
	return Integer(mulSign, mult);
}

// функции для работы с целыми числами
// делала Анищенко А.И.
Integer Integer::DIV_ZZ_Z(const Integer& a, const Integer& b) { // деление целого на целое
	if (b != Integer("0")) {
		if (a.value >= b.value) {
			Integer result;
			if ((a.value < 0 && b.value > 0) || (a.value > 0 && b.value < 0)) {
				Integer absA = a.value.abs();
				Integer absB = b.value.abs();

				result.value = -(absA.value / absB.value);
			}
			else {
				result.value = a.value / b.value;
			}

			return result;
		}
		else {
			return Integer();
		}
	}
	throw std::string{ "Division by zero!" };
}

// делала Анищенко А.И.
Integer Integer::MOD_ZZ_Z(const Integer& a, const Integer& b) { // остаток от деления целого на целое
	if (b.value != Integer("0")) {
		Integer result;
		if ((a.value < 0 && b.value > 0) || (a.value > 0 && b.value < 0)) {
			Integer absA = a.value.abs();
			Integer absB = b.value.abs();

			result.value = -(absA.value % absB.value);
		}
		else {
			result.value = a.value % b.value;
		}
		return result;
	}
	throw std::string{ "Division by zero!" };
}
