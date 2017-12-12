#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refreshFields();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshFields()
{
    if(bShowTitleBlock)
        ui->lineEdit_TitleBlock->show();
    else
        ui->lineEdit_TitleBlock->hide();
    if(bShowMortgageTerms)
        showMortgageTerms();
    else
        hideMortgageTerms();

    ui->lineEditPrice->setText( doubleToCurrency ( m_Mort.getPrice(), 0, US_DOLLARS ) );
    ui->lineEdit->setText(doubleToCurrency(m_Mort.getPrincipal(),0,US_DOLLARS ));

    ui->lineEditMonthlyPayment->setText(doubleToCurrency(m_Mort.getMonthlyPayment(),2 , US_DOLLARS ) );
    ui->AmountofInterest->setText( doubleToCurrency (m_Mort.getInterestPaid(), 0, US_DOLLARS)    );



    ui->lineEditDownPayment->setText( doubleToCurrency( m_Mort.getDownPaymentDollars(),0, US_DOLLARS )  );
    ui->doubleSpinBoxDownPaymentPercent->setValue(m_Mort.getDownPaymentPercent()*100  );
    ui->labelDownPayment ->setText( doubleToCurrency( m_Mort.getDownPaymentDollars(),0, US_DOLLARS )  );
    ui->labelDownPaymentPercent->setText( addCommasToDouble( m_Mort.getDownPaymentPercent()*100, 2 ).append(" %") );

    ui->labelMontlyTax->setText( doubleToCurrency (m_Mort.getMonthlyTaxPayment(), 2, US_DOLLARS ) );
    ui->labelPrincipalAndInterest->setText( doubleToCurrency(m_Mort.getPrincipalAndInterestMontlyPayment() , 2, US_DOLLARS  )  ); //<-----------------------------
    ui->doubleSpinBoxMillRate->setValue(m_Mort.getMillRate() );
    ui->lineEditOtherMonthly->setText( doubleToCurrency( m_Mort.getOtherMontlyExpenses() , 2, US_DOLLARS)  );
    ui->labelAnualCostsAndTaxes->setText( doubleToCurrency( m_Mort.getAnnualTaxesAndExpenses(), 0, US_DOLLARS) );

    //Save this for another day - Too confusing
    //ui->labelLifeOfLoanTaxAndExpenses->setText( doubleToCurrency ( m_Mort.getLifeOfLoanTaxesAndExpenses(),0, US_DOLLARS));
    ui->labelLifeOfLoanTaxAndExpenses->hide();
    ui->label_LifeOfLoanTitle->hide();

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

    ui->checkBoxCalcFromMonthlyPayment->setChecked(m_Mort.getCalcFromMontlyPayment() );

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

void MainWindow::on_NumOfYears_valueChanged(int arg1)
{
    if(!bShowTable)
        on_NumOfYears_editingFinished();
}

void MainWindow::on_NumOfPayments_valueChanged(int arg1)
{
    if(!bShowTable)
        on_NumOfPayments_editingFinished();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if(!bShowTable)
        on_lineEdit_editingFinished();
}

void MainWindow::on_InterestRate_valueChanged(double arg1)
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
    double dTemp = usDollarsStringToDouble(ui->lineEditMonthlyPayment->text());
    m_Mort.enterMonthlyPayment(dTemp);
    refreshFields();
}

void MainWindow::on_lineEditDownPayment_textChanged(const QString &arg1)
{
    if(!bShowTable)
        on_lineEditDownPayment_editingFinished();
}

void MainWindow::on_lineEditPrice_textChanged(const QString &arg1)
{
    if(!bShowTable)
        on_lineEditPrice_editingFinished();
}

void MainWindow::on_doubleSpinBoxDownPaymentPercent_valueChanged(double arg1)
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
    //ui->label->show(); principal
    ui->checkBox->show();//DP calc %
    ui->checkBoxCalcFromMonthlyPayment->show();
    ui->labelDownPayment->show();
    ui->labelDownPaymentPercent->show();
    ui->labelAnualCostsAndTaxes->show();
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
    //ui->label->hide(); principal
    ui->checkBox->hide();//DP calc %
    ui->checkBoxCalcFromMonthlyPayment->hide();
    ui->labelDownPayment->hide();
    ui->labelDownPaymentPercent->hide();
    ui->labelAnualCostsAndTaxes->hide();
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
}

void MainWindow::on_spinBoxExtraPaymentNum_valueChanged(int arg1)
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

void MainWindow::on_spinBoxPaymentOffset_valueChanged(int arg1)
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

void MainWindow::on_doubleSpinBoxMillRate_valueChanged(double arg1)
{
    if(!bShowTable)
        on_doubleSpinBoxMillRate_editingFinished();
}

void MainWindow::on_lineEditMonthlyPayment_textChanged(const QString &arg1)
{
    //if(!bShowTable && m_Mort.getCalcFromMontlyPayment() )// Doesn't work because of Decimals in the string.
        //on_lineEditMonthlyPayment_editingFinished();
}

void MainWindow::on_actionReset_All_triggered()
{
    m_Mort.resetDefaults();
    ui->lineEdit_TitleBlock->clear();
    ui->NumOfPayments->setValue(m_Mort.getNumOfPayments() );
    ui->NumOfYears->setValue(m_Mort.getNumOfYears());// <---------------------
    ui->InterestRate->setValue(m_Mort.getAnualInterestRate()  );
    on_pushButtonClearExtraPayments_clicked();
    //refreshFields(); <- done by clear extra payments
}

void MainWindow::on_actionShow_Mortgage_Terms_toggled(bool arg1)
{
   bShowMortgageTerms = arg1;
    refreshFields();
}
