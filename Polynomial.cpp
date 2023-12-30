#include "Polynomial.h"

#include <set>

#define FREE_TERM 1
//#define int long long
using namespace std;

//�������� �� ������������� ����
bool Polynomial::poly_empty() {
    Polynomial poly = (*this);
    vector<std::string> zero{ "0", "+0", "-0" };
    return poly.coef.size() == 1 && std::count(zero.begin(), zero.end(), poly.coef[0].get_nominator().getValue());//
}

//����������� ������������ ����������
Polynomial::Polynomial(vector<Rational> coefficients) {//
    if (coefficients.size() < 1) {
        std::cout << "Not a polynom!";
        exit(0);
    }
    else {
        coef = coefficients;
    }
}

//������ ���������� ������������
void Polynomial::norm_polynom() {
    vector<Rational> coeff_this = (*this).coef;//
    reverse(coeff_this.begin(), coeff_this.end());
    while (coeff_this.size() > 1 && coeff_this.back().get_nominator().POZ_Z_D() == 0) {//
        coeff_this.pop_back();
    }
    reverse(coeff_this.begin(), coeff_this.end());
    (*this).coef = coeff_this;
}

//��������� �����������
Polynomial Polynomial::MUL_PP_P(Polynomial poly1) {
    Polynomial poly2 = *this;
    vector<Rational> coeff = poly1.coef;//
    vector<Rational> other_coeff = poly2.coef;//
    reverse(other_coeff.begin(), other_coeff.end());
    reverse(coeff.begin(), coeff.end());
    vector<Rational> new_coeff = { Rational(Integer("0"),Natural("1")) };
    Polynomial poly_result(new_coeff);
    for (int i = 0; i < coeff.size(); ++i) {
        poly_result = poly_result + poly2.MUL_Pxk_P(i) * coeff[i];
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
    while (!poly_m.poly_empty() && poly_m.DEG_P_N() >= poly_n.DEG_P_N()) {
        Polynomial poly_x({ Rational(Integer("1"), Natural("1")), Rational(Integer("0"), Natural("1")) });//P = x
        Polynomial poly_zero({ Rational(Integer("1"), Natural("1")) });//P = 1
        Rational coeff = poly_m.LED_P_Q().DIV_QQ_Q(poly_n.LED_P_Q());
        Polynomial poly_t({ Rational(Integer("0"), Natural("1")) });
        if (poly_m.DEG_P_N() != poly_n.DEG_P_N()) {
            poly_t = poly_x.MUL_Pxk_P(poly_m.DEG_P_N() - poly_n.DEG_P_N() - 1) * coeff;
        }
        else {
            poly_t = poly_zero * coeff;
        }
        poly_t.norm_polynom();
        //cout << "poly_t " << poly_t.visual() << "\n";

        poly_q = poly_q + poly_t;//+
        poly_q.norm_polynom();
        poly_r = poly_m - poly_n.MUL_PP_P(poly_t);//+
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

Polynomial::Polynomial(const std::string& poly) {
    Polynomial res;
    std::string temp = poly;
    temp.erase(std::remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
    std::stringstream stream(temp);
    std::string tmp;
    while (getline(stream, tmp, '+')) {
        size_t xid = tmp.find('x');
        if (xid == std::string::npos) {
            //res.get_coef().push_back(Rational(tmp));
            //res = res + Rational(tmp);
            //res.get_coef().back() = Rational(tmp);
            Polynomial h(Rational(tmp), 0);
            res = res + h;
            continue;
        }
        std::string left = tmp.substr(0, xid != 0 && tmp[xid - 1] == '*' ? xid - 1 : xid);
        Rational coef = Rational(!left.empty() ? left : "1");
        if (xid + 2 >= tmp.size()) {
            res = res + Polynomial(coef, 1);
            continue;
        }
        std::string right = tmp.substr(xid + 2, tmp.size() - xid - 2);
        std::stringstream sstream(right);
        size_t degre;
        sstream >> degre;
        res = res + Polynomial(coef, degre);
    }
    *this = res;
}

Polynomial::Polynomial() : Polynomial({ Rational("0") }) {}


Polynomial::Polynomial(const Rational& num, size_t deg) {
    coef.push_back(num);
    while (coef.size() <= deg)
        coef.push_back(Rational("0"));
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
    Polynomial poly_ans(new_coef);
    poly_ans.norm_polynom();
    return poly_ans;
}

//��
Polynomial Polynomial::MOD_PP_P(Polynomial poly_n) {
    Polynomial poly_m = (*this);
    Polynomial poly_r = poly_m - poly_n.MUL_PP_P(poly_m.DIV_PP_P(poly_n));
    poly_r.norm_polynom();
    return poly_r;
}
//  P = N*Q + R
// R = P - N*Q
//��
//Polynomial Polynomial::nod_polynom(Pol)
// �������� ���� �����������
Polynomial Polynomial::operator+(const Polynomial& other) {
    Polynomial poly = Polynomial::add_polynom(*this, other, false);
    poly.norm_polynom();
    return poly;
}

//��
// ��������� ���� �����������
Polynomial Polynomial::operator-(const Polynomial& other) {
    Polynomial poly = add_polynom(*this, other, true);
    poly.norm_polynom();
    return poly;
}

Polynomial Polynomial::operator*(Rational a) const {
    Polynomial result(*this);  // ������� ����� ����������
    for (Rational& coefficient : result.coef) {
        coefficient = coefficient.MUL_QQ_Q(a);
    }
    result.norm_polynom();
    return result;
}

// ��������� ���������� �� x^k �����������: ���������� ����� �������, �� ����� �������
Polynomial Polynomial::MUL_Pxk_P(int k) const {
    Polynomial result = *this;
    for (int i = 0; i < k; ++i) {
        result.coef.push_back(Rational(Integer("0"), Natural("1")));
    }
    return result;
}

// ���������� �������� ������������ ����������
Rational Polynomial::LED_P_Q() {
    return coef[0];
}


// ���������� ������� ����������
int Polynomial::DEG_P_N() const {
    int k = 0;
    for (Rational num : coef) {
        if (num.is_zero()) {
            k--;
        }
        else {
            break;
        }
    }
    return static_cast<int>(coef.size()) - FREE_TERM + k;
}
Polynomial Polynomial::nod_polynom(Polynomial poly_m, Polynomial poly_n) {
    if (poly_m.poly_empty()) {
        //cout << "poly_m = " << poly_m.visual() << "\n";
        return poly_n;
    }
    else if (poly_n.poly_empty()) {
        //cout << "poly_m = " << poly_m.visual() << "\n";
        //cout << "poly_n = " << poly_n.visual() << "\n";
        return poly_m;
    }
    return nod_polynom(poly_n, poly_n.MOD_PP_P(poly_m));
}
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

    //std::cout << "��� ����������: " << result.first << std::endl;
    //std::cout << "��� ������������: " << result.second << std::endl;
    //std::cout << result.first << "/" << result.second << "*(";
    std::cout << "NODE of numerators: ";  result.get_nominator().print();
    std::cout << "\nNOK of denominators: "; result.get_denominator().print();
    std::cout << "\n"; result.print(); std::cout << "*(";
    Polynomial help = *this;
    //help = help * result;
    Rational one("1");
    help = help * (one.DIV_QQ_Q(result));
    help.visual();
    std::cout << ")\n";
}

Polynomial Polynomial::NMR_P_P() {
    Polynomial poly = *this;
    return poly.DIV_PP_P(poly.nod_polynom(poly.DER_P_P(), poly));
}

void Polynomial::visual() {
    int deg = static_cast<int>(coef.size()) - FREE_TERM;
    int i = 0;
    for (auto& x : coef) {
        if (x.is_zero()) {
            deg--;
            continue;
        }
        x.print();
        if (deg != 0) {
            std::cout << "x^" << deg << " ";
            std::cout << "+";
        }
        deg--;
    }
    std::cout << "\n";
}





