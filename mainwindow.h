#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mortgagecalc.h"
#include "mattcalculations.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_NumOfYears_valueChanged(int arg1);

    void on_NumOfPayments_valueChanged(int arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_InterestRate_valueChanged(double arg1);

    void on_InterestRate_editingFinished();

    //void on_lineEditMonthlyPayment_textChanged(const QString &arg1);

    void on_lineEditMonthlyPayment_editingFinished();

    void on_lineEditDownPayment_textChanged(const QString &arg1);

    void on_lineEditPrice_textChanged(const QString &arg1);

    void on_doubleSpinBoxDownPaymentPercent_valueChanged(double arg1);

    void on_doubleSpinBoxMillRate_valueChanged(double arg1);

    //void on_checkBox_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::MainWindow *ui;

    MortgageCalc m_Mort;

};

#endif // MAINWINDOW_H
