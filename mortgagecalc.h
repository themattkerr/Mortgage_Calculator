#ifndef MORTGAGECALC_H
#define MORTGAGECALC_H


class MortgageCalc
{
public:
    MortgageCalc();

    void enterPrincipal(int nPrincipal);
    void enterNumOfYears(int nNumOfYears);
    void enterNumOfPayments(int nNumOfPayments);
    void enterInterestRate(double dInterestRate);
    void enterMonthlyPayment(double dMonthlyPayment);

    int getPrincipal();
    int getNumOfYears();
    int getNumOfPayments();
    double getInterestRate();
    double getMonthlyPayment();


private:
    int m_nPrincipal = 0;
    int m_nNumOfYears = 0;
    int m_nNumOfPayments = 0;
    double m_dInterestRate = 0;
    double m_dMonthlyPayment = 0;

    void calcMonthlyPayment();

    void refreshData();


};

#endif // MORTGAGECALC_H
