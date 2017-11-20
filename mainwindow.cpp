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
    m_Mort.enterAnualInterestRate(ui->InterestRate->value() );
    m_Mort.enterNumOfPayments(ui->NumOfPayments->value() );
    //m_Mort.enterPrincipal(ui->lineEdit-> );

    double dTemp = m_Mort.getMonthlyPayment();
    ui->lineEditMonthlyPayment->setText(doubleToCurrency(m_Mort.getMonthlyPayment(),2 , US_DOLLARS ) );
    ui->AmountofInterest->setText( doubleToCurrency (m_Mort.getInterestPaid(), 0, US_DOLLARS)    );
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
