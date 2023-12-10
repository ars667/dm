#include "Polynomial.h"

#include <set>

#define FREE_TERM 1
//#define int long long
using namespace std;

bool Polynomial::poly_empty() {
    Polynomial poly = (*this);
    vector<std::string> zero{ "0", "+0", "-0" };
    return poly.coef.size() == 1 && std::count(zero.begin(), zero.end(), poly.coef[0].get_nominator().getValue());//
}


Polynomial::Polynomial(vector<Rational> coefficients) {//
    if (coefficients.size() < 1) {
        std::cout << "Not a polynom!";
        exit(0);
    }
    else {
        coef = coefficients;
    }
}

void Polynomial::norm_polynom() {
    vector<Rational> coeff_this = (*this).coef;//
    reverse(coeff_this.begin(), coeff_this.end());
    while (coeff_this.size() > 1 && coeff_this.back().get_nominator().POZ_Z_D() == 0) {//
        coeff_this.pop_back();
    }
    reverse(coeff_this.begin(), coeff_this.end());
    (*this).coef = coeff_this;
}
Polynomial Polynomial::mul_pol(Polynomial poly1) {
    Polynomial poly2 = *this;
    vector<Rational> coeff = poly1.coef;//
    vector<Rational> other_coeff = poly2.coef;//
    reverse(other_coeff.begin(), other_coeff.end());
    reverse(coeff.begin(), coeff.end());
    vector<Rational> new_coeff = { Rational(Integer("0"),Natural("1")) };
    Polynomial poly_result(new_coeff);
    for (int i = 0; i < coeff.size(); ++i) {
        poly_result = poly_result + poly2.multiplyByXk(i) * coeff[i];
        //poly_result.visual();
        //cout << "\n";
    }
    //cout << "afaddas\n";
    poly_result.norm_polynom();
    return poly_result;
}

