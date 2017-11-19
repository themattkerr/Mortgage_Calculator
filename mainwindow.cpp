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
    m_Mort.enterInterestRate(ui->InterestRate->value() );
    m_Mort.enterNumOfPayments(ui->NumOfPayments->value() );
    m_Mort.enterPrincipal(ui->Principal->value() );

    double dTemp = m_Mort.getMonthlyPayment();
    ui->lineEditMonthlyPayment->setText(QString::number(dTemp));
}
