#pragma once
#include "Natural.h"
#include <string>

class Integer 
{
	bool sign; // 1 ��� '-', 0 '+'
	Natural value;
public:
	Integer();
	Integer(std::string strInt);
	Integer(bool sign, Natural value);

	long long int getValue() const; //��������� ����� value � int, ���� ������ 10 ������
	int getDigit(unsigned int rank) const; //������ ����� �� �������
	int getRank() const; //������ ����������� ��������
	bool getSign() const;

	Natural ABS_Z_N(const Integer&); //���������� �������� �����, ��������� - �����������
	unsigned int POZ_Z_D(const Integer&); //����������� ��������������� ����� (2 - �������������, 0 � ������ ����, 1 - �������������)
	Integer MUL_ZM_Z(const Integer&);// * �� -1
	Integer TRANS_Z_N(const Natural&);//�������������� ������������ � �����
	Natural TRANS_N_Z(const Integer&);//�������������� ������ ���������������� � �����������
	Integer ADD_ZZ_Z(const Integer&, const Integer&);//�������� ����� �����
	Integer SUB_ZZ_Z(const Integer&, const Integer&);//��������� ����� �����
	Integer MUL_ZZ_Z(const Integer&, const Integer&);//��������� ����� �����
	Integer DIV_ZZ_Z(const Integer&, const Integer&);//������� �� ������� ������ �� ����� (�������� ������� �� ����)
	Integer MOD_ZZ_Z(const Integer&, const Integer&);//������� �� ������� ������ �� �����(�������� ������� �� ����)
};
