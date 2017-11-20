#include "mortgagecalc.h"

MortgageCalc::MortgageCalc()
{

}



// ------Privite Calc Functions -----------------------------

void MortgageCalc::calcMonthlyPayment()
{
    if ( m_nPrincipal          > 0 &&
         //m_nNumOfYears    > 0 &&
         m_nNumOfPayments      > 0 &&
         m_dAnualInterestRate  > 0 &&
         m_dMonthlyInterestRate> 0 )
    {
      double dTop = 0, dBot = 0, dTemp = 1;
      for(int iii = 1; iii <= m_nNumOfPayments; iii++)
      {
          dTemp = dTemp * (1+m_dMonthlyInterestRate);
      }
      dTop = m_dMonthlyInterestRate * dTemp;
      dBot = dTemp - 1;
      m_dMonthlyPayment = m_nPrincipal*(dTop/dBot);
    }
    else
    {
        m_dMonthlyPayment = 0;
    }
    return;
}

void MortgageCalc::refreshData()
{
    calcMonthlyPayment();
}



// ------Public Enter Functions ------------------------------

void MortgageCalc::enterPrincipal(int nPrincipal)
{
    m_nPrincipal = nPrincipal;
}

void MortgageCalc::enterNumOfYears(int nNumOfYears)
{
    m_nNumOfYears = nNumOfYears;
    m_nNumOfPayments = roundDoubleToPoints( (nNumOfYears * nNumberOfMonthsInAYear) ,0);
    //refreshData();
}

void MortgageCalc::enterNumOfPayments(int nNumOfPayments)
{
    if(nNumOfPayments >= 0)
    {
        m_nNumOfPayments = nNumOfPayments;
        m_nNumOfYears = roundDoubleToPoints((nNumOfPayments/nNumberOfMonthsInAYear ),0 );
    }
    else
    {
        m_nNumOfPayments = 0;
        m_nNumOfYears = 0;
    }
    //refreshData();
}

void MortgageCalc::enterAnualInterestRate(double dAnualInterestRate)
{
    m_dAnualInterestRate = dAnualInterestRate;
    m_dMonthlyInterestRate = dAnualInterestRate / nNumberOfMonthsInAYear;

}

 void MortgageCalc::enterMonthlyInterestRate(double dMontlyInterestRate)
 {
     m_dAnualInterestRate = dMontlyInterestRate * nNumberOfMonthsInAYear;
     m_dMonthlyInterestRate = dMontlyInterestRate;
 }

void MortgageCalc::enterMonthlyPayment(double dMonthlyPayment)
{
    m_dMonthlyPayment = dMonthlyPayment;
}



// ------Public Get Functions --------------------------------

int MortgageCalc::getPrincipal()
{
    refreshData();
    return m_nPrincipal;
}

int MortgageCalc::getNumOfYears()
{
    refreshData();
    return m_nNumOfYears;
}

int MortgageCalc::getNumOfPayments()
{
    refreshData();
    return m_nNumOfPayments;
}

double MortgageCalc::getAnualInterestRate()
{
    refreshData();
    return m_dAnualInterestRate;
}

double MortgageCalc::getMonthlyPayment()
{
    refreshData();
    return m_dMonthlyPayment;
}

double MortgageCalc::getInterestPaid()
{
    refreshData();
    double dTemp = (m_dMonthlyPayment*m_nNumOfPayments ) - m_nPrincipal;
    if (dTemp < 0)
        return 0;
    return dTemp;
}
