#include "RationalNumbers.h"
#include "BigInt.h"

Rational::Rational(): nominator("0"), denominator("1") 
{
}

Rational::Rational(BigInt nominator, Natural denominator)
{
	if (denominator.getDigit(denominator.getSize()))
	{
		this->nominator = nominator;
		this->denominator = denominator;
	}
	throw std::string{ "Division by zero!" };
}

Rational::Rational(bool sign, string str_nom, string str_denom): nominator(sign, str_nom), denominator(str_denom) 
{
}

Rational Rational::RED_Q_Q(const Rational& Rati)//Сокращение дроби || Ссылка на ABS_Z_N,  GCF_NN_N  и  DIV_ZZ_Z
{		// ABS_Z_N - модуль числа, GCF_NN_N - нод натуральных чисел, 
		
	BigInt nominator = BigInt::DIV_ZZ_Z(Rati.nominator, BigInt::TRANS_N_Z(Natural::GCF_NN_N(BigInt::TRANS_Z_N(Rati.nominator), Rati.denominator)));
	Natural denominator = Natural::DIV_NN_N(Rati.denominator, Natural::GCF_NN_N(BigInt::TRANS_Z_N(Rati.nominator), Rati.denominator));
	Rational ans(nominator, denominator);
	return ans;
}		// DIV_ZZ_Z - частное от деления целого на целое

bool Rational::INT_Q_B(const Rational& Rati)//Проверка сокращенного дробного на целое, если рациональное число является целым, то «да», иначе «нет»
{
	Natural natNom = BigInt::TRANS_Z_N(Rati.nominator);
	if (Natural::COM_NN_D(natNom, Rati.denominator) != 0)
		return false;
	else
		return true;
}

Rational Rational::TRANS_Z_Q(const BigInt& nom)//Преобразование целого в дробное
{
	Rational ans = Rational(nom, Natural("1"));
	return ans;
}

BigInt Rational::TRANS_Q_Z(const Rational& Rati)//Преобразование сокращенного дробного в целое (если знаменатель равен 1)
{
	if (!(Rati.denominator.getDigit(0) == 1 && Rati.denominator.getSize() == 1)) 
	{
		return Rati.nominator;
	}
	throw std::string{ "Denominator is not 1!" };
	return BigInt(false, Natural("0"));
}

Rational Rational::ADD_QQ_Q(const Rational& ratA, const Rational& ratB)//Сложение дробей || Ссылка на LCM_NN_N и MUL_ZZ_Z
{							// LCM_NN_N - НОК натуральных чисел, MUL_ZZ_Z - умножение целых чисел, add_zz_z - сложение
	BigInt totDenom = BigInt::TRANS_N_Z(Natural::LCM_NN_N(ratA.denominator, ratB.denominator));
	Rational ratC;
	ratC.nominator = totDenom;
	ratC.denominator = ratA.denominator;
	Rational ratD;
	ratD.nominator = totDenom;
	ratD.denominator = ratB.denominator;
	Rational total;
	total.denominator = BigInt::TRANS_Z_N(totDenom);
	total.nominator = BigInt::ADD_ZZ_Z(BigInt::MUL_ZZ_Z(ratA.nominator, TRANS_Q_Z(RED_Q_Q(ratC))),
		BigInt::MUL_ZZ_Z(ratB.nominator, TRANS_Q_Z(RED_Q_Q(ratD))));
	return RED_Q_Q(total);
}


Rational Rational::SUB_QQ_Q(const Rational& ratA, const Rational& ratB) //Вычитание дробей
{ //sub - вычитание. Всё аналогично сложению. Без копипасты придётся делать доп модуль, так что только так. Отличается только total.nominator
	BigInt totDenom = BigInt::TRANS_N_Z(Natural::LCM_NN_N(ratA.denominator, ratB.denominator));
	Rational ratC;//Вычитание дробей || Ссылка на LCM_NN_N, MUL_ZZ_Z и SUB_ZZ_Z
	ratC.nominator = totDenom;
	ratC.denominator = ratA.denominator;
	Rational ratD;
	ratD.nominator = totDenom;
	ratD.denominator = ratB.denominator;
	Rational total;
	total.denominator = BigInt::TRANS_Z_N(totDenom);
	total.nominator = BigInt::SUB_ZZ_Z(BigInt::MUL_ZZ_Z(ratA.nominator, TRANS_Q_Z(RED_Q_Q(ratC))),
		BigInt::MUL_ZZ_Z(ratB.nominator, TRANS_Q_Z(RED_Q_Q(ratD))));
	return RED_Q_Q(total);
}

Rational Rational::MUL_QQ_Q(const Rational& ratA, const Rational& ratB)
{//Умножение дробей || Ссылка на MUL_ZZ_Z
	BigInt nom = BigInt::MUL_ZZ_Z(ratA.nominator, ratB.nominator);
	Natural denom = Natural::MUL_NN_N(ratA.denominator, ratB.denominator);
	Rational ans(nom, denom);
	return RED_Q_Q(ans);
}

Rational Rational::DIV_QQ_Q(const Rational& ratA, const Rational& ratB)
{//Деление дробей (делитель отличен от нуля) || Ссылка на MUL_ZZ_Z
	bool signB = ratB.nominator.getSign();
	Rational revRatB(BigInt::TRANS_N_Z(ratB.denominator), BigInt::TRANS_Z_N(ratB.nominator));//переворачиваем вторую дробь
	if (signB == true)//если минус был потерян, то через MUL_ZM_Z меняем знак(не путать с ZZ_Z) 
	{
		revRatB.nominator = BigInt::MUL_ZM_Z(revRatB.nominator);
	}
	Rational ans = MUL_QQ_Q(ratA, revRatB);
	return RED_Q_Q(ans);
}