Polynomial Polynomial::DIV_PP_P(Polynomial poly_n) {
    Polynomial poly_q({ Rational(Integer("0"), Natural("1")) });
    Polynomial poly_m = *this;
    Polynomial poly_r = poly_m;
    while (!poly_m.poly_empty() && poly_m.degree() >= poly_n.degree()) {
        Polynomial poly_x({ Rational(Integer("1"), Natural("1")), Rational(Integer("0"), Natural("1")) });//P = x
        Polynomial poly_zero({ Rational(Integer("1"), Natural("1")) });//P = 1
        Rational coeff = poly_m.leadingCoefficientNum().DIV_QQ_Q(poly_n.leadingCoefficientNum());
        Polynomial poly_t({ Rational(Integer("0"), Natural("1")) });
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
    vector<Rational> new_coeff;
    for (int i = 0; i < poly.coef.size() - 1; ++i) {
        Rational coeff = poly.coef[i].MUL_QQ_Q(Rational(std::to_string(poly.coef.size() - 1 - i)));
        RED_Q_Q(coeff);
        new_coeff.push_back(coeff);
    }
    return Polynomial(new_coeff);
}
vector<Rational> Polynomial::get_coef() {
    return coef;
}
Polynomial Polynomial::add_polynom(Polynomial poly1, Polynomial poly2, bool minus) {
    std::vector<Rational> new_coef;
    std::vector<Rational> coeff = poly1.coef;
    std::vector<Rational> other_coeff = poly2.coef;

    reverse(other_coeff.begin(), other_coeff.end());
    reverse(coeff.begin(), coeff.end());

    int m = static_cast<int>(std::min(coeff.size(), other_coeff.size()));
    for (int i = 0; i < m; ++i) {
        Rational p;
        if (minus) {
            p = coeff[i].SUB_QQ_Q(other_coeff[i]);
        }
        else {
            p = coeff[i].ADD_QQ_Q(other_coeff[i]);
        }
        new_coef.push_back(p);
    }
    if (coeff.size() > m) {
        for (int i = m; i < coeff.size(); ++i) {
            new_coef.push_back(coeff[i]);
        }
    }
    else {
        for (int i = m; i < other_coeff.size(); ++i) {
            new_coef.push_back(other_coeff[i]);
        }
    }

    reverse(new_coef.begin(), new_coef.end());

    return Polynomial(new_coef);
}

//ÎÊ
Polynomial Polynomial::ost_div_pp(Polynomial poly_n) {
    Polynomial poly_m = (*this);
    Polynomial poly_r = poly_m - poly_n.mul_pol(poly_m.DIV_PP_P(poly_n));
    poly_r.norm_polynom();
    return poly_r;
}

//ÎÊ
//Polynomial Polynomial::nod_polynom(Pol)
// Ñëîæåíèå äâóõ ìíîãî÷ëåíîâ
Polynomial Polynomial::operator+(const Polynomial& other) {
    Polynomial poly = Polynomial::add_polynom(*this, other, false);
    return poly;
}

//ÎÊ
// Âû÷èòàíèå äâóõ ìíîãî÷ëåíîâ
Polynomial Polynomial::operator-(const Polynomial& other) {
    Polynomial poly = add_polynom(*this, other, true);
    return poly;
}



Polynomial Polynomial::operator*(Rational a) const {
    Polynomial result(*this);  // Ñîçäàåì êîïèþ ìíîãî÷ëåíà
    for (Rational& coefficient : result.coef) {
        coefficient = coefficient.MUL_QQ_Q(a);
    }
    return result;
}

// Óìíîæåíèå ìíîãî÷ëåíà íà x^k Îñîáåííîñòè: âîçâðàùàåò íîâûé ïîëèíîì, íå ìåíÿÿ òåêóùèé
Polynomial Polynomial::multiplyByXk(int k) const {
    Polynomial result = *this;
    for (int i = 0; i < k; ++i) {
        result.coef.push_back(Rational(Integer("0"), Natural("1")));
    }
    return result;
}

// Íàõîæäåíèå ñòàðøåãî êîýôôèöèåíòà ìíîãî÷ëåíà
Rational Polynomial::leadingCoefficientNum() {
    return coef[0];
}


// Íàõîæäåíèå ñòåïåíè ìíîãî÷ëåíà
int Polynomial::degree() const {
    int k = 0;
    for (Rational num : coef) {
        if (Natural(num.get_nominator().getValue()).isZero() == 1) {
            k--;
        }
        else {
            break;
        }
    }
    return static_cast<int>(coef.size()) - FREE_TERM + k;
}
/*
Rational Polynomial::calculateLCMandGCD() {
    Natural commonDenominator("1");
    Integer commonNumerator("0");

    for (Rational& term : coef) {
        //commonDenominator = LCM_NN_N(commonDenominator, term.get_denominator());
        commonDenominator = commonDenominator.lcm(term.get_denominator());
        //commonNumerator = GCF_NN_N(commonNumerator, term.get_nominator());
        commonNumerator = commonNumerator.GCF_NN_N(commonNumerator, term.get_nominator());
    }
    Rational b(commonNumerator, commonDenominator);
    return b;
}

void Polynomial::nod_nok() {
    Rational result = calculateLCMandGCD();
    //std::pair<int, int> p = make_pair(result.second, result.first);

   // std::cout << "ÍÎÄ ÷èñëèòåëåé: " << result.first << std::endl;
    //std::cout << "ÍÎÊ çíàìåíàòåëåé: " << result.second << std::endl;
    //std::cout << result.first << "/" << result.second << "*(";
    std::cout << "ÍÎÄ ÷èñëèòåëåé: ";  result.get_nominator().print();
    std::cout << "\nÍÎÊ çíàìåíàòåëåé: "; result.get_denominator().print();
    std::cout << "\n"; result.print(); std::cout << "*(";
    Polynomial help = *this;
    help = help * result;
    help.visual();
    std::cout << ")\n";
}*/


void Polynomial::visual() {
    int deg = static_cast<int>(coef.size()) - FREE_TERM;
    int i = 0;
    for (auto& x : coef) {
        x.print();
        std::cout << "x^" << deg << " ";
        deg--;
    }
}