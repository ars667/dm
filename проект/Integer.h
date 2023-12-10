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

	Natural ABS_Z_N(); //јбсолютна€ величина числа, результат - натуральное
	unsigned int POZ_Z_D(); //ќпределение положительности числа (2 - положительное, 0 Ч равное нулю, 1 - отрицательное)
	Integer MUL_ZM_Z();// * на -1
	Integer TRANS_N_Z(const Natural& natural);//ѕреобразование натурального в целое
	Natural TRANS_Z_N(const Integer&);//ѕреобразование целого неотрицательного в натуральное
	Integer ADD_ZZ_Z(const Integer&);//—ложение целых чисел
	Integer SUB_ZZ_Z(const Integer&);//¬ычитание целых чисел
	Integer MUL_ZZ_Z(const Integer&);//”множение целых чисел
	Integer DIV_ZZ_Z(const Integer&);//„астное от делени€ целого на целое (делитель отличен от нул€)
	Integer MOD_ZZ_Z(const Integer&);//ќстаток от делени€ целого на целое(делитель отличен от нул€)
};
