#pragma once
#include "Natural.h"

class Integer 
{
	bool sign; // 1 это '-', 0 '+'
	Natural value;
public:
	Integer();
	Integer(string strInt);
	Integer(bool sign, Natural value);

	long long int getValue() const; //перевести часть value в int, если меньше 10 знаков
	int getDigit(unsigned int rank) const; //узнать цифру по разр€ду
	int getRank() const; //узнать колличество разр€дов
	bool getSign() const;

	Natural ABS_Z_N(const Integer&); //јбсолютна€ величина числа, результат - натуральное
	unsigned int POZ_Z_D(const Integer&); //ќпределение положительности числа (2 - положительное, 0 Ч равное нулю, 1 - отрицательное)
	Integer MUL_ZM_Z(const Integer&);// * на -1
	Integer TRANS_Z_N(const Natural&);//ѕреобразование натурального в целое
	Natural TRANS_N_Z(const Integer&);//ѕреобразование целого неотрицательного в натуральное
	Integer ADD_ZZ_Z(const Integer&, const Integer&);//—ложение целых чисел
	Integer SUB_ZZ_Z(const Integer&, const Integer&);//¬ычитание целых чисел
	Integer MUL_ZZ_Z(const Integer&, const Integer&);//”множение целых чисел
	Integer DIV_ZZ_Z(const Integer&, const Integer&);//„астное от делени€ целого на целое (делитель отличен от нул€)
	Integer MOD_ZZ_Z(const Integer&, const Integer&);//ќстаток от делени€ целого на целое(делитель отличен от нул€)
};
