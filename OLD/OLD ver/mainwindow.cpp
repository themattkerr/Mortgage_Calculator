#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    Qt::WindowFlags flags = this->windowFlags();
//    this->setWindowFlags(flags|Qt::WindowStaysOnTopHint);

    m_cMontlyCosts = new CalculateOtherMonthlyExpensesDialog(this, &m_dCalculatedMonthlyExpenses);
    refreshFields();
    ui->doubleSpinBoxMillRate->setValue(m_Mort.getMillRate());
    adjustSize();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_cMontlyCosts;
}

void MainWindow::refreshFields()
{
    //m_Mort.enterOtherMonthlyExpenses(m_dCalculatedMonthlyExpenses);

    if(bShowTitleBlock)
        ui->lineEdit_TitleBlock->show();
    else
        ui->lineEdit_TitleBlock->hide();
    if(bShowMortgageTerms)
        showMortgageTerms();
    else
        hideMortgageTerms();
    if(bShowPaymentStatistics)
        showPaymentStatistics();
    else
        hidePaymentStatistics();

    ui->AmountofInterest->setText( doubleToCurrency (m_Mort.getInterestPaid(), 0, US_DOLLARS)    );

    ui->labelMontlyTax->setText( doubleToCurrency (m_Mort.getMonthlyTaxPayment(), 2, US_DOLLARS ) );
    ui->labelPrincipalAndInterest->setText( doubleToCurrency(m_Mort.getPrincipalAndInterestMontlyPayment() , 2, US_DOLLARS  )  ); //<-----------------------------

    ui->lineEditOtherMonthly->setText( doubleToCurrency( m_Mort.getOtherMontlyExpenses() , 2, US_DOLLARS)  );
    ui->labelAnualCostsAndTaxes->setText( doubleToCurrency( (12*m_Mort.getOtherMontlyExpenses()), 0, US_DOLLARS) );
    //trying out to see if just having annual other costs is ok.
    //ui->labelAnualCostsAndTaxes->setText( doubleToCurrency( m_Mort.getAnnualTaxesAndExpenses(), 0, US_DOLLARS) );

    ui->labelLifeOfLoanTaxAndExpenses->hide();
    ui->label_LifeOfLoanTitle->hide();

    int const n_NumberOfMonthsInAYear = 12;
    ui->labelAnnualTax->setText(doubleToCurrency((m_Mort.getMonthlyTaxPayment()*n_NumberOfMonthsInAYear), 0, US_DOLLARS));

    setupCalcFromPercentGUI(); // The next three functions need to be excuted in this order.  I believe this is due to the later calcultaions of setupCalcFromPercentGUI()
    setupCalcFromMonthlyPaymentGUI();
    setupAmortizationTableAndExtraPaymentsGUI();

    //Save this for another day - Too confusing
    //ui->labelLifeOfLoanTaxAndExpenses->setText( doubleToCurrency ( m_Mort.getLifeOfLoanTaxesAndExpenses(),0, US_DOLLARS));
    if(bShowPaymentStatistics)
        refreshPayStats();
}

void MainWindow::refreshPayStats()
{
    setMaxMinForPayStats();
    //Calc Interst and pricipal paid  InputPayments, &dCalcPricipal, &dCalcInterest, &nPaymentNumOfPayOff
    //PaintPayStatsfields();



}

void MainWindow::setMaxMinForPayStats()
{
    int nMaxPaymentNum = ui->NumOfPayments->value();
    int nMaxYearsNum = ui->NumOfYears->value();
    ui->payStatPaymentSpinBox->setMaximum(nMaxPaymentNum);
    ui->payStatYearSpinBox->setMaximum(nMaxYearsNum);
}

