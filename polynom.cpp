#include "polynom.h"
#include "mathFunc.h"
#include <set>

#define FREE_TERM 1

using namespace std;

bool Polynomial::poly_empty() {
    Polynomial poly = (*this);
    return poly.coef.size() == 1 && poly.coef[0].first == 0;
}

Polynomial::Polynomial(vector<pair<int, int>> coefficients) {
    for (auto pair : coefficients) {
        if (pair.second == 0) {
            std::cout << "Divide by zero!";
            exit(0);
        }
    }
    if (coefficients.size() < 1) {
        std::cout << "Not a polynom!";
        exit(0);
    }
    else {
        coef = coefficients;
        //cout << "dfsdf";
    }
}

void Polynomial::norm_polynom(){
    vector<pair<int, int>> coeff_this = (*this).coef;
    reverse(coeff_this.begin(), coeff_this.end());
    while (coeff_this.size() > 1 && coeff_this.back().first == 0) {
        coeff_this.pop_back();
    }
    reverse(coeff_this.begin(), coeff_this.end());
    (*this).coef = coeff_this;
}
Polynomial Polynomial::mul_pol(Polynomial poly1) {
    Polynomial poly2 = *this;
    vector<pair<int, int>> coeff = poly1.coef;
    vector<pair<int, int>> other_coeff = poly2.coef;
    reverse(other_coeff.begin(), other_coeff.end());
    reverse(coeff.begin(), coeff.end());
    vector<pair<int, int>> new_coeff = { {0,1}, {0,1} };
    Polynomial poly_result(new_coeff);
    //cout << "dfsdf";
    for (int i = 0; i < coeff.size(); ++i) {
        poly_result = poly_result + poly2.multiplyByXk(i) * coeff[i];
    }
    poly_result.norm_polynom();
    return poly_result;
}

Polynomial Polynomial::DIV_PP_P(Polynomial poly_n) {
    Polynomial poly_q({ {0,1} });
    Polynomial poly_m = *this;
    Polynomial poly_r = poly_m;
    while (poly_m.degree() >= poly_n.degree()) {
        Polynomial poly_x({ { 1,1 }, { 0,1 } });//P = x
        Polynomial poly_zero({ { 1,1 } });//P = 1
        pair<int, int> coeff = DIV_QQ_Q(poly_m.leadingCoefficientPair(), poly_n.leadingCoefficientPair());
        Polynomial poly_t({ { 0,1 } });
        if (poly_m.degree() != poly_n.degree()) {
            poly_t = poly_x.multiplyByXk(poly_m.degree() - poly_n.degree() - 1) * coeff;
        }
        else {
            poly_t = poly_zero * coeff;
        }
        poly_t.norm_polynom();
        //cout << "poly_t " << poly_t.visual() << "\n";

        poly_q = poly_q + poly_t;//+
        poly_q.norm_polynom();
        poly_r = poly_m - poly_n.mul_pol(poly_t);//+
        poly_r.norm_polynom();
        //cout << "R: " << poly_r.visual() << "\n";
        poly_m = poly_r;
        //cout << poly_m.visual() << "\n";
        //cout << "deq1: " << poly_m.degree() << " " << "deq2: " << poly_n.degree() << "\n";
        
    }
    poly_q.norm_polynom();
    return poly_q;
}

Polynomial Polynomial::DER_P_P() {
    Polynomial poly = *this;
    vector<pair <int, int>> new_coeff;
    for (int i = 0; i < poly.coef.size()-1; ++i) {
        std::pair <int, int> coeff = MUL_QQ_Q(make_pair((poly.coef.size() - 1 - i), 1), poly.coef[i]);
        RED_Q_Q(coeff);
        new_coeff.push_back(coeff);
    }
    return Polynomial(new_coeff);
}
vector<pair<int, int>> Polynomial::get_coef() {
    return coef;
}
Polynomial Polynomial::add_polynom(Polynomial poly1, Polynomial poly2, bool minus) {
    std::vector<std::pair<int, int>> new_coef;
    std::vector<std::pair<int, int>> coeff = poly1.coef;
    std::vector<std::pair<int, int>> other_coeff = poly2.coef;

    reverse(other_coeff.begin(), other_coeff.end());
    reverse(coeff.begin(), coeff.end());

    size_t m = std::min(coeff.size(), other_coeff.size());
    for (size_t i = 0; i < m; ++i) {
        std::pair<int, int> p = ADD_QQ_Q(coeff[i], other_coeff[i], minus);
        new_coef.push_back(p);
    }
    if (coeff.size() > m) {
        for (size_t i = m; i < coeff.size(); ++i) {
            new_coef.push_back(coeff[i]);
        }
    }
    else {
        for (size_t i = m; i < other_coeff.size(); ++i) {
            new_coef.push_back(other_coeff[i]);
        }
    }
    
    reverse(new_coef.begin(), new_coef.end());
    
    return Polynomial(new_coef);
}

