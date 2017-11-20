#ifndef MORTGAGECALC_H
#define MORTGAGECALC_H

#include "mattcalculations.h"

class MortgageCalc
{
public:
    MortgageCalc();

    void enterPrincipal(int nPrincipal);
    void enterNumOfYears(int nNumOfYears);
    void enterNumOfPayments(int nNumOfPayments);
    void enterAnualInterestRate(double dAnualInterestRate);
    void enterMonthlyInterestRate(double dMontlyInterestRate);
    void enterMonthlyPayment(double dMonthlyPayment);

    int getPrincipal();
    int getNumOfYears();
    int getNumOfPayments();
    double getAnualInterestRate();
    double getMonthlyPayment();
    double getInterestPaid();


private:
    int const nNumberOfMonthsInAYear = 12;
    int m_nPrincipal = 0;
    int m_nNumOfYears = 0;
    int m_nNumOfPayments = 0;
    double m_dAnualInterestRate = 0;
    double m_dMonthlyInterestRate = 0;
    double m_dMonthlyPayment = 0;

    void calcMonthlyPayment();


    void refreshData();


};

#endif // MORTGAGECALC_H