void MainWindow::setupCalcFromMonthlyPaymentGUI()
{
    ui->lineEditPrice->setText( doubleToCurrency ( m_Mort.getPrice(), 0, US_DOLLARS ) );
    ui->priceLabel->setText(doubleToCurrency ( m_Mort.getPrice(), 0, US_DOLLARS ));
    ui->lineEdit->setText(doubleToCurrency(m_Mort.getPrincipal(),0,US_DOLLARS ));
    ui->principalLabel->setText(doubleToCurrency(m_Mort.getPrincipal(),0,US_DOLLARS )  );

    if(!m_Mort.getCalcFromMontlyPayment())
        ui->lineEditMonthlyPayment->setText(doubleToCurrency(m_Mort.getMonthlyPayment(),2 , US_DOLLARS ) );
    ui->monthlyPaymentLabel->setText(doubleToCurrency(m_Mort.getMonthlyPayment(),2 , US_DOLLARS )  );
    ui->checkBoxCalcFromMonthlyPayment->setChecked(m_Mort.getCalcFromMontlyPayment() );
    showOrHideCalcFromMontlyPayment();

}
 void MainWindow::showOrHideCalcFromMontlyPayment()
 {
     if(m_Mort.getCalcFromMontlyPayment())
     {
         ui->lineEditPrice->hide();
         ui->priceLabel->show();
         ui->lineEdit->hide();
         ui->principalLabel->show();
         ui->monthlyPaymentLabel->hide();
         ui->lineEditMonthlyPayment->show();
         if(!bShowMortgageTerms)
             ui->priceLabel->hide();

     }
     else
     {
         ui->lineEditPrice->show();
         ui->priceLabel->hide();
         ui->lineEdit->show();
         ui->principalLabel->hide();
         ui->monthlyPaymentLabel->show();
         ui->lineEditMonthlyPayment->hide();
         if(!bShowMortgageTerms)
             ui->lineEditPrice->hide();
     }
 }



void MainWindow::setupCalcFromPercentGUI()
{
    if(m_Mort.getDownPaymentCalcFromPercent())
    {
        ui->checkBox->setChecked(true);
        ui->lineEditDownPayment->hide();
        ui->labelDownPaymentPercent->hide();
        if(bShowMortgageTerms)
        {
            ui->doubleSpinBoxDownPaymentPercent->show();
            ui->labelDownPayment->show();
        }
    }
    else
    {
        ui->checkBox->setChecked(false);
        ui->doubleSpinBoxDownPaymentPercent->hide();
        ui->labelDownPayment->hide();
        if(bShowMortgageTerms)
        {
            ui->lineEditDownPayment->show();
            ui->labelDownPaymentPercent->show();
        }
    }

    ui->lineEditDownPayment->setText( doubleToCurrency( m_Mort.getDownPaymentDollars(),0, US_DOLLARS )  );
    if(!m_Mort.getDownPaymentCalcFromPercent())
        ui->doubleSpinBoxDownPaymentPercent->setValue(m_Mort.getDownPaymentPercent()*100  );
    ui->labelDownPayment ->setText( doubleToCurrency( m_Mort.getDownPaymentDollars(),0, US_DOLLARS )  );
    ui->labelDownPaymentPercent->setText( addCommasToDouble( m_Mort.getDownPaymentPercent()*100, 2 ).append(" %") );
}


void MainWindow::setupAmortizationTableAndExtraPaymentsGUI()
{
    ui->textBrowser->clear();
    QString strReport;
    QString strAnualReport;
    int nPaymentNum = ui->spinBoxExtraPaymentNum->value();
    double dExtraPaymentAmount = usDollarsStringToDouble ( ui->lineEditExtraPayAmount->text());

    double dRecurringExtraPayment = usDollarsStringToDouble( ui->lineEditRecurringExtraAmount->text()) ;
    ui->lineEditRecurringExtraAmount->setText( doubleToCurrency(dRecurringExtraPayment,2,US_DOLLARS) );
    int nStartExtraPayments = ui->spinBoxRecurringExtraStartPoint->value();
    int nStopExtraPayments = ui->spinBoxRecurringExtraStop->value() ;

    ui->spinBoxExtraPaymentNum->setMaximum(m_Mort.getNumOfPayments());
    ui->spinBoxRecurringExtraStop->setMaximum(m_Mort.getNumOfPayments());
    ui->spinBoxRecurringExtraStartPoint->setMaximum(m_Mort.getNumOfPayments());



    int nMaxOffset = (ui->spinBoxRecurringExtraStop->value() - ui->spinBoxRecurringExtraStartPoint->value())/2;
    if(nMaxOffset)
        ui->spinBoxPaymentOffset->setMaximum(nMaxOffset);
    else
        ui->spinBoxPaymentOffset->setMaximum(1);

    if( bShowExtraPayments || bShowTable )
    {
        int nPaymentOffset = ui->spinBoxPaymentOffset->value();
        strReport = m_Mort.getAmortizationSchedule(nPaymentNum, dExtraPaymentAmount, nStartExtraPayments, dRecurringExtraPayment, nStopExtraPayments, nPaymentOffset, strAnualReport, m_dTotalIntrestPaid  );
        ui->LabelInterestPaid->setText( doubleToCurrency( m_dTotalIntrestPaid , 0, US_DOLLARS) );
        ui->label_InterestDifference ->setText( doubleToCurrency( ( m_Mort.getInterestPaid() - m_dTotalIntrestPaid) , 0, US_DOLLARS) );
     }


    if ( bShowTable )
    {
        showAmortizationSchedule();
        ui->textBrowser->setText(strReport);
    }
    else
        hideAmortizationSchedule();
    if (bShowExtraPayments)
        showExtraPayments();
    else
        hideExtraPayments();
}

