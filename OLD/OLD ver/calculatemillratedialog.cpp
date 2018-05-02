#include "calculatemillratedialog.h"
#include "ui_calculatemillratedialog.h"

#include "mainwindow.h"

CalculateMillRateDialog::CalculateMillRateDialog(QWidget *parent, double *dMillRate) :
    QDialog(parent),
    ui(new Ui::CalculateMillRateDialog)
{
    ui->setupUi(this);
    m_dptrMillRate = dMillRate;

    Qt::WindowFlags flags = this->windowFlags();
    this->setWindowFlags(flags|Qt::WindowStaysOnTopHint);

    refreshFields();
}

CalculateMillRateDialog::~CalculateMillRateDialog()
{
    delete ui;
}

void CalculateMillRateDialog::on_annualTaxAmountLineEdit_textChanged(const QString &arg1)
{
    m_dAnnualTaxAmount = usDollarsStringToDouble(arg1);
    refreshFields();
}

void CalculateMillRateDialog::on_assessedValueLineEdit_textChanged(const QString &arg1)
{
    m_dAssesedValue = usDollarsStringToDouble(arg1);
    refreshFields();
}

void CalculateMillRateDialog::refreshFields()
{
    if(m_dAssesedValue > 0 && m_dAnnualTaxAmount < m_dAssesedValue )
        m_dTempMillRate = ((m_dAnnualTaxAmount / m_dAssesedValue)*dMillRateMultiplier);
    else
        m_dTempMillRate = 0;

    ui->annualTaxAmountLineEdit->setText(doubleToCurrency(m_dAnnualTaxAmount, 0, US_DOLLARS) );
    ui->assessedValueLineEdit->setText(doubleToCurrency(m_dAssesedValue,0,US_DOLLARS));
    ui->calculatedMillRateLabel->setText(addCommasToDouble((m_dTempMillRate),3));

}

void CalculateMillRateDialog::on_buttonBox_accepted()
{
    *m_dptrMillRate = m_dTempMillRate;
//    ((MainWindow*)parentWidget())
    this->close();
}

void CalculateMillRateDialog::on_buttonBox_rejected()
{
    *m_dptrMillRate = -1;
    this->close();
}
