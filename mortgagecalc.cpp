#include "mortgagecalc.h"

MortgageCalc::MortgageCalc()
{

}



// ------Privite Calc Functions -----------------------------

void MortgageCalc::calcMonthlyLoanPaymentPandI()
{
    if ( m_dPrincipal          > 0 &&
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
      m_dMonthyLoanPaymentPandI = m_dPrincipal*(dTop/dBot);
    }
    else
    {
        m_dMonthyLoanPaymentPandI = 0;
    }
    return;
}

void MortgageCalc::calcPrincipalFromMonthlyPandI()
{
    if ( m_dMonthyLoanPaymentPandI     > 0 &&
         m_nNumOfPayments      > 0 &&
         m_dAnualInterestRate  > 0 &&
         m_dMonthlyInterestRate> 0 )
    {
      double dTop = 0, dBot = 0, dTemp = 1;
      for(int iii = 1; iii <= m_nNumOfPayments; iii++)
      {
          dTemp = dTemp * (1+m_dMonthlyInterestRate);
      }
      dBot = m_dMonthlyInterestRate * dTemp;
      dTop = dTemp - 1;
      m_dPrincipal  = m_dMonthyLoanPaymentPandI *(dTop/dBot);
    }
    else
    {
        m_dPrincipal = 0;
    }
    return;
}

void MortgageCalc::calcPrincipalFromPriceAndDownPayment()
{
    if (m_dPrice > m_dDownPayment)
        m_dPrincipal = m_dPrice - m_dDownPayment;
    else
        m_dPrincipal = 0;
}


 void MortgageCalc::calcDownPaymentDollars()
 {
     if(m_dDownPaymentPercent > 0 &&
        m_dPrice > 0     )
     {
         m_dDownPayment = m_dPrice * m_dDownPaymentPercent;
     }

     else
         m_dDownPayment = 0;
 }

 void MortgageCalc::calcDownPaymentPercent()
 {
     if(m_dPrice >0 && m_dDownPayment >0)
        m_dDownPaymentPercent = m_dDownPayment / m_dPrice;
     else
         m_dDownPaymentPercent =0;
 }

 void MortgageCalc::calcPriceFromMontlyPayment()
 {
    if(m_nNumOfPayments > 0 &&
       m_dMonthlyInterestRate > 0 &&
       //m_dDownPaymentPercent > 0 &&
       m_dMillRate > 0 )
    {
        double dBotPart1 = 0, dBotPart2 = 0;
        double dTop = 0, dBot = 0, dTemp = 1;
        for(int iii = 1; iii <= m_nNumOfPayments; iii++)
        {
            dTemp = dTemp * (1+m_dMonthlyInterestRate);
        }
        dTop = (1-m_dDownPaymentPercent)*m_dMonthlyInterestRate*dTemp;
        dBot = dTemp - 1;
        dBotPart1 = dTop/dBot;
        dBotPart2 = m_dMillRate*dMillRateMultiplier/nNumberOfMonthsInAYear;
        m_dPrice = m_dMonthyPayment/(dBotPart1+dBotPart2);
     }
    else
    {
        m_dPrice = 0;
    }
 }

void MortgageCalc::calcMontlyTax()
{
    if( m_dPrice > 0 && m_dMillRate > 0   )
        m_dMonthlyTaxPayment = m_dPrice * ((m_dMillRate * dMillRateMultiplier)/nNumberOfMonthsInAYear);
    else
        m_dMonthlyTaxPayment = 0;
}

void MortgageCalc::refreshData()
{
    if (m_bDownpaymentEnteredAsPercent)
        calcDownPaymentDollars();
    else
        calcDownPaymentPercent();

    if (m_dPrice > 0 && m_dDownPayment > 0 && m_bDownpaymentEnteredAsPercent == false)
    { m_dPrincipal = m_dPrice - m_dDownPayment; }
    if (m_dPrice > 0 && m_dDownPaymentPercent > 0 && m_bDownpaymentEnteredAsPercent == true)
    { m_dPrincipal =  roundDoubleToPoints( m_dPrice - (m_dPrice * m_dDownPaymentPercent),0) ; }


    calcMonthlyLoanPaymentPandI();
    calcMontlyTax();
}



// ------Public Enter Functions ------------------------------

void MortgageCalc::enterDownPaymentDollars(double dDownPaymentDollars)
{
    //m_bDownpaymentEnteredAsPercent = false;
    m_dDownPayment = dDownPaymentDollars;
    //calcDownPaymentPercent();
    refreshData();
}

 void MortgageCalc::enterDownPaymentPercent(double dDownPaymentPercent)
 {
    //m_bDownpaymentEnteredAsPercent = true;
    m_dDownPaymentPercent = dDownPaymentPercent;
    //calcDownPaymentDollars();
    refreshData();

 }

void MortgageCalc::enterPrincipal(int nPrincipal)
{
    m_dPrincipal = nPrincipal;
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
    m_dMonthyPayment = dMonthlyPayment;
    //calcPrincipalFromPriceAndDownPayment();
    calcPriceFromMontlyPayment();
    refreshData();
}

void MortgageCalc::enterPrice(double dPrice)
{
    m_dPrice = dPrice;
    refreshData();
}

void MortgageCalc::enterMillRate(double dMillRate)
{
    m_dMillRate = dMillRate;
    refreshData();
}

void MortgageCalc::setDownPaymentCalcFromPercent(bool bCalcFromPercent)
{
    m_bDownpaymentEnteredAsPercent = bCalcFromPercent;
    refreshData();
}


// ------Public Get Functions --------------------------------

double MortgageCalc::getPrincipal()
{
    refreshData();
    return m_dPrincipal;
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
    return m_dMonthyLoanPaymentPandI + m_dMonthlyTaxPayment;
}

double MortgageCalc::getInterestPaid()
{
    refreshData();
    double dTemp = (m_dMonthyLoanPaymentPandI*m_nNumOfPayments ) - m_dPrincipal;
    if (dTemp < 0)
        return 0;
    return dTemp;
}
double MortgageCalc::getPrice()
{
    refreshData();
    return m_dPrice;
}

double MortgageCalc::getMillRate()
{
      return m_dMillRate;
}

double MortgageCalc::getDownPaymentDollars()
{
    refreshData();
    return m_dDownPayment;
}

double MortgageCalc::getDownPaymentPercent()
{
    refreshData();
    return m_dDownPaymentPercent;
}

double MortgageCalc::getMonthlyTaxPayment()
{
    return m_dMonthlyTaxPayment;
}