void MainWindow::on_NumOfYears_valueChanged()
{
    if(!bShowTable)
        on_NumOfYears_editingFinished();
}

void MainWindow::on_NumOfPayments_valueChanged(int arg1)
{
    int nDifferenceInNumOfPayments = fabs(arg1 - m_Mort.getNumOfPayments());
    int nThresholdForLiveUpdates = 10;
    if(!bShowTable && (nDifferenceInNumOfPayments < nThresholdForLiveUpdates))
        on_NumOfPayments_editingFinished();
}

void MainWindow::on_lineEdit_textChanged()
{
    if(!bShowTable)
        on_lineEdit_editingFinished();
}

void MainWindow::on_InterestRate_valueChanged()
{
    if(!bShowTable)
        on_InterestRate_editingFinished();
}

void MainWindow::on_InterestRate_editingFinished()
{
    double dTemp = ui->InterestRate->value() / 100;
    m_Mort.enterAnualInterestRate(dTemp);
    refreshFields();
}

void MainWindow::on_lineEditMonthlyPayment_editingFinished()
{
//    double dTemp = usDollarsStringToDouble(ui->lineEditMonthlyPayment->text());
//    m_Mort.enterMonthlyPayment(dTemp);

    refreshFields();
}

void MainWindow::on_lineEditDownPayment_textChanged()
{
    if(!bShowTable)
        on_lineEditDownPayment_editingFinished();
}

void MainWindow::on_lineEditPrice_textChanged()
{
    if(!bShowTable)
        on_lineEditPrice_editingFinished();
}

void MainWindow::on_doubleSpinBoxDownPaymentPercent_valueChanged()
{
    if(!bShowTable)
        on_doubleSpinBoxDownPaymentPercent_editingFinished();
}


void MainWindow::on_checkBox_clicked(bool checked)
{
    m_Mort.setDownPaymentCalcFromPercent(checked);
    refreshFields();
}

void MainWindow::on_doubleSpinBoxMillRate_editingFinished()
{
    m_Mort.enterMillRate(ui->doubleSpinBoxMillRate->value() );
    refreshFields();
}

void MainWindow::on_lineEditOtherMonthly_editingFinished()
{
    double dTemp = usDollarsStringToDouble(ui->lineEditOtherMonthly->text() );
    m_Mort.enterOtherMonthlyExpenses(dTemp);
    refreshFields();
}

void MainWindow::on_lineEditExtraPayAmount_editingFinished()
{
     double dInsert = usDollarsStringToDouble(  ui->lineEditExtraPayAmount->text());
     ui->lineEditExtraPayAmount->setText( doubleToCurrency ( dInsert,0,US_DOLLARS ) );
     refreshFields();
}

void MainWindow::showAmortizationSchedule()
{
    ui->textBrowser->show();
    ui->lineAmortizationTable->show();



}
void MainWindow::hideAmortizationSchedule()
{
    ui->textBrowser->hide();
    ui->lineAmortizationTable->hide();


}

