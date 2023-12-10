#include "Integer.h"
#include <iostream>
using namespace std;

Integer::Integer()
{
	sign = false;
	value = Natural("0");
}

Integer::Integer(string strInt) // �����������, ���� ������ ������ ����� - ���� ���������� � �������������� ������� ��� ������, ����� + � ��� ����������� Natural
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

std::string Integer::getValue() const // �������� value, ��������� ����
{
	if (sign == true)
		return str_().substr(1, str_().length() - 1);
	return str_().substr(0, str_().length());
}


// ���������� �������� �����, ��������� - �����������
Natural Integer::ABS_Z_N() {
	return value;
}

unsigned int Integer::POZ_Z_D() // ����������� ��������������� ����� (2 - �������������, 0 � ������ ����, 1 - �������������)
{								// ������ �������� �������� sign
	Natural val = value;
	if ((val).isZero())
		return 0;
	if (sign == false)
		return 2;
	if (sign == true)
		return 1;
}

Integer Integer::MUL_ZM_Z() { // ��������� ������ �� -1
	Integer ans;			// �������� �����, ����� �� ���������������
	ans.value = value;
	if (ans.value.isZero() == 1)
		return Integer("0");
	if (sign == true)
		ans.sign = false;
	else
		ans.sign = true;
	return ans;
}

//// �������������� ������������ � �����
Integer Integer::TRANS_N_Z(const Natural& natural) {
	return Integer(false, natural);
}

// �������������� ������ ���������������� � �����������
Natural Integer::TRANS_Z_N(const Integer& integer) { 
	if (sign == true)
		throw "Negative number"; // �������� �� �����������������, ������������ ����������
	// return ABS_Z_N(integer); ����� ������������ ABS_Z_N, �.�. ��� ����� ��������� ��� �������
	return Natural(integer.value);
}

Integer Integer::ADD_ZZ_Z(const Integer& intB) //�������� ����� �����, ABS_Z_N - ������� ���, COM_NN_D - �������� 2 ���, ADD_NN_N SUB_NN_N MUL_ZM_Z - ����� �����
{	//POZ_Z_D - ��� �������(������ ��� ������� � 0, ��� ��� �� ���������.)
	// ��������� �����, ��� ��� ���������� �������� ��������� �������� ����� �����������, ���� ���� ����������� ��������� � �������� �����������
	// � ������ ��������� �� �������� ���������� ������� ����������� ������ ���� ����� - ������ ��� �����������, ������� ����� ������������ 
	// ��������� �� ������ �����, ����� � ������ ��������� �� �������� �������� ���� � ����� ������� �� ��������
	// ����� � ������ ���������� ������ ������������ ������� �������� � ����������� ��������� �����
	// � ������ ������ ������ ������� ��� ��������� �� ������ � ���������
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
		else if (bigger == 2)//A > B �� ���
		{
			sum = (value - intB.value);
			return Integer(sign, sum);
		}
		else if (bigger == 1)//A < B �� ���
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

Integer Integer::SUB_ZZ_Z(const Integer& intB) //��������� ����� �����, POZ_Z_D ABS_Z_N COM_NN_D ADD_NN_N SUB_NN_N MUL_ZM_Z
{												// �������� �� ������ ����� ������� ����������
	Integer tempB = intB;
	Integer intRevB = tempB.MUL_ZM_Z();
	Integer result = ADD_ZZ_Z(intRevB);
	return result;
}

Integer Integer::MUL_ZZ_Z(const Integer& intB) // ��������� ����� �����, POZ_Z_D ABS_Z_N MUL_NN_N MUL_ZM_Z
{						// �������� ��� ������, �������� ��� ��������. ��� ������ ������ - �����, ����� +, ��� 0 ��������� ��������
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

// ������� ��� ������ � ������ �������
Integer Integer::DIV_ZZ_Z(const Integer& b) { // ������� ������ �� �����
												// ������ ���� ����� ���������� ������ ������� MUL � ������������ ������� �����������
	Integer result;
	result.sign = MUL_ZZ_Z(b).sign;
	result.value = value / b.value;
	return result;
}

Integer Integer::MOD_ZZ_Z(const Integer& b) { // ������� �� ������� ������ �� ����� (�� �� �����, ��� � �����������, ������ ��������� ����)
	Integer div = DIV_ZZ_Z(b);
	return Integer(div.sign, value % b.value);
}
