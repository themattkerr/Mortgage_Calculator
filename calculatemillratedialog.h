#ifndef CALCULATEMILLRATEDIALOG_H
#define CALCULATEMILLRATEDIALOG_H

#include <QDialog>

#include "../../Matts_Software/General_Library/mattcalculations.h"


namespace Ui {
class CalculateMillRateDialog;
}

class CalculateMillRateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalculateMillRateDialog(QWidget *parent = 0, double *dMillRate = 0);
    ~CalculateMillRateDialog();

private slots:


    void on_annualTaxAmountLineEdit_textChanged(const QString &arg1);

    void on_assessedValueLineEdit_textChanged(const QString &arg1);

    void refreshFields();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CalculateMillRateDialog *ui;

    const double dMillRateMultiplier = 1000;
    double *m_dptrMillRate = 0;
    double m_dTempMillRate = 0;
    double m_dAnnualTaxAmount = 0;
    double m_dAssesedValue = 0;
};

#endif // CALCULATEMILLRATEDIALOG_H
