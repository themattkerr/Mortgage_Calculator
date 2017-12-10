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

    void enterAnualTax(double dAnualTax);
    void enterDownPaymentPercent(double dDownPaymentPercent);
    void enterDownPaymentDollars(double dDownPaymentDollars);

    void enterPrice(double dPrice);
    void enterMillRate(double dMillRate);
    void enterOtherMonthlyExpenses(double dOtherMontlyExpenses);

    void setDownPaymentCalcFromPercent(bool bCalcFromPercent);
    void setCalcFromMonthlyPayment(bool b_LockMontlyPayment);




    double getPrincipal();
    int getNumOfYears();
    int getNumOfPayments();
    double getAnualInterestRate();
    double getMonthlyPayment();
    double getInterestPaid();

    double getPrice();
    double getMillRate();
    double getDownPaymentDollars();
    double getDownPaymentPercent();

    double getMonthlyTaxPayment();
    double getPrincipalAndInterestMontlyPayment();
    double getOtherMontlyExpenses();
    double getAnnualTaxesAndExpenses();
    double getLifeOfLoanTaxesAndExpenses();

    bool getDownPaymentCalcFromPercent();  
    bool getCalcFromMontlyPayment();

    QString getAmortizationSchedule(int nInsertPaymentNum, double dAmount, int nStartExtraPayments, double dRegularExtraPayment, int nStopExtraPayments,int nPaymentOffset, QString &strAnualReport, double &dTotalInterestPaid);
    QString getAmortizationSchedule(int nInsertPaymentNum, double dAmount, QString &strAnualReport);
    QString getAmortizationSchedule(int nInsertPaymentNum, double dAmount);
    QString getAmortizationSchedule(int nStartExtraPayments, double dRegularExtraPayment, int nStopExtraPayments, int nPaymentOffset);
    QString getAmortizationSchedule();

    void resetDefaults();

private:
    int const nNumberOfMonthsInAYear = 12;
    double const dMillRateMultiplier = .001;
    double m_dMillRate = 23.9718;

    double m_dPrincipal = 0;
    int m_nNumOfYears = 0;
    int m_nNumOfPayments = 0;

    double m_dAnualInterestRate = 0;
    double m_dMonthlyInterestRate = 0;
    double m_dMonthyLoanPaymentPandI = 0;
    double m_dMonthyPayment = 0;
    bool m_bCalcFromMonthlyPayment = false;

    double m_dPrice = 0;

    double m_dDownPayment = 0;
    double m_dDownPaymentPercent =0;
    bool m_bDownpaymentEnteredAsPercent = false;

    double m_dMonthlyTaxPayment = 0;
    double m_dOtherMontlyExpenses = 0;

    void calcMonthlyLoanPaymentPandI();
    void calcPrincipalFromMonthlyPandI();
    void calcPrincipalFromPriceAndDownPayment();

    void calcDownPaymentPercent();
    void calcDownPaymentDollars();

    void calcPriceFromMontlyPayment();
    void calcMontlyTax();
    void calcMillRate();


    void refreshData();


};

#endif // MORTGAGECALC_H
