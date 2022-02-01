#include <iostream>
#include <map>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>
#include <clocale>
using namespace std;

//Коваленко Дарья
void a_pay_sum(double payment, double interest_rate, int month) { //аннуитетный
    double a = (100 + interest_rate) / 100, x = payment / month, s, an;
    an = pow(a, month);
    s = (x / an) * ((an - 1) / (a - 1));
    cout  << "Вы можете взять кредит размером " << fixed << setprecision(3) << s << " при погашении аннуитетными платежами\n";
}
//Коваленко Дарья
void d_pay_sum(double payment, double interest_rate, int month) { //дифференцированный
    double r = interest_rate / 100, s;
    s = payment / (1 + r * ((1 + month) / 2));
    cout << "Вы можете взять кредит размером " << fixed << setprecision(3) << s << " при погашении дифференцированными платежами\n";
}
//Коваленко Дарья
void insurance(int n) {
    int a;
    double s = 0, b;
    for (int i = 0; i < n; i++) {
        cout << "период: ";
        cin >> a;
        cout << "стоимость: ";
        cin >> b;
        s += a * b;
    }
    cout << "Сумма всех выплат по страховкам равна " << fixed << setprecision(3) << s;
}
//Степанычев Артём
void diff_credit_scheme(double loan_amount, double percent, int number_of_months) {
    map <double, double> payment_schedule;
    cout << "\nСхема выплат дифференцированных платежей\n";
    cout << "Месяц" << "   " << "Выплата" << endl;
    double fix = loan_amount / number_of_months;
    for (double i = 0; i < number_of_months; i++) {
        double n = number_of_months - i, razn = (percent / 100) * loan_amount * (n / number_of_months);
        payment_schedule[i + 1] = fix + razn;
    }
    for (auto& now : payment_schedule) {
        cout << fixed << setprecision(3) << setw(5) << int(now.first) << "   " << now.second << endl;
    }
}
//Степанычев Артём
double ann_credit_pay(double loan_amount, double percent, int number_of_months) {
    map <int, double> payment_schedule;
    cout << fixed;
    double x, sum_p = 0, interest_rate;
    interest_rate = 1 + (percent / 100);
    for (int i = 0; i < number_of_months; i++)
        sum_p += pow(interest_rate, i);
    x = (loan_amount * pow(interest_rate, number_of_months)) / sum_p;
    return x;
}
//Степанычев Артем
vector <double> diff_credit_info(double loan_amount, double percent, int number_of_months, double additional_amount) {
    double sum = 0, fix = loan_amount / number_of_months, p = 1 + (percent / 100);
    for (int i = 0; i < number_of_months; i++) {
        double n = number_of_months - i, razn = (percent / 100) * loan_amount * (n / number_of_months);
        sum += fix + razn;
    }
    double sum_1 = 0;
    double s = loan_amount;
    if (additional_amount == 0)
        return { sum, 0 };
    else {
        double sum_1 = 0;
        for (int i = 0; i < number_of_months; i++) {
            double credit = loan_amount;
            double k = number_of_months - i, payment = (percent / 100) * loan_amount * (k / number_of_months) + additional_amount + fix;
            loan_amount -= payment;
            loan_amount *= p;
            if (loan_amount < 0) {
                sum_1 += credit;
                break;
            }
            sum_1 += payment;
        }
        double r = sum - sum_1;
        return {sum, sum_1 };
    }
}
//Пашинская Пелагея
void deposit_info(double sum, double p, int numb_of_month, double change_sum = 0, int change_month = 0) {
    double percent = 1 + (p / 100.0);
    //printf("Вклад за %d месяцев принесет прибыль, равную %.3f\n", numb_of_month, deposit2 - sum);
    cout << "Вклад за " << numb_of_month << " месяцев принесет прибыль, равную " << fixed << setprecision(3) << pow(percent, numb_of_month)*sum<< endl;
    string sl = (change_sum > 0) ? "увеличится на " : "уменьшится на ", sl1 = (change_sum > 0) ? "добавить " : "забрать ";
    cout << "Прибыль по вкладу " << sl << fixed << setprecision(3) << abs(change_sum)*pow(percent, numb_of_month-change_month+1) << ", если на " << change_month << " месяце " << sl1 << fixed << setprecision(3) << abs(change_sum);
    //printf("Прибыль по вкладу увеличится на %.3f, если на %d месяце добавить %.3f рублей\n", fabs(deposit2 - deposit1), change_month, abs(change_sum));
}
//Пашинская Пелагея
vector <double> ann_credit_info(double loan_amount, double percent, int number_of_months, double additional_amount) {
    double main_pay = ann_credit_pay(loan_amount, percent, number_of_months);
    double pay2 = main_pay + additional_amount;
    double sum1 = number_of_months * main_pay;
    double p = 1 + (percent / 100);
    int k = 0;
    while (loan_amount - pay2 > 0) {
        loan_amount *= p;
        loan_amount -= pay2;
        k += 1;
    } return { sum1, k * pay2 + loan_amount};
}
//Пашинская Пелагея
int main() {
    setlocale(LC_ALL, "ru");
    int n, cn, ks;
    double s, p, cs, ads;
    cout << "ВВЕДИТЕ\n сумма (кредита, вклада или страхового взноса) \n процент\n количество периодов\n доп. сумма для платежей (уменьшить - отрицательное, не менять - 0)\n сколько добавить к начальной сумме (уменьшить - отрицательное, не менять - 0)\n на каком месяце добавить\n колво страховых периодов (если расчет вклада/кредита - 0) " << endl;
    cin >> s >> p >> n >> ads >> cs >> cn >> ks;
    cout << "КРЕДИТ" << endl;

    cout << "Ваш ежемесячный аннуитетный платеж по кредиту равен " << fixed << setprecision(3) << ann_credit_pay(s, p, n),
    cout << endl;

    diff_credit_scheme(s, p, n);
    cout << endl;

    vector <double> ved = diff_credit_info(s, p, n, ads);
    string s1 = ads > 0 ? "увеличении" : "уменьшении";
    string s2 = (ads > 0) ? " меньше" : " больше";
    //printf("По обычной схеме дифференцированными платежами вы выплатите %.3f\nПри %s платежей на %.3f вы выплатите на %.3f %s \n\n", ved[0], ads > 0 ? "увеличении" : "уменьшении", abs(ads), abs(ved[0] - ved[1]), ads > 0 ? "меньше" : "больше");
    cout << "По обычной схеме дифференцированными платежами вы выплатите " << fixed << setprecision(3) << ved[0] << "\nПри " << s1 << " платежей на " << fixed << setprecision(3) << abs(ads) << " вы выплатите на " << fixed << setprecision(3) << abs(ved[0] - ved[1]) << s2 << endl << endl;

    vector <double> vea = ann_credit_info(s, p, n, ads);
    //printf("По обычной схеме аннуитетными платежами вы выплатите %.3f\nПри %s платежей на %.3f вы выплатите на %.3f %s \n\n", vea[0], ads > 0 ? "увеличении" : "уменьшении", abs(ads), abs(vea[0] - vea[1]), ads > 0 ? "меньше" : "больше");
    cout << "По обычной схеме аннуитетными платежами вы выплатите " << fixed << setprecision(3) << vea[0] << "\nПри " << s1 << " платежей на " << fixed << setprecision(3) << abs(ads) << " вы выплатите на " << fixed << setprecision(3) << abs(vea[0] - vea[1]) << s2 << endl << endl;

    
    a_pay_sum(s, p, n);
    d_pay_sum(s, p, n);


    cout << endl << "ВКЛАД" << endl;
    deposit_info(s, p, n, cs, cn);
    cout << endl;

    cout << "СТРАХОВКИ\n";
    insurance(ks);
}




