#pragma once
#include<vector>

//НОК
int GCF_NN_N(int a, int b);

//НОД
int LCM_NN_N(int a, int b);

// Сокращение дроби
void RED_Q_Q(std::pair<int, int>& fraction);

//Сложение дробей
std::pair<int, int> ADD_QQ_Q(std::pair<int, int> fraction1, std::pair<int, int> fraction2, bool minus = false);
std::pair<int, int> MUL_QQ_Q(std::pair<int, int> fraction1, std::pair <int, int> fraction2);
std::pair<int, int> DIV_QQ_Q(std::pair<int, int> fraction1, std::pair <int, int> fraction2);