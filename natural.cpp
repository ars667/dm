#include "Natural.h"
#include <iostream>
#include <cmath>

Natural::Natural()
{
}

Natural::Natural(std::string s) //s - число в виде строки, которое нужно преобразовать в класс 
{
    int len = s.length(); //получает длину строки и сохраняет её в переменной len
    for (int i = len - 1; i >= 0; i--) //проходит по строке s в обратном порядке, начиная с последнего символа. Это делается с помощью цикла for, который итерируется от len - 1 до 0.
    {
        char c = s[i]; 
        if (c >= '0' && c <= '9') //проверяет, если символ является цифрой, то преобразует символл в число
        {
            this->digit.push_back(c - '0'); //добавляет в вектор digit
        }
    }
    this->n = digit.size(); //устанавливает значение n равным размеру вектора digit. Значение n представляет собой количество цифр в числе.
}

Natural Natural::operator+(const Natural& other)
{
    Natural result("");
    int carry = 0; //carry - для хранения переноса при сложении цифр

    for (int i = 0; i < std::max(n, other.n) || carry; ++i)
    {
        if (i == result.n) //если текущий индекс i равен количеству цифр в result, она увеличивает количество цифр в result.
            // result.digit.push_back(0);
            result.n++;
        int sum = carry + (i < n ? digit[i] : 0) + (i < other.n ? other.digit[i] : 0); //она вычисляет сумму текущего переноса и текущих цифр в обоих числах (или 0, если одно из чисел уже полностью обработано).
        result.digit.push_back(sum % 10); //добавляет остаток от деления суммы на 10 в вектор цифр result и обновляет перенос, делением суммы на 10.
        carry = sum / 10;
    }

    result.n = result.digit.size(); //обновляет количество цифр в result и возвращает result.
    return result;
}

Natural Natural::operator-(const Natural& other)
{
    if ((*this > other == 1) || (*this > other == 0)) //проверяет, больше ли исходное число (*this) или равно числу other.
    {
        return Natural("0"); //т.к. нельзя вычесть большее число из меньшего
    }

    Natural result("");
    int borrow = 0; //borrow - для хранения заема при вычитании цифр.

    for (int i = 0; i < std::max(n, other.n) || borrow; ++i) //ычисляет разность текущего заема и текущих цифр в обоих числах (или 0, если одно из чисел уже полностью обработано
    {
        int sub = (i < n ? digit[i] : 0) - borrow - (i < other.n ? other.digit[i] : 0);

        if (sub < 0) //добавляет 10 к разности и устанавливает заем равным 1.
        {
            sub += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0; //устанавливает заем равным 0.
        }

        if (i == result.n) //если текущий индекс i равен количеству цифр в result
        {
            // result.digit.push_back(0);
            result.n++; //увеличивает количество цифр в result
        }

        result.digit.push_back(sub);
    }

    while (result.n > 1 && result.digit.back() == 0) //удаляет все незначащие нули в начале числа (если они есть)
    {
        result.digit.pop_back();
        result.n--;
    }

    return result;
}

Natural Natural::operator*(const Natural& other)
{
    Natural result("");

    for (int i = 0; i < n; ++i)
    {
        int carry = 0; //carry для хранения переноса при умножении цифр 
        Natural temp("");

        for (int j = 0; j < other.n || carry; ++j) //проходит по каждой цифре числа other или пока есть перенос
        {
            if (j == temp.n) //если текущий индекс j равен количеству цифр в temp, она добавляет 0 в вектор цифр temp и увеличивает количество цифр в temp
                temp.digit.push_back(0);
            temp.n++;

            int product = carry + digit[i] * (j < other.n ? other.digit[j] : 0); //вычисляет произведение текущего переноса и текущих цифр в обоих числах (или 0, если одно из чисел уже полностью обработано).
            temp.digit[j] = product % 10;
            carry = product / 10; //обновляет перенос, делением произведения на 10
        }

        for (int j = 0; j < temp.n; ++j) //для сдвига цифр в temp
            temp.digit[j] *= pow(10, i); //умножает каждую цифру в temp на 10 в степени i
        result = result + temp;
    }

    return result;
}

