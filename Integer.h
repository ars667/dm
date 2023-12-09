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

	bool getSign() const;
	void print() const;
	std::string str_() const;
	std::string getValue() const;
	
	//���
	Integer GCF_NN_N(const Integer& a, const Integer& b);
	//���
	Integer LCM_NN_N(const Integer&);

	Natural ABS_Z_N(); //���������� �������� �����, ��������� - �����������
	unsigned int POZ_Z_D(); //����������� ��������������� ����� (2 - �������������, 0 � ������ ����, 1 - �������������)
	Integer MUL_ZM_Z();// * �� -1
	Integer TRANS_N_Z(const Natural& natural);//�������������� ������������ � �����
	Natural TRANS_Z_N(const Integer& a);//�������������� ������ ���������������� � �����������
	Integer ADD_ZZ_Z(const Integer& a);//�������� ����� �����
	Integer SUB_ZZ_Z(const Integer& a);//��������� ����� �����
	Integer MUL_ZZ_Z(const Integer& a);//��������� ����� �����
	Integer DIV_ZZ_Z(const Integer& a);//������� �� ������� ������ �� ����� (�������� ������� �� ����)
	Integer MOD_ZZ_Z(const Integer& a);//������� �� ������� ������ �� �����(�������� ������� �� ����)
};