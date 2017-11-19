#include "mortgagecalc.h"

MortgageCalc::MortgageCalc()
{

}



// ------Privite Calc Functions -----------------------------

void MortgageCalc::calcMonthlyPayment()
{
    if ( m_nPrincipal     > 0 &&
         //m_nNumOfYears    > 0 &&
         m_nNumOfPayments > 0 &&
         m_dInterestRate  > 0 )
    {
      double dTop = 0, dBot = 0, dTemp = 1;
      for(int iii = 1; iii <= m_nNumOfPayments; iii++)
      {
          dTemp = dTemp * (1+m_dInterestRate);
      }
      dTop = m_dInterestRate*dTemp;
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
}

void MortgageCalc::enterNumOfPayments(int nNumOfPayments)
{
    m_nNumOfPayments = nNumOfPayments;
}

void MortgageCalc::enterInterestRate(double dInterestRate)
{
    m_dInterestRate = dInterestRate;
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

double MortgageCalc::getInterestRate()
{
    refreshData();
    return m_dInterestRate;
}

double MortgageCalc::getMonthlyPayment()
{
    refreshData();
    return m_dMonthlyPayment;
}