Natural Natural::operator/(const Natural& other)
{
    if (other.isZero())
    {
        throw std::invalid_argument("Division by zero"); //функция выбрасывает исключение, так как деление на ноль не определено.
    }
    Natural result("0"); 

    Natural currentDividend = *this; // currentDividend - инициализируется значением исходного объекта. Этот объект будет использоваться для хранения текущего делимого в процессе деления.

    while (currentDividend > other == 2 || currentDividend > other == 0) //пока currentDividend больше или равен other
    {
        currentDividend = currentDividend - other; //вычитает other из currentDividend и увеличивает result на 1
        result = result + Natural("1");
    }

    return result;
}

Natural Natural::operator%(const Natural& other)
{
    if (other.isZero())
    {
        throw std::invalid_argument("Division by zero"); //выбрасывает исключение, так как деление на ноль не определено
    }
    if (*this > other == 1)
    {
        return *this; //возвращает исходное число
    }
    Natural currentDividend = *this; //для хранения текущего делимого в процессе деления.

    while (currentDividend > other == 2 || currentDividend > other == 0) // на каждом шаге вычитается делитель из текущего делимого.
    {
        currentDividend = currentDividend - other;
    }

    return currentDividend; //currentDividend, который теперь содержит остаток от деления исходного числа на other
}

int Natural::operator>(const Natural& other)
{
    if (this->n > other.n)
    {
        return 2;
    }
    else if (this->n < other.n)
    {
        return 1;
    }
    else
    {
        for (int i = this->n - 1; i >= 0; i--)
        {
            if (this->digit[i] > other.digit[i])
            {
                return 2;
            }
            else if (this->digit[i] < other.digit[i])
            {
                return 1;
            }
        }
        return 0;
    }
}

Natural Natural::gcd(const Natural& other)
{
    Natural a = *this;
    Natural b = other;
    while (!b.isZero())
    {
        Natural temp_b = b; 
        b = a % b;
        a = temp_b; //обновляет b на остаток от деления a на b и обновляет a на значение temp_b
    }

    return a; //a, который теперь содержит НОД исходного числа и other
}

Natural Natural::lcm(const Natural& other)
{
    Natural gcd_result = this->gcd(other); //умножая исходный объект и аргумент, а затем делая полученное произведение на gcd_result

    Natural lcm_result = (*this * other) / gcd_result;

    return lcm_result; //lcm_result, который теперь содержит НОК исходного числа и other.
}

int Natural::isZero() const
{
    if (this->digit.empty())
    {
        return 1;
    }
    if ((this->n) == 1 && (this->digit[0]) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Natural::isOne()
{
    if ((this->n) == 1 && (this->digit[0]) == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Natural::print() const
{
    if (digit.empty())
    {
        std::cout << "0";
    }
    else
    {
        for (int i = n - 1; i >= 0; --i)
        {
            std::cout << digit[i];
        }
    }
    std::cout << std::endl;
}

void Natural::check()
{
    std::cout << this->n << std::endl;
    if (digit.empty())
    {
        std::cout << "EMP";
    }
    else
    {
        for (int i = n - 1; i >= 0; --i)
        {
            std::cout << digit[i] << std::endl;
        }
    }
}

std::string Natural::str_() const
{
    std::string ans;
    for (int i = n - 1; i >= 0; --i)
    {
        ans.append(std::to_string(digit[i]));
    }
    return ans;
}

Natural Natural::add1()
{
    Natural num("1");
    return *this + num;
}

std::string Natural::getDigit()
{
    std::string s;
    for (int i = 0; i < this->n; i++)
    {
        char c = static_cast<char>(i);
        s += c;
    }
    return s;
}
