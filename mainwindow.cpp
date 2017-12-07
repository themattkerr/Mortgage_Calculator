#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    ui->lineEditMontlyTax->setText( doubleToCurrency (m_Mort.getMonthlyTaxPayment(), 2, US_DOLLARS ) );
    ui->doubleSpinBoxMillRate->setValue(m_Mort.getMillRate() );

}

void MainWindow::on_NumOfYears_valueChanged(int arg1)
{
    m_Mort.enterNumOfYears(ui->NumOfYears->value() );
    ui->NumOfPayments->setValue(m_Mort.getNumOfPayments()  );
    on_pushButton_clicked();
}

void MainWindow::on_NumOfPayments_valueChanged(int arg1)
{
    m_Mort.enterNumOfPayments(ui->NumOfPayments->value() );
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

        double dTemp = ui->InterestRate->value() / 100;
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
    double dTemp = usDollarsStringToDouble(ui->lineEditDownPayment ->text());
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

void MainWindow::on_doubleSpinBoxMillRate_valueChanged(double arg1)
{
    m_Mort.enterMillRate(arg1);
    on_pushButton_clicked();
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    m_Mort.setDownPaymentCalcFromPercent(checked);
    on_pushButton_clicked();
}