void MainWindow::showMortgageTerms()
{
    ui->priceLabel->show();
    ui->lineEditPrice->show();
    //ui->label->show(); principal
    ui->checkBox->show();//DP calc %
    ui->checkBoxCalcFromMonthlyPayment->show();
    ui->labelDownPayment->show();
    ui->labelDownPaymentPercent->show();
    ui->labelAnualCostsAndTaxes->show();
    ui->labelAnnualTax->show();
    ui->labelMontlyTax->show();
    ui->labelPrincipalAndInterest->show();
    ui->labelDownPaymentPercent->show();

    ui->label_2->show();
    ui->label_3->show();
    ui->label_4->show();
    //ui->label_5->show();
    //ui->label_6->show();
    ui->label_7->show();
    ui->label_8->show();
    ui->label_9->show();
    ui->label_10->show();

    ui->label_11->show();
    ui->label_12->show();
    ui->label_13->show();
    ui->label_14->show();
    ui->label_15->show();

    ui->lineEditPrice->show();
    //ui->lineEdit->show();
    ui->lineEditDownPayment->show();
    ui->lineEditOtherMonthly->show();
    ui->doubleSpinBoxDownPaymentPercent->show();
    ui->doubleSpinBoxMillRate->show();
    ui->NumOfYears->show();
    ui->NumOfPayments->show();
    ui->InterestRate->show();



}

void MainWindow::hideMortgageTerms()
{

    ui->priceLabel->hide();
    ui->lineEditPrice->hide();
    //ui->label->hide(); principal
    ui->checkBox->hide();//DP calc %
    ui->checkBoxCalcFromMonthlyPayment->hide();
    ui->labelDownPayment->hide();
    ui->labelDownPaymentPercent->hide();
    ui->labelAnualCostsAndTaxes->hide();
    ui->labelAnnualTax->hide();
    ui->labelMontlyTax->hide();
    ui->labelPrincipalAndInterest->hide();
    ui->labelDownPaymentPercent->hide();

    ui->label_2->hide();
    //ui->label_3->hide();//num of years
    //ui->label_4->hide();//num of payments
    //ui->label_5->hide();
    //ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->label_9->hide();
    ui->label_10->hide();

    ui->label_11->hide();
    ui->label_12->hide();
    ui->label_13->hide();
    ui->label_14->hide();
    ui->label_15->hide();

    ui->lineEditPrice->hide();
    //ui->lineEdit->hide();
    ui->lineEditDownPayment->hide();
    ui->lineEditOtherMonthly->hide();
    ui->doubleSpinBoxDownPaymentPercent->hide();
    ui->doubleSpinBoxMillRate->hide();
    //ui->NumOfYears->hide();
    //ui->NumOfPayments->hide();
    ui->InterestRate->hide();

}

void MainWindow::showExtraPayments()
{
    ui->lineEditExtraPayAmount->show();
    ui->spinBoxExtraPaymentNum->show();
    ui->pushButtonClearExtraPayments->show();
    ui->label_extraamount->show();
    ui->label_ExtraPaymentNum->show();
    ui->label_extratitle->show();
    ui->label_recurringExtra->show();
    ui->lineEditRecurringExtraAmount->show();
    ui->labelRecurringStartNum->show();
    ui->spinBoxRecurringExtraStartPoint->show();
    ui->spinBoxRecurringExtraStop->show();
    ui->labelRecurringExtraStopNum->show();
    ui->label_RecurringAmount->show();
    ui->line_Payments->show();
    ui->LabelInterestPaid->show();
    ui->label_sumInterest->show();
    ui->label_InterestDifference->show();
    ui->label_Diff->show();
    ui->labelPaymentOffsetTitle->show();
    ui->spinBoxPaymentOffset->show();
}

void MainWindow::hideExtraPayments()
{
    ui->lineEditExtraPayAmount->hide();
    ui->spinBoxExtraPaymentNum->hide();
    ui->pushButtonClearExtraPayments->hide();
    ui->label_extraamount->hide();
    ui->label_ExtraPaymentNum->hide();
    ui->label_extratitle->hide();
    ui->label_recurringExtra->hide();
    ui->lineEditRecurringExtraAmount->hide();
    ui->labelRecurringStartNum->hide();
    ui->spinBoxRecurringExtraStartPoint->hide();
    ui->spinBoxRecurringExtraStop->hide();
    ui->labelRecurringExtraStopNum->hide();
    ui->label_RecurringAmount->hide();
    ui->line_Payments->hide();
    ui->LabelInterestPaid->hide();
    ui->label_sumInterest->hide();
    ui->label_InterestDifference->hide();
    ui->label_Diff->hide();
    ui->labelPaymentOffsetTitle->hide();
    ui->spinBoxPaymentOffset->hide();
}

