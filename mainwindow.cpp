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
        ui->doubleSpinBoxDownPaymentPercent->show();
        ui->lineEditDownPayment->hide();
        ui->labelDownPaymentPercent->hide();
        ui->labelDownPayment->show();

    }
    else
    {
        ui->doubleSpinBoxDownPaymentPercent->hide();
        ui->lineEditDownPayment->show();
        ui->labelDownPaymentPercent->show();
        ui->labelDownPayment->hide();
    }

    ui->textBrowser->clear();
    QString strReport;
    QString strAnualReport;
    int nPaymentNum = ui->spinBoxExtraPaymentNum->value();
    double dExtraPaymentAmount = usDollarsStringToDouble ( ui->lineEditExtraPayAmount->text());

    double dRecurringExtraPayment = usDollarsStringToDouble( ui->lineEditRecurringExtraAmount->text()) ;
    ui->lineEditRecurringExtraAmount->setText( doubleToCurrency(dRecurringExtraPayment,2,US_DOLLARS) );
    int nStartExtraPayments = ui->spinBoxRecurringExtraStartPoint->value();
    int nStopExtraPayments = ui->spinBoxRecurringExtraStop->value() ;

//    m_Mort.getNumOfPayments();
    ui->spinBoxExtraPaymentNum->setMaximum(m_Mort.getNumOfPayments());

    ui->spinBoxRecurringExtraStop->setMaximum(m_Mort.getNumOfPayments());
    ui->spinBoxRecurringExtraStartPoint->setMaximum(m_Mort.getNumOfPayments());

    int nMaxOffset = (ui->spinBoxRecurringExtraStop->value() - ui->spinBoxRecurringExtraStartPoint->value())/2;
    if(nMaxOffset)
        ui->spinBoxPaymentOffset->setMaximum(nMaxOffset);
    else
        ui->spinBoxPaymentOffset->setMaximum(1);
    //ui->spinBoxPaymentOffset->setMinimum(1);

    if( bShowExtraPayments || bShowTable )
    {
    int nPaymentOffset = ui->spinBoxPaymentOffset->value();
    strReport = m_Mort.getAmortizationSchedule(nPaymentNum, dExtraPaymentAmount, nStartExtraPayments, dRecurringExtraPayment, nStopExtraPayments, nPaymentOffset, strAnualReport, m_dTotalIntrestPaid  );
    ui->LabelInterestPaid->setText( doubleToCurrency( m_dTotalIntrestPaid , 0, US_DOLLARS) );
    ui->label_InterestDifference ->setText( doubleToCurrency( ( m_Mort.getInterestPaid() - m_dTotalIntrestPaid) , 0, US_DOLLARS) );
    //ui->textBrowser->setText(strReport);
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

    //adjustSize();
}

void MainWindow::on_NumOfYears_valueChanged(int arg1)
{
    if(!bShowTable)
        on_NumOfYears_editingFinished();
//    m_Mort.enterNumOfYears(arg1 );
//    ui->NumOfPayments->setValue(m_Mort.getNumOfPayments()  );
//    refreshFields();
}

void MainWindow::on_NumOfPayments_valueChanged(int arg1)
{
    if(!bShowTable)
        on_NumOfPayments_editingFinished();

//    m_Mort.enterNumOfPayments(arg1 );
//    ui->NumOfYears->setValue(m_Mort.getNumOfYears() );
//    refreshFields();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if(!bShowTable)
        on_lineEdit_editingFinished();
//     double dTemp = usDollarsStringToDouble(arg1);
//     m_Mort.enterPrincipal(dTemp);
//     ui->lineEdit->setText( doubleToCurrency(m_Mort.getPrincipal(),0,US_DOLLARS ) );
//     refreshFields();
}

void MainWindow::on_InterestRate_valueChanged(double arg1)
{
    if(!bShowTable)
        on_InterestRate_editingFinished();
//        double dTemp = arg1 / 100;
//        m_Mort.enterAnualInterestRate(dTemp);
//        refreshFields();
}

void MainWindow::on_InterestRate_editingFinished()
{
    double dTemp = ui->InterestRate->value() / 100;
    m_Mort.enterAnualInterestRate(dTemp);
    refreshFields();
}

//void MainWindow::on_lineEditMonthlyPayment_textChanged(const QString &arg1)
//{

//}

