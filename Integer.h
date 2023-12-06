#pragma once
#include "Natural.h"
#include <string>

class Integer
{
	bool sign; // 1 это '-', 0 '+'
	Natural value;
public:
	Integer();
	Integer(std::string strInt);
	Integer(bool sign, Natural value);

	bool getSign() const;
	void print() const;
	std::string str_() const;
	std::string getValue() const;

	Natural ABS_Z_N(); //Абсолютная величина числа, результат - натуральное
	unsigned int POZ_Z_D(); //Определение положительности числа (2 - положительное, 0 — равное нулю, 1 - отрицательное)
	Integer MUL_ZM_Z();// * на -1
	Integer TRANS_N_Z(const Natural& natural);//Преобразование натурального в целое
	Natural TRANS_Z_N(const Integer&);//Преобразование целого неотрицательного в натуральное
	Integer ADD_ZZ_Z(const Integer&);//Сложение целых чисел
	Integer SUB_ZZ_Z(const Integer&);//Вычитание целых чисел
	Integer MUL_ZZ_Z(const Integer&);//Умножение целых чисел
	Integer DIV_ZZ_Z(const Integer&);//Частное от деления целого на целое (делитель отличен от нуля)
	Integer MOD_ZZ_Z(const Integer&);//Остаток от деления целого на целое(делитель отличен от нуля)
};