void MainWindow::showPaymentStatistics()
{
    ui->payStatEquityLabel->show();
    ui->payStatInterestLabel->show();
    ui->payStatIntTaxOtherLabel->show();
    ui->payStatOtherLabel->show();
    ui->payStatPaymentSpinBox->show();
    ui->payStatPmtsToZeroLabel->show();
    ui->payStatPrincipalLabel->show();
    ui->payStatsLine->show();
    ui->payStatTaxesLabel->show();
    ui->payStatYearSpinBox->show();
    ui->payStatYearsToZeroLabel->show();
    ui->payStatInerestSavedLabel->show();
    ui->payStat80LoanToValueLabel->show();
    ui->payStatSumExtraPaymentsLabel->show();
    ui->payStatDiffInValueLabel->show();

    ui->label_16->show();
    ui->label_17->show();
    ui->label_18->show();
    ui->label_19->show();
    ui->label_20->show();
    ui->label_21->show();
    ui->label_22->show();
    ui->label_23->show();
    ui->label_24->show();
    ui->label_25->show();
    ui->label_28->show();
    ui->label_29->show();
    ui->label_26->show();
    ui->label_27->show();
}

void MainWindow::hidePaymentStatistics()
{
    ui->payStatEquityLabel->hide();
    ui->payStatInterestLabel->hide();
    ui->payStatIntTaxOtherLabel->hide();
    ui->payStatOtherLabel->hide();
    ui->payStatPaymentSpinBox->hide();
    ui->payStatPmtsToZeroLabel->hide();
    ui->payStatPrincipalLabel->hide();
    ui->payStatsLine->hide();
    ui->payStatTaxesLabel->hide();
    ui->payStatYearSpinBox->hide();
    ui->payStatYearsToZeroLabel->hide();
    ui->payStatInerestSavedLabel->hide();
    ui->payStat80LoanToValueLabel->hide();
    ui->payStatSumExtraPaymentsLabel->hide();
    ui->payStatDiffInValueLabel->hide();

    ui->label_16->hide();
    ui->label_17->hide();
    ui->label_18->hide();
    ui->label_19->hide();
    ui->label_20->hide();
    ui->label_21->hide();
    ui->label_22->hide();
    ui->label_23->hide();
    ui->label_24->hide();
    ui->label_25->hide();
    ui->label_28->hide();
    ui->label_29->hide();
    ui->label_26->hide();
    ui->label_27->hide();
}

void MainWindow::on_actionShow_Amortization_Shedule_toggled(bool arg1)
{
    bShowTable = arg1;
    refreshFields();
}

void MainWindow::on_actionShow_Extra_Payments_toggled(bool arg1)
{
    bShowExtraPayments = arg1;
    refreshFields();
}

void MainWindow::on_pushButtonClearExtraPayments_clicked()
{
    ui->lineEditExtraPayAmount->clear();
    ui->lineEditRecurringExtraAmount->clear();
    ui->spinBoxExtraPaymentNum->setValue(0);
    ui->spinBoxRecurringExtraStartPoint->setValue(0);
    ui->spinBoxRecurringExtraStop->setValue(m_Mort.getNumOfPayments() );
    refreshFields();

}

void MainWindow::on_spinBoxRecurringExtraStartPoint_valueChanged(int arg1)
{
    if(ui->spinBoxRecurringExtraStop->value() < arg1)
        ui->spinBoxRecurringExtraStop->setValue(arg1);
    if(!bShowTable)
        on_spinBoxRecurringExtraStartPoint_editingFinished();
}

void MainWindow::on_spinBoxRecurringExtraStop_valueChanged(int arg1)
{
    if(ui->spinBoxRecurringExtraStartPoint->value() > arg1)
        ui->spinBoxRecurringExtraStartPoint->setValue(arg1);
    if(!bShowTable)
        on_spinBoxRecurringExtraStop_editingFinished();
}

void MainWindow::on_lineEditRecurringExtraAmount_editingFinished()
{
    refreshFields();
}

void MainWindow::on_checkBoxCalcFromMonthlyPayment_clicked(bool checked)
{
    m_Mort.setCalcFromMonthlyPayment(checked);
    if(checked)
    {
        double dTemp = usDollarsStringToDouble(ui->lineEditMonthlyPayment->text());
        m_Mort.enterMonthlyPayment(dTemp);
    }
    refreshFields();
}

