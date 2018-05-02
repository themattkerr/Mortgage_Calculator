#ifndef CALCULATEOTHERMONTHLYEXPENSESDIALOG_H
#define CALCULATEOTHERMONTHLYEXPENSESDIALOG_H

#include <QDialog>
#include <QMainWindow>
//#include "mainwindow.h"
#include <QKeyEvent>

#include "../../Matts_Software/General_Library/mattcalculations.h"

namespace Ui {
class CalculateOtherMonthlyExpensesDialog;
}

class CalculateOtherMonthlyExpensesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalculateOtherMonthlyExpensesDialog(QWidget *parent = 0, double *dMontlyExps = 0);
    ~CalculateOtherMonthlyExpensesDialog();
    void resetAll();

private slots:
    void on_M1_lineEdit_editingFinished();

    void on_M2_lineEdit_editingFinished();

    void on_M3_lineEdit_editingFinished();

    void on_M4_lineEdit_editingFinished();

    void on_M5_lineEdit_editingFinished();

    void on_M6_lineEdit_editingFinished();

    void on_M7_lineEdit_editingFinished();

    void on_A1_lineEdit_editingFinished();

    void on_A2_lineEdit_editingFinished();

    void on_A3_lineEdit_editingFinished();

    void on_buttonBox_accepted();

    void on_clearAllPushButton_clicked();

private:
    Ui::CalculateOtherMonthlyExpensesDialog *ui;
    void refreshFields();

    double *pnt_dTotalMontlyExpenses = 0;
    double m_dTotalMontlyEpenses = 0;

    void keyPressEvent(QKeyEvent *evt);
    QWidget *m_Parent;
};

#endif // CALCULATEOTHERMONTHLYEXPENSESDIALOG_H
