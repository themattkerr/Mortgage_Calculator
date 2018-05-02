#include "calculateothermonthlyexpensesdialog.h"
#include "ui_calculateothermonthlyexpensesdialog.h"

#include "mainwindow.h"

CalculateOtherMonthlyExpensesDialog::CalculateOtherMonthlyExpensesDialog(QWidget *parent, double *dMontlyExps) :
    QDialog(parent),
    ui(new Ui::CalculateOtherMonthlyExpensesDialog)
{
    ui->setupUi(this);
    pnt_dTotalMontlyExpenses = dMontlyExps;

    m_Parent = qobject_cast<MainWindow*>(parent);


    Qt::WindowFlags flags = this->windowFlags();
    this->setWindowFlags(flags|Qt::WindowStaysOnTopHint);

    refreshFields();
}

CalculateOtherMonthlyExpensesDialog::~CalculateOtherMonthlyExpensesDialog()
{
    delete ui;
}

void CalculateOtherMonthlyExpensesDialog::on_M1_lineEdit_editingFinished()
{
    refreshFields();
}

void CalculateOtherMonthlyExpensesDialog::on_M2_lineEdit_editingFinished()
{
    refreshFields();
}

void CalculateOtherMonthlyExpensesDialog::on_M3_lineEdit_editingFinished()
{
    refreshFields();
}

void CalculateOtherMonthlyExpensesDialog::on_M4_lineEdit_editingFinished()
{
    refreshFields();
}

void CalculateOtherMonthlyExpensesDialog::on_M5_lineEdit_editingFinished()
{
    refreshFields();
}

void CalculateOtherMonthlyExpensesDialog::on_M6_lineEdit_editingFinished()
{
    refreshFields();
}

void CalculateOtherMonthlyExpensesDialog::on_M7_lineEdit_editingFinished()
{
    refreshFields();
}

void CalculateOtherMonthlyExpensesDialog::on_A1_lineEdit_editingFinished()
{
    refreshFields();
}

void CalculateOtherMonthlyExpensesDialog::on_A2_lineEdit_editingFinished()
{
    refreshFields();
}

void CalculateOtherMonthlyExpensesDialog::on_A3_lineEdit_editingFinished()
{
    refreshFields();
}
void CalculateOtherMonthlyExpensesDialog::refreshFields()
{
    ui->M1_lineEdit->setText( doubleToCurrency( usDollarsStringToDouble(ui->M1_lineEdit->text()),2,US_DOLLARS));
    ui->M2_lineEdit->setText( doubleToCurrency( usDollarsStringToDouble(ui->M2_lineEdit->text()),2,US_DOLLARS));
    ui->M3_lineEdit->setText( doubleToCurrency( usDollarsStringToDouble(ui->M3_lineEdit->text()),2,US_DOLLARS));
    ui->M4_lineEdit->setText( doubleToCurrency( usDollarsStringToDouble(ui->M4_lineEdit->text()),2,US_DOLLARS));
    ui->M5_lineEdit->setText( doubleToCurrency( usDollarsStringToDouble(ui->M5_lineEdit->text()),2,US_DOLLARS));
    ui->M6_lineEdit->setText( doubleToCurrency( usDollarsStringToDouble(ui->M6_lineEdit->text()),2,US_DOLLARS));
    ui->M7_lineEdit->setText( doubleToCurrency( usDollarsStringToDouble(ui->M7_lineEdit->text()),2,US_DOLLARS));

    ui->A1_lineEdit->setText( doubleToCurrency( usDollarsStringToDouble(ui->A1_lineEdit->text()),2,US_DOLLARS));
    ui->A2_lineEdit->setText( doubleToCurrency( usDollarsStringToDouble(ui->A2_lineEdit->text()),2,US_DOLLARS));
    ui->A3_lineEdit->setText( doubleToCurrency( usDollarsStringToDouble(ui->A3_lineEdit->text()),2,US_DOLLARS));



    m_dTotalMontlyEpenses =
    usDollarsStringToDouble(ui->M1_lineEdit->text()) +
    usDollarsStringToDouble(ui->M2_lineEdit->text()) +
    usDollarsStringToDouble(ui->M3_lineEdit->text()) +
    usDollarsStringToDouble(ui->M4_lineEdit->text()) +
    usDollarsStringToDouble(ui->M5_lineEdit->text()) +
    usDollarsStringToDouble(ui->M6_lineEdit->text()) +
    usDollarsStringToDouble(ui->M7_lineEdit->text()) +
    ((
        usDollarsStringToDouble(ui->A1_lineEdit->text()) +
        usDollarsStringToDouble(ui->A2_lineEdit->text()) +
        usDollarsStringToDouble(ui->A3_lineEdit->text())
                )/12);

    ui->totalMontlyExpensesLabel->setText(doubleToCurrency(m_dTotalMontlyEpenses,2,US_DOLLARS));
}

void CalculateOtherMonthlyExpensesDialog::on_buttonBox_accepted()
{
    *pnt_dTotalMontlyExpenses = m_dTotalMontlyEpenses;

    ((MainWindow*)parentWidget())->enterCalculatedMonthlyExpenses(m_dTotalMontlyEpenses);
    ((MainWindow*)parentWidget())->refreshFields();
}

void CalculateOtherMonthlyExpensesDialog::keyPressEvent(QKeyEvent *evt)
{
    if((evt->key() == Qt::Key_Enter) || (evt->key() == Qt::Key_Return))
        return;
    QDialog::keyPressEvent(evt);
}

void CalculateOtherMonthlyExpensesDialog::on_clearAllPushButton_clicked()
{
    resetAll();
}

 void CalculateOtherMonthlyExpensesDialog::resetAll()
 {
     ui->M1_lineEdit->setText("0");
     ui->M2_lineEdit->setText("0");
     ui->M3_lineEdit->setText("0");
     ui->M4_lineEdit->setText("0");
     ui->M5_lineEdit->setText("0");
     ui->M6_lineEdit->setText("0");
     ui->M7_lineEdit->setText("0");

     ui->A1_lineEdit->setText("0");
     ui->A2_lineEdit->setText("0");
     ui->A3_lineEdit->setText("0");

     ui->lineEdit_10->setText("");
     ui->lineEdit_11->setText("");
     ui->lineEdit_12->setText("");
     ui->lineEdit_13->setText("");
     ui->lineEdit_14->setText("");


     refreshFields();
 }