void MainWindow::on_spinBoxExtraPaymentNum_valueChanged()
{
    if(!bShowTable)
        on_spinBoxExtraPaymentNum_editingFinished();
}

void MainWindow::on_lineEditPrice_editingFinished()
{
    {
        double dTemp = usDollarsStringToDouble( ui->lineEditPrice->text());
        m_Mort.enterPrice(dTemp);
        refreshFields();
    }
}

void MainWindow::on_doubleSpinBoxDownPaymentPercent_editingFinished()
{
    double arg1 = ui->doubleSpinBoxDownPaymentPercent->value();
    double dTemp = arg1 / 100;
    if(arg1 == 0)
    {
        m_Mort.enterPrincipal(usDollarsStringToDouble( ui->lineEditPrice->text() ));
    }
    m_Mort.enterDownPaymentPercent(dTemp);
    refreshFields();
}

void MainWindow::on_lineEditDownPayment_editingFinished()
{
    QString arg1 = ui->lineEditDownPayment->text();
    double dTemp = usDollarsStringToDouble(arg1);
    m_Mort.enterDownPaymentDollars(dTemp);
    if(dTemp == 0)
    {
        m_Mort.enterPrincipal(usDollarsStringToDouble( ui->lineEditPrice->text() ));
    }


    refreshFields();
}

void MainWindow::on_lineEdit_editingFinished()
{
    QString arg1 = ui->lineEdit->text();
    double dTemp = usDollarsStringToDouble(arg1);
    m_Mort.enterPrincipal(dTemp);
    ui->lineEdit->setText( doubleToCurrency(m_Mort.getPrincipal(),0,US_DOLLARS ) );
    refreshFields();
}

void MainWindow::on_NumOfYears_editingFinished()
{
    int arg1 = ui->NumOfYears->value();
    m_Mort.enterNumOfYears(arg1 );
    int nNumOfPayments = ui->NumOfPayments->value();
    int const nNumOfMonthsInYear = 12;
    if(arg1 == static_cast<int>(nNumOfPayments/nNumOfMonthsInYear))
    {
        m_Mort.enterNumOfPayments(nNumOfPayments);
    }

    ui->NumOfPayments->setValue(m_Mort.getNumOfPayments()  );
    refreshFields();
}

void MainWindow::on_NumOfPayments_editingFinished()
{
    int arg1 = ui->NumOfPayments->value();
    m_Mort.enterNumOfPayments(arg1 );
    ui->NumOfYears->setValue(m_Mort.getNumOfYears() );
    refreshFields();
}

void MainWindow::on_spinBoxExtraPaymentNum_editingFinished()
{
    refreshFields();
}

void MainWindow::on_spinBoxRecurringExtraStartPoint_editingFinished()
{
    refreshFields();
}

void MainWindow::on_spinBoxRecurringExtraStop_editingFinished()
{
    refreshFields();
}

void MainWindow::on_spinBoxPaymentOffset_editingFinished()
{
    refreshFields();
}

void MainWindow::on_spinBoxPaymentOffset_valueChanged()
{
    if(!bShowTable)
        on_spinBoxPaymentOffset_editingFinished();
}

void MainWindow::on_actionTitle_Block_toggled(bool arg1)
{
    bShowTitleBlock = arg1;
    refreshFields();
}

void MainWindow::on_lineEdit_TitleBlock_textChanged(const QString &arg1)
{
    if(arg1 == "")
        this->setWindowTitle("Mode RN - Mortgage Calculator");
    else
        this->setWindowTitle(arg1);
}



void MainWindow::on_lineEditMonthlyPayment_textChanged(const QString &arg1)
{
   if(m_Mort.getCalcFromMontlyPayment())
   {
    double dTemp = usDollarsStringToDouble(arg1);
    QString strTemp = "";
    int nlength = arg1.length();
    int nDecPos = arg1.indexOf('.')+1;
    if (nDecPos <= 0)
        nDecPos = 1;
    int nDecimalsToShow = nlength -(nDecPos);
    if (arg1.indexOf('.') == -1)
        nDecimalsToShow = 0;
    if(nDecimalsToShow > 2)
    {
        for (int iii = 0; iii < (nlength -1); iii++)
            strTemp.append(arg1[iii]  );
        nDecimalsToShow = 2;
        dTemp = usDollarsStringToDouble(strTemp);
    }
    m_Mort.enterMonthlyPayment(dTemp);
    if (nlength != nDecPos)
    {
        double dTempMonthlyPayment = m_Mort.getMonthlyPayment();
        dTempMonthlyPayment = roundDoubleToPoints(dTempMonthlyPayment, nDecimalsToShow);
        QString strMontlyPayment = doubleToCurrency(dTempMonthlyPayment,nDecimalsToShow , US_DOLLARS );
        ui->lineEditMonthlyPayment->setText(strMontlyPayment );
    }
    if(!bShowTable && m_Mort.getCalcFromMontlyPayment())
        on_lineEditMonthlyPayment_editingFinished();
   }
}

