#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calculatemillratedialog.h"
#include "calculateothermonthlyexpensesdialog.h"

#include "mortgagecalc.h"
#include "../../Matts_Software/General_Library/mattcalculations.h"
#include "aboutdialog.h"

#define CURRENT_VERSION "1.2.0_Beta_1"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void enterCalculatedMonthlyExpenses(double dMonthlyEpenses);
    void refreshFields();
    void updateMillRate();
    void setupCalcFromMonthlyPaymentGUI();
    void setupCalcFromPercentGUI();
    void setupAmortizationTableAndExtraPaymentsGUI();
    void showOrHideCalcFromMontlyPayment();

private slots:
    void on_actionTitle_Block_toggled(bool arg1);
    void on_actionShow_Mortgage_Terms_toggled(bool arg1);
    void on_actionShow_Amortization_Shedule_toggled(bool arg1);
    void on_actionShow_Extra_Payments_toggled(bool arg1);
    void on_actionShow_Payment_Statistics_toggled(bool arg1);

    void on_lineEdit_TitleBlock_textChanged(const QString &arg1);
    void on_checkBoxCalcFromMonthlyPayment_clicked(bool checked);
    void on_checkBox_clicked(bool checked);

    void on_lineEditPrice_textChanged();
    void on_lineEditPrice_editingFinished();

    void on_lineEditDownPayment_textChanged();
    void on_lineEditDownPayment_editingFinished();
    void on_doubleSpinBoxDownPaymentPercent_valueChanged();
    void on_doubleSpinBoxDownPaymentPercent_editingFinished();

    void on_lineEdit_textChanged();
    void on_lineEdit_editingFinished();

    void on_NumOfYears_valueChanged();
    void on_NumOfYears_editingFinished();
    void on_NumOfPayments_valueChanged(int arg1);
    void on_NumOfPayments_editingFinished();

    void on_InterestRate_valueChanged();
    void on_InterestRate_editingFinished();

    void on_doubleSpinBoxMillRate_valueChanged();
    void on_doubleSpinBoxMillRate_editingFinished();

    void on_lineEditOtherMonthly_editingFinished();

    void on_lineEditMonthlyPayment_textChanged(const QString &arg1);
    void on_lineEditMonthlyPayment_editingFinished();

    void on_pushButtonClearExtraPayments_clicked();

    void on_spinBoxExtraPaymentNum_valueChanged();
    void on_spinBoxExtraPaymentNum_editingFinished();

    void on_lineEditExtraPayAmount_editingFinished();

    void on_spinBoxRecurringExtraStartPoint_valueChanged(int arg1);
    void on_spinBoxRecurringExtraStartPoint_editingFinished();

    void on_lineEditRecurringExtraAmount_editingFinished();

    void on_spinBoxRecurringExtraStop_valueChanged(int arg1);   
    void on_spinBoxRecurringExtraStop_editingFinished();

    void on_spinBoxPaymentOffset_valueChanged();
    void on_spinBoxPaymentOffset_editingFinished();

    void on_actionReset_All_triggered();





    void on_actionCalculate_Mill_Rate_triggered();

    void on_actionCalculate_Other_Monthly_Expenses_triggered();

    void on_actionAbout_triggered();

    void on_actionAlways_On_Top_toggled(bool arg1);





    void on_payStatYearSpinBox_editingFinished();

    void on_payStatYearSpinBox_valueChanged();



    void on_payStatPaymentSpinBox_valueChanged();

    void on_payStatPaymentSpinBox_editingFinished();

private:
    Ui::MainWindow *ui;

    MortgageCalc m_Mort;

     double m_dCalculatedMonthlyExpenses = 0;
    CalculateOtherMonthlyExpensesDialog  *m_cMontlyCosts = 0 ;

    double m_dTotalIntrestPaid = 0;

    bool bShowTitleBlock = false;

    void showMortgageTerms();
    void hideMortgageTerms();
    bool bShowMortgageTerms = true;

    void showAmortizationSchedule();
    void hideAmortizationSchedule();  
    bool bShowTable = false;

    void showExtraPayments();
    void hideExtraPayments();
    bool bShowExtraPayments = false;

    void showPaymentStatistics();
    void hidePaymentStatistics();
    bool bShowPaymentStatistics = false;

    void refreshPayStats();
    void setMaxMinForPayStats();

};

#endif // MAINWINDOW_H
