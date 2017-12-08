#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_pushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
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
    ui->labelAnualCostsAndTaxes->setText( doubleToCurrency( calcAnualExpenses(), 0, US_DOLLARS) );

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
    double dRecurringExtraPayment;

    strReport = m_Mort.getAmortizationSchedule(nPaymentNum, dExtraPaymentAmount, dRecurringExtraPayment, strAnualReport );
    ui->textBrowser->setText(strReport);

    m_Mort.getNumOfPayments();
    ui->spinBoxExtraPaymentNum->setMaximum(m_Mort.getNumOfPayments());

    if ( bShowTable )
        showAmortizationSchedule();
    else
        hideAmortizationSchedule();

    //adjustSize();
}

void MainWindow::on_NumOfYears_valueChanged(int arg1)
{
    m_Mort.enterNumOfYears(arg1 );
    ui->NumOfPayments->setValue(m_Mort.getNumOfPayments()  );
    on_pushButton_clicked();
}

void MainWindow::on_NumOfPayments_valueChanged(int arg1)
{
    m_Mort.enterNumOfPayments(arg1 );
    ui->NumOfYears->setValue(m_Mort.getNumOfYears() );
    on_pushButton_clicked();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
     double dTemp = usDollarsStringToDouble(arg1);
     m_Mort.enterPrincipal(dTemp);
     ui->lineEdit->setText( doubleToCurrency(m_Mort.getPrincipal(),0,US_DOLLARS ) );
     on_pushButton_clicked();
}

void MainWindow::on_InterestRate_valueChanged(double arg1)
{

        double dTemp = arg1 / 100;
        m_Mort.enterAnualInterestRate(dTemp);
        on_pushButton_clicked();
}

void MainWindow::on_InterestRate_editingFinished()
{
    double dTemp = ui->InterestRate->value() / 100;
    m_Mort.enterAnualInterestRate(dTemp);
    on_pushButton_clicked();
}

//void MainWindow::on_lineEditMonthlyPayment_textChanged(const QString &arg1)
//{

//}

void MainWindow::on_lineEditMonthlyPayment_editingFinished()
{
    double dTemp = usDollarsStringToDouble(ui->lineEditMonthlyPayment->text());
    m_Mort.enterMonthlyPayment(dTemp);
    //ui->lineEditMonthlyPayment->setText( doubleToCurrency(m_Mort.getMonthlyPayment(),2,US_DOLLARS) );
    on_pushButton_clicked();
}

void MainWindow::on_lineEditDownPayment_textChanged(const QString &arg1)
{
    double dTemp = usDollarsStringToDouble(arg1);
    m_Mort.enterDownPaymentDollars(dTemp);
    on_pushButton_clicked();
}

void MainWindow::on_lineEditPrice_textChanged(const QString &arg1)
{
    double dTemp = usDollarsStringToDouble( arg1);
    m_Mort.enterPrice(dTemp);
    on_pushButton_clicked();
}

void MainWindow::on_doubleSpinBoxDownPaymentPercent_valueChanged(double arg1)
{
    double dTemp = arg1 / 100;
    m_Mort.enterDownPaymentPercent(dTemp);
    on_pushButton_clicked();
}

//void MainWindow::on_doubleSpinBoxMillRate_valueChanged(double arg1)
//{

//}

void MainWindow::on_checkBox_clicked(bool checked)
{
    m_Mort.setDownPaymentCalcFromPercent(checked);
    on_pushButton_clicked();
}

void MainWindow::on_doubleSpinBoxMillRate_editingFinished()
{
    m_Mort.enterMillRate(ui->doubleSpinBoxMillRate->value() );
    on_pushButton_clicked();
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
    on_pushButton_clicked();
}

 double MainWindow::calcAnualExpenses()
 {
     int const nNumOfMonthsInYear = 12;
     double dTemp = (m_Mort.getMonthlyTaxPayment()*nNumOfMonthsInYear) + (m_Mort.getOtherMontlyExpenses()*nNumOfMonthsInYear) ;
     return dTemp;
 }

void MainWindow::on_lineEditExtraPayAmount_editingFinished()
{
     double dInsert = usDollarsStringToDouble(  ui->lineEditExtraPayAmount->text());
     ui->lineEditExtraPayAmount->setText( doubleToCurrency ( dInsert,0,US_DOLLARS ) );
     on_pushButton_clicked();
}

void MainWindow::on_pushButtonInsert_clicked()
{
//    double dInsert = usDollarsStringToDouble(  ui->lineEditExtraPayAmount->text());
//    QString strTemp = m_Mort.getAmortizationSchedule(ui->spinBoxExtraPaymentNum->value() , dInsert );
//    ui->textBrowser->clear();
//    ui->textBrowser->setText( strTemp );
}

//void MainWindow::on_pushButton_toggled(bool checked)
//{

//}

void MainWindow::showAmortizationSchedule()
{
    ui->textBrowser->show();


}
void MainWindow::hideAmortizationSchedule()
{
    ui->textBrowser->hide();

}

void MainWindow::showExtraPayments()
{
    ui->lineEditExtraPayAmount->show();
    ui->spinBoxExtraPaymentNum->show();
    ui->pushButtonInsert->show();
    ui->label_extraamount->show();
    ui->label_ExtraPaymentNum->show();
    ui->label_extratitle->show();
    ui->label_recurringExtra->show();
    ui->lineEditRecurringExtraAmount->show();
    ui->labelRecurringStartNum->show();
    ui->spinBoxRecurringExtraStartPoint->show();
}

void MainWindow::hideExtraPayments()
{
    ui->lineEditExtraPayAmount->hide();
    ui->spinBoxExtraPaymentNum->hide();
    ui->pushButtonInsert->hide();
    ui->label_extraamount->hide();
    ui->label_ExtraPaymentNum->hide();
    ui->label_extratitle->hide();
    ui->label_recurringExtra->hide();
    ui->lineEditRecurringExtraAmount->hide();
    ui->labelRecurringStartNum->hide();
    ui->spinBoxRecurringExtraStartPoint->hide();
}

//void MainWindow::on_pushButton_clicked(bool checked)
//{
//    if(bShowTable)
//        bShowTable = false;
//    else
//        bShowTable = true;
//    on_pushButton_clicked();
//}

void MainWindow::on_actionShow_Amortization_Shedule_toggled(bool arg1)
{
    bShowTable = arg1;
    on_pushButton_clicked();
}

void MainWindow::on_actionShow_Extra_Payments_toggled(bool arg1)
{
    bShowExtraPayments = arg1;
    on_pushButton_clicked();
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    if(arg1 == "")
        this->setWindowTitle("Mode RN - Mortgage Calculator");
    else
        this->setWindowTitle(arg1);
}