void MainWindow::on_actionReset_All_triggered()
{
    m_Mort.resetDefaults();
    ui->doubleSpinBoxMillRate->setValue(m_Mort.getMillRate());
    ui->lineEdit_TitleBlock->clear();
    ui->NumOfPayments->setValue(m_Mort.getNumOfPayments() );
    ui->principalLabel->setText(doubleToCurrency(m_Mort.getPrincipal(), 2, US_DOLLARS));

    ui->NumOfYears->setValue(m_Mort.getNumOfYears());// <---------------------
    ui->InterestRate->setValue(m_Mort.getAnualInterestRate()  );
    on_pushButtonClearExtraPayments_clicked();
    m_cMontlyCosts->resetAll(); ;

    //refreshFields(); <- done by clear extra payments
}

void MainWindow::on_actionShow_Mortgage_Terms_toggled(bool arg1)
{
   bShowMortgageTerms = arg1;
    refreshFields();
}

void MainWindow::on_doubleSpinBoxMillRate_valueChanged()
{
       if(!bShowTable)
            {
                on_doubleSpinBoxMillRate_editingFinished();
            }

}

void MainWindow::on_actionCalculate_Mill_Rate_triggered()
{
    double dMillRate;
    CalculateMillRateDialog *x = new CalculateMillRateDialog(this, &dMillRate  );
    x->exec();
    if(dMillRate != -1 && dMillRate >= 0)
    {
        m_Mort.enterMillRate(dMillRate);
        ui->doubleSpinBoxMillRate->setValue(m_Mort.getMillRate());
        refreshFields();
    }
    delete x;
}


void MainWindow::on_actionCalculate_Other_Monthly_Expenses_triggered()
{
    m_cMontlyCosts->show();
}

void MainWindow::enterCalculatedMonthlyExpenses(double dMonthlyEpenses)
{
    m_Mort.enterOtherMonthlyExpenses(dMonthlyEpenses);
    refreshFields();
}

void MainWindow::on_actionAbout_triggered()
{
    aboutDialog *about = new aboutDialog;
    about->show();
}

void MainWindow::on_actionAlways_On_Top_toggled(bool arg1)
{
    Qt::WindowFlags flags = this->windowFlags();
    if (arg1)
    {
        this->setWindowFlags(flags | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
        this->show();
    }
    else
    {
        this->setWindowFlags(flags ^ (Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint));
        this->show();
    }
}






void MainWindow::on_actionShow_Payment_Statistics_toggled(bool arg1)
{
    bShowPaymentStatistics = arg1;
    refreshFields();
}



void MainWindow::on_payStatYearSpinBox_valueChanged()
{
    if(!bShowTable)
        on_payStatYearSpinBox_editingFinished();
}

void MainWindow::on_payStatYearSpinBox_editingFinished()
{
    int nNumOfMonthsInYear = 12;
    int nYear = ui->payStatYearSpinBox->value();
    int nPayNum = ui->payStatPaymentSpinBox->value();
    if(nYear != (nPayNum/nNumOfMonthsInYear))
        ui->payStatPaymentSpinBox->setValue(nYear*nNumOfMonthsInYear);
}

void MainWindow::on_payStatPaymentSpinBox_valueChanged()
{
    if(!bShowTable)
        on_payStatPaymentSpinBox_editingFinished();
}

void MainWindow::on_payStatPaymentSpinBox_editingFinished()
{
    int nNumOfMonthsInYear = 12;
    int nPaymentNum = ui->payStatPaymentSpinBox->value();
    ui->payStatYearSpinBox->setValue(nPaymentNum/nNumOfMonthsInYear);
}