Polynomial Polynomial::ost_div_pp(Polynomial poly_n) {
    Polynomial poly_m = (*this);
    Polynomial poly_r = poly_m - poly_n.mul_pol(poly_m.DIV_PP_P(poly_n));
    poly_r.norm_polynom();
    return poly_r;
}

//Polynomial Polynomial::nod_polynom(Pol)
// Сложение двух многочленов
Polynomial Polynomial::operator+(const Polynomial& other) {
    Polynomial poly = Polynomial::add_polynom(*this, other, false);
    return poly;
}

// Вычитание двух многочленов
Polynomial Polynomial::operator-(const Polynomial& other){
    Polynomial poly = add_polynom(*this, other, true);
    return poly;
}

// Умножение многочлена на рациональное число(только справо)
Polynomial Polynomial::operator*(int scalar) const {
    Polynomial result = *this;
    for (auto& term : result.coef) {
        term.first *= scalar;
        RED_Q_Q(term);
    }
    return result;
}

Polynomial Polynomial::operator*(std::pair<int, int> fraction) const {
    if (fraction.second == 0) {
        std::cout << "Divide by zero!";
        exit(0);
    }
    Polynomial result = *this;
    for (auto& p : result.coef) {
        p.first *= fraction.first;
        p.second *= fraction.second;
        RED_Q_Q(p);
    }
    return result;
}

// Умножение многочлена на x^k Особенности: возвращает новый полином, не меняя текущий
Polynomial Polynomial::multiplyByXk(int k) const {
    Polynomial result = *this;
    for (int i = 0; i < k; ++i) {
        result.coef.push_back(make_pair(0, 1));
    }
    return result;
}

// Нахождение старшего коэффициента многочлена
pair<int, int> Polynomial::leadingCoefficientPair() {
    return coef[0];
}

double Polynomial::leadingCoefficientNum() {
    return static_cast<double>(leadingCoefficientPair().first) / leadingCoefficientPair().second;
}

// Нахождение степени многочлена
size_t Polynomial::degree() const {
    return coef.size() - FREE_TERM;
}

std::pair<int, int> Polynomial::calculateLCMandGCD() {
    int commonDenominator = 1;
    int commonNumerator = 0;

    for (const auto& term : coef) {
        commonDenominator = LCM_NN_N(commonDenominator, term.second);
        commonNumerator = GCF_NN_N(commonNumerator, term.first);
    }

    return std::make_pair(commonNumerator, commonDenominator);
}

void Polynomial::nod_nok() {
    std::pair<int, int> result = calculateLCMandGCD();
    std::pair<int, int> p = make_pair(result.second, result.first);

    std::cout << "НОД числителей: " << result.first << std::endl;
    std::cout << "НОК знаменателей: " << result.second << std::endl;
    std::cout << result.first << "/" << result.second << "*(";
    Polynomial help = *this;
    help = help * p;
    std::cout << help.visual();
    std::cout << ")\n";
}


std::string Polynomial::visual() {
    std::string str;
    size_t deg = coef.size() - FREE_TERM;
    int i = 0;
    std::pair<int, int> p;
    std::string substr;
    while (deg > 1) {
        p = coef[i];
        if (p.first == 0) {
            deg--;
            i++;
            continue;
        }
        if (p.first % p.second == 0) {
            string s = p.first / p.second == 1 ? "" : to_string(p.first / p.second);
            substr = s + "x^" + to_string(deg);
            if (!(coef[i + 1].first < 0 || coef[i + 1].second < 0))
                substr += "+";
        }
        else {
            substr = "(" + to_string(p.first) + "/" + to_string(p.second) + ")" + "x^" + to_string(deg);
            if (!(coef[i + 1].first < 0 || coef[i + 1].second < 0))
                substr += "+";
        }
        str += substr;
        i++;
        deg--;
    }
    if (coef.size() >= 2) {
        // Отдельный случай просто икс
        p = coef[coef.size() - 2];
        if (p.first != 0) {
            if (p.first % p.second == 0) {
                string s = p.first / p.second == 1 ? "" : to_string(p.first / p.second);
                substr = s + "x";
                if (!(coef[i + 1].first < 0 || coef[i + 1].second < 0))
                    substr += "+";
            }
            else {
                substr = "(" + to_string(p.first) + "/" + to_string(p.second) + ")" + "x";
                if (!(coef[i + 1].first < 0 || coef[i + 1].second < 0))
                    substr += "+";
            }
            str += substr;
        }
        
    }
    // Отдельный случай свободный член
    p = coef[coef.size() - 1];
    if (p.first != 0) {
        if (p.first % p.second == 0) {
            substr = to_string(p.first / p.second);
        }
        else {
            substr = to_string(p.first) + "/" + to_string(p.second);
        }
        str += substr;
    }
    //удаление возможных плюсов в конце
    while (not str.empty() && str.back() == '+') {
        str.pop_back();
    }
    return str;
}

void Polynomial::simplify() {
    for (auto& term : coef) {
        RED_Q_Q(term);
    }
}



