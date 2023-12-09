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
	
	//НОД
	Integer GCF_NN_N(const Integer& a, const Integer& b);
	//НОК
	Integer LCM_NN_N(const Integer&);

	Natural ABS_Z_N(); //Абсолютная величина числа, результат - натуральное
	unsigned int POZ_Z_D(); //Определение положительности числа (2 - положительное, 0 — равное нулю, 1 - отрицательное)
	Integer MUL_ZM_Z();// * на -1
	Integer TRANS_N_Z(const Natural& natural);//Преобразование натурального в целое
	Natural TRANS_Z_N(const Integer& a);//Преобразование целого неотрицательного в натуральное
	Integer ADD_ZZ_Z(const Integer& a);//Сложение целых чисел
	Integer SUB_ZZ_Z(const Integer& a);//Вычитание целых чисел
	Integer MUL_ZZ_Z(const Integer& a);//Умножение целых чисел
	Integer DIV_ZZ_Z(const Integer& a);//Частное от деления целого на целое (делитель отличен от нуля)
	Integer MOD_ZZ_Z(const Integer& a);//Остаток от деления целого на целое(делитель отличен от нуля)
};