void MainWindow::on_lineEditMonthlyPayment_editingFinished()
{
    double dTemp = usDollarsStringToDouble(ui->lineEditMonthlyPayment->text());
    m_Mort.enterMonthlyPayment(dTemp);
    //ui->lineEditMonthlyPayment->setText( doubleToCurrency(m_Mort.getMonthlyPayment(),2,US_DOLLARS) );
    refreshFields();
}

void MainWindow::on_lineEditDownPayment_textChanged(const QString &arg1)
{
    if(!bShowTable)
        on_lineEditDownPayment_editingFinished();

//    double dTemp = usDollarsStringToDouble(arg1);
//    m_Mort.enterDownPaymentDollars(dTemp);
//    refreshFields();
}

void MainWindow::on_lineEditPrice_textChanged(const QString &arg1)
{
    if(!bShowTable)
        on_lineEditPrice_editingFinished();
//    double dTemp = usDollarsStringToDouble( arg1);
//    m_Mort.enterPrice(dTemp);
//    refreshFields();
}

void MainWindow::on_doubleSpinBoxDownPaymentPercent_valueChanged(double arg1)
{
    if(!bShowTable)
        on_doubleSpinBoxDownPaymentPercent_editingFinished();
//    double dTemp = arg1 / 100;
//    m_Mort.enterDownPaymentPercent(dTemp);
//    refreshFields();
}

//void MainWindow::on_doubleSpinBoxMillRate_valueChanged(double arg1)
//{

//}

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

//void MainWindow::on_lineEditOtherMonthly_textChanged(const QString &arg1)
//{
//     double dTemp = usDollarsStringToDouble( arg1);
//     ui->lineEditOtherMonthly->setText( doubleToCurrency( dTemp, 2, US_DOLLARS)  );
//}

void MainWindow::on_lineEditOtherMonthly_editingFinished()
{
    double dTemp = usDollarsStringToDouble(ui->lineEditOtherMonthly->text() );
    m_Mort.enterOtherMonthlyExpenses(dTemp);
    refreshFields();
}

// double MainWindow::calcAnualExpenses()
// {
//     int const nNumOfMonthsInYear = 12;
//     double dTemp = (m_Mort.getMonthlyTaxPayment()*nNumOfMonthsInYear) + (m_Mort.getOtherMontlyExpenses()*nNumOfMonthsInYear) ;
//     return dTemp;
// }

void MainWindow::on_lineEditExtraPayAmount_editingFinished()
{
     double dInsert = usDollarsStringToDouble(  ui->lineEditExtraPayAmount->text());
     ui->lineEditExtraPayAmount->setText( doubleToCurrency ( dInsert,0,US_DOLLARS ) );
     refreshFields();
}

//void MainWindow::on_pushButtonInsert_clicked()
//{
//    double dInsert = usDollarsStringToDouble(  ui->lineEditExtraPayAmount->text());
//    QString strTemp = m_Mort.getAmortizationSchedule(ui->spinBoxExtraPaymentNum->value() , dInsert );
//    ui->textBrowser->clear();
//    ui->textBrowser->setText( strTemp );
//}

//void MainWindow::on_pushButton_toggled(bool checked)
//{

//}

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

//void MainWindow::on_pushButton_clicked(bool checked)
//{
//    if(bShowTable)
//        bShowTable = false;
//    else
//        bShowTable = true;
//    refreshFields();
//}

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

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    if(arg1 == "")
        this->setWindowTitle("Mode RN - Mortgage Calculator");
    else
        this->setWindowTitle(arg1);
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
//    refreshFields();
}

void MainWindow::on_spinBoxRecurringExtraStop_valueChanged(int arg1)
{
    if(ui->spinBoxRecurringExtraStartPoint->value() > arg1)
        ui->spinBoxRecurringExtraStartPoint->setValue(arg1);
//    refreshFields();
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
    //refreshFields();
}

void MainWindow::on_lineEditPrice_editingFinished()
{
    //if(bShowTable)
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
    m_Mort.enterDownPaymentPercent(dTemp);
    refreshFields();
}

void MainWindow::on_lineEditDownPayment_editingFinished()
{
    QString arg1 = ui->lineEditDownPayment->text();
    double dTemp = usDollarsStringToDouble(arg1);
    m_Mort.enterDownPaymentDollars(dTemp);
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
