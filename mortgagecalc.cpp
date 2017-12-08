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
    if (m_dPrice >= m_dDownPayment)
        m_dPrincipal = m_dPrice - m_dDownPayment;
    else
        m_dPrincipal = 0;
}


 void MortgageCalc::calcDownPaymentDollars()
 {
     if(m_dDownPaymentPercent >= 0 &&
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
    //This is used if a percentage for downpayment is entered
     if(m_nNumOfPayments > 0 &&
       m_dMonthlyInterestRate > 0 &&
       //m_dDownPaymentPercent > 0 &&
       m_dMillRate > 0 &&
       m_bDownpaymentEnteredAsPercent == true)
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
        m_dPrice = (m_dMonthyPayment - m_dOtherMontlyExpenses) /(dBotPart1+dBotPart2);
        if(m_dDownPayment == 0 && m_dDownPaymentPercent ==0)
            m_dPrincipal = m_dPrice;
     }
    //This is used to calculate if an explicite downpaynent amount is entered
    else if(m_nNumOfPayments > 0 &&
       m_dMonthlyInterestRate > 0 &&
       m_dMillRate > 0 &&
       m_bDownpaymentEnteredAsPercent == false)
    {

         double dTop = 0, dBot = 0, dTemp = 1;
         for(int iii = 1; iii <= m_nNumOfPayments; iii++)
         {
             dTemp = dTemp * (1+m_dMonthlyInterestRate);
         }
        dTop = (((m_dMonthyPayment-m_dOtherMontlyExpenses)*(dTemp-1))/(m_dMonthlyInterestRate * dTemp)) + m_dDownPayment ;
        dBot = 1 + (((m_dMillRate*dMillRateMultiplier)*(dTemp - 1))/( nNumberOfMonthsInAYear * m_dMonthlyInterestRate * dTemp)) ;
        m_dPrice = dTop/dBot;


         if(m_dDownPayment == 0 )
            m_dPrincipal = m_dPrice;
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

void MortgageCalc::enterOtherMonthlyExpenses(double dOtherMontlyExpenses)
{
    m_dOtherMontlyExpenses = dOtherMontlyExpenses;
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
    return m_dMonthyLoanPaymentPandI + m_dMonthlyTaxPayment + m_dOtherMontlyExpenses;
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

double MortgageCalc::getPrincipalAndInterestMontlyPayment()
{
    return m_dMonthyLoanPaymentPandI;
}

bool MortgageCalc::getDownPaymentCalcFromPercent()
{
   return m_bDownpaymentEnteredAsPercent;
}
double MortgageCalc::getOtherMontlyExpenses()
{
    return m_dOtherMontlyExpenses;
}

QString MortgageCalc::getAmortizationSchedule()
{
    int nTempUnused = 0;
    return getAmortizationSchedule(nTempUnused, nTempUnused);
}

QString MortgageCalc::getAmortizationSchedule(double dRegularExtraPayment)
{
    QString strTemp;
    int nTempUnused = 0;
    double dTempUnused = 0;

    return getAmortizationSchedule(nTempUnused, dTempUnused, dRegularExtraPayment, strTemp );
}

QString MortgageCalc::getAmortizationSchedule(int nInsertPaymentNum, double dAmount)
{
    QString strTemp;
    return getAmortizationSchedule(nInsertPaymentNum, dAmount, strTemp );
}

QString MortgageCalc::getAmortizationSchedule(int nInsertPaymentNum, double dAmount, QString &strAnualReport)
{
    double dTempRegularExtraPayment = 0;
    return getAmortizationSchedule(nInsertPaymentNum, dAmount, dTempRegularExtraPayment, strAnualReport);
}

QString MortgageCalc::getAmortizationSchedule(int nInsertPaymentNum, double dAmount, double dRegularExtraPayment, QString &strAnualReport )
{
    QString strSpace = " --- "; strSpace.append("\t");
    QString strReportOutput = "";
        strReportOutput.append("Payment").append(strSpace)
                .append("Remaining").append(strSpace)
                .append("Principal").append(strSpace)
                .append("Interest")
                .append("\n");

    //QString strAnualReport = "";
    int    nYearNum = 1;
    double dCurrentPrincipal = m_dPrincipal;
    double dCurrentIntrestPayment = 0;
    double dCurrentPrincipalPayment = 0;
    double dAnualInterestPayed = 0;
    double dAnualPrincipalPayed = 0;



    for(int nPaymentNum = 1; nPaymentNum <= m_nNumOfPayments; nPaymentNum++)
    {
        strReportOutput.append(QString::number(nPaymentNum)).append(strSpace).append(strSpace);
        dCurrentIntrestPayment = dCurrentPrincipal * m_dMonthlyInterestRate;
        dCurrentPrincipal = dCurrentPrincipal + dCurrentIntrestPayment;
        dCurrentPrincipalPayment =  m_dMonthyLoanPaymentPandI - dCurrentIntrestPayment;

        if( nPaymentNum == nInsertPaymentNum )
        {
            dCurrentPrincipal = dCurrentPrincipal - dAmount;

        }

        if( dCurrentIntrestPayment < 0 )
            dCurrentIntrestPayment = 0;
        if( dCurrentPrincipal < 0 )
        {
            dCurrentPrincipal = 0;
            dCurrentPrincipalPayment = 0;
        }
        if( dCurrentPrincipalPayment < 0  )
            dCurrentPrincipalPayment = 0;
        if( dCurrentPrincipalPayment > dCurrentPrincipal)
        {
            dCurrentPrincipalPayment = dCurrentPrincipal - dCurrentIntrestPayment;
        }
        dAnualInterestPayed = dAnualInterestPayed + dCurrentIntrestPayment;
        dAnualPrincipalPayed= dAnualPrincipalPayed+ dCurrentPrincipalPayment;

        strReportOutput.append( doubleToCurrency (dCurrentPrincipal, 2, US_DOLLARS) );
        if (dCurrentPrincipal > 0)
            strReportOutput.append(strSpace)
                       .append( doubleToCurrency (dCurrentPrincipalPayment, 2, US_DOLLARS) ).append(strSpace)
                       .append( doubleToCurrency (dCurrentIntrestPayment, 2, US_DOLLARS) );
         if( nPaymentNum == nInsertPaymentNum && dAmount > 0 )
         {
            dAnualPrincipalPayed = dAnualPrincipalPayed + dAmount;
             strReportOutput.append("\t   <---------Extra Payment:  \t").append( doubleToCurrency (dAmount,2,US_DOLLARS )  );
         }
        strReportOutput.append("\n");
        //Anual report
         if (!(nPaymentNum % nNumberOfMonthsInAYear ))
         {
             strAnualReport.clear(); // <------------------------------------This needs to go if you want an actual anual report
             strAnualReport.append( drawLine() ).append("\n");
             strAnualReport.append("Year: ").append(QString::number(nYearNum)).append(strSpace);
             strAnualReport.append("Principal Payed: ").append( doubleToCurrency (dAnualPrincipalPayed, 0, US_DOLLARS) ).append(strSpace);
             strAnualReport.append("Interest Payed: ").append( doubleToCurrency(dAnualInterestPayed, 0, US_DOLLARS ) );
             strAnualReport.append("\n");
             strAnualReport.append( drawLine() ).append("\n");

             dAnualInterestPayed = 0;
             dAnualPrincipalPayed = 0;
             strReportOutput.append(strAnualReport);
             nYearNum++;
         }

         dCurrentPrincipal = dCurrentPrincipal - m_dMonthyLoanPaymentPandI;

    }
    return strReportOutput;

}
