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


    void on_NumOfYears_valueChanged(int arg1);

    void on_NumOfPayments_valueChanged(int arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_InterestRate_valueChanged(double arg1);

    void on_InterestRate_editingFinished();



    void on_lineEditMonthlyPayment_editingFinished();

    void on_lineEditDownPayment_textChanged(const QString &arg1);

    void on_lineEditPrice_textChanged(const QString &arg1);

    void on_doubleSpinBoxDownPaymentPercent_valueChanged(double arg1);
    void on_doubleSpinBoxDownPaymentPercent_editingFinished();


    void on_checkBox_clicked(bool checked);

    void on_doubleSpinBoxMillRate_editingFinished();


    void on_lineEditOtherMonthly_editingFinished();

    void on_lineEditExtraPayAmount_editingFinished();



    void on_actionShow_Amortization_Shedule_toggled(bool arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_actionShow_Extra_Payments_toggled(bool arg1);



    void on_pushButtonClearExtraPayments_clicked();

    void on_spinBoxRecurringExtraStartPoint_valueChanged(int arg1);

    void on_spinBoxRecurringExtraStop_valueChanged(int arg1);

    void on_lineEditRecurringExtraAmount_editingFinished();

    void on_checkBoxCalcFromMonthlyPayment_clicked(bool checked);

    void on_spinBoxExtraPaymentNum_valueChanged(int arg1);

    void on_lineEditPrice_editingFinished();



    void on_lineEditDownPayment_editingFinished();

    void on_lineEdit_editingFinished();

    void on_NumOfYears_editingFinished();

    void on_NumOfPayments_editingFinished();

    void on_spinBoxExtraPaymentNum_editingFinished();

    void on_spinBoxRecurringExtraStartPoint_editingFinished();

    void on_spinBoxRecurringExtraStop_editingFinished();

    void on_spinBoxPaymentOffset_editingFinished();

    void on_spinBoxPaymentOffset_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    MortgageCalc m_Mort;

    double m_dTotalIntrestPaid = 0;

//    double calcAnualExpenses();

    void showAmortizationSchedule();
    void hideAmortizationSchedule();  
    bool bShowTable = false;

    void showExtraPayments();
    void hideExtraPayments();
    bool bShowExtraPayments = false;

    void refreshFields();

};

#endif // MAINWINDOW_H
