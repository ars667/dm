#include "Rational.h"
#include "Integer.h"
#include <iostream>

Rational::Rational() : nominator("0"), denominator("1")
{
}

Rational::Rational(Integer nominator, Natural denominator)
{
	if (denominator.isZero())
	{
		throw std::string{ "Division by zero!" };
	}
	this->nominator = nominator;
	this->denominator = denominator;
}

Rational::Rational(std::string rat)
{
	if (rat.find("/") > 1000) // ��� ������������ ����� ����� ������
	{
		denominator = Natural("1");
		nominator = Integer(rat);
	}
	else
	{
		int slash = rat.find("/");
		nominator = Integer(rat.substr(0, slash + 1));
		int len = rat.length() - slash - 1;
		denominator = Natural(rat.substr(slash + 1, len));
	}
}

void Rational::print() const
{
	std::string ans;
	ans.append(nominator.str_());
	Natural denom = denominator;
	if (denom.isOne() == 1)
		std::cout << ans;
	else
	{
		ans.append("/");
		ans.append(denominator.str_());
		std::cout << ans;
	}
}

std::string Rational::str_() const
{
	std::string ans;
	ans.append(nominator.str_());
	Natural denom = denominator;
	if (denom.isOne() == 1)
		return ans;
	ans.append("/");
	ans.append(denominator.str_());
	return ans;
}

Rational Rational::RED_Q_Q(const Rational& ConstRati)//���������� ����� || ������ �� ABS_Z_N,  GCF_NN_N  �  DIV_ZZ_Z
{		// ABS_Z_N - ������ �����, GCF_NN_N - ��� ����������� �����, 
	Rational Rati = ConstRati;
	if (Natural(Rati.nominator.getValue()).isZero() == 1)
    return Rational("0");
	int sign = Rati.nominator.getSign();
	Integer unsignedNominator = Integer(Rati.nominator.getValue());
	Integer nominat = unsignedNominator.DIV_ZZ_Z(unsignedNominator.Integer::TRANS_N_Z(unsignedNominator.TRANS_Z_N(unsignedNominator).Natural::gcd(Rati.denominator)));
	Natural denominat = (Rati.denominator / unsignedNominator.Integer::TRANS_Z_N(unsignedNominator).Natural::gcd(Rati.denominator));
	std::string temp;
	if (sign == 1)
		temp.append("-");
	temp.append(nominat.getValue());
	Rational ans(temp, denominat);
	return ans;
}		// DIV_ZZ_Z - ������� �� ������� ������ �� �����

bool Rational::INT_Q_B(const Rational& ConstRati)//�������� ������������ �������� �� �����, ���� ������������ ����� �������� �����, �� ���, ����� ����
{
	Integer nom;
	int sign = ConstRati.nominator.getSign();
	if (sign == 1)
	{
		nom = Integer(ConstRati.nominator.getValue());
	}
	else
		nom = ConstRati.nominator;
	Natural natNom = nom.Integer::TRANS_Z_N(nom);
	Rational rat = ConstRati;
	if (rat.denominator.isOne())
		return true;
	else
		return false;
}

Rational Rational::TRANS_Z_Q(const  Integer& nom)//�������������� ������ � �������
{
	Rational ans = Rational(nom, Natural("1"));
	return ans;
}

Integer Rational::TRANS_Q_Z(const Rational& ConstRati)//�������������� ������������ �������� � ����� (���� ����������� ����� 1)
{
	Rational rati = ConstRati;
	if ((rati.denominator.isOne() == 1))
	{
		return rati.nominator;
	}
	throw std::string{ "Denominator is not 1!" };
	return  Integer(false, Natural("0"));
}

Rational Rational::ADD_QQ_Q(const Rational& constRatB)//�������� ������ || ������ �� LCM_NN_N(lcm) � MUL_ZZ_Z
{							// LCM_NN_N - ��� ����������� �����, MUL_ZZ_Z - ��������� ����� �����, add_zz_z - ��������
	Rational ratB = constRatB;
	Natural totDenom = (denominator.Natural::lcm(ratB.denominator));
	Natural mulA = totDenom / denominator; // �� ������� ���� ��������� ��������� �
	Natural mulB = totDenom / ratB.denominator; // ��� B
	Rational ratAM;
	ratAM.nominator = nominator.MUL_ZZ_Z(nominator.TRANS_N_Z(mulA));
	ratAM.denominator = totDenom;
	Rational ratBM;
	ratBM.nominator = ratB.nominator.MUL_ZZ_Z(ratB.nominator.TRANS_N_Z(mulB));
	ratBM.denominator = totDenom;
	Rational total;
	total.denominator = totDenom;
	total.nominator = ratAM.nominator.ADD_ZZ_Z(ratBM.nominator);
	return RED_Q_Q(total);
}


Rational Rational::SUB_QQ_Q(const Rational& constRatB) //��������� ������
{ //sub - ���������. �� ���������� ��������. ���������� ������� ����� ����� ��� 2�� ���������
	Rational tempRatB = constRatB;
	Integer revB = tempRatB.nominator.MUL_ZM_Z();
	Rational ratB = Rational(revB, tempRatB.denominator);
	return RED_Q_Q(ADD_QQ_Q(ratB));
}

Rational Rational::MUL_QQ_Q(const Rational& ConstRatB)
{//��������� ������ || ������ �� MUL_ZZ_Z
	Rational ratB = ConstRatB;
	Integer nom = nominator.Integer::MUL_ZZ_Z(ratB.nominator);
	Natural denom = (denominator * ratB.denominator);
	Rational ans(nom, denom);
	return RED_Q_Q(ans);
}

Rational Rational::DIV_QQ_Q(const Rational& constRatB)
{//������� ������ (�������� ������� �� ����) || ������ �� MUL_ZZ_Z
	Rational ratB = constRatB;
	bool signB = ratB.nominator.getSign();
	Natural unsNominator = Natural(ratB.nominator.getValue());
	Rational revRatB(nominator.Integer::TRANS_N_Z(ratB.denominator), unsNominator);//�������������� ������ �����
	if (signB == true)//���� ����� ��� �������, �� ����� MUL_ZM_Z ������ ����(�� ������ � ZZ_Z) 
	{
		revRatB.nominator = revRatB.nominator.Integer::MUL_ZM_Z();
	}
	Rational ans = MUL_QQ_Q(revRatB);
	return RED_Q_Q(ans);
}
Integer Rational::get_nominator()
{
	return nominator;
}

Natural Rational::get_denominator()
{
	return denominator;
}

bool Rational::is_zero() {
	return (nominator.getValue() == "0");
}