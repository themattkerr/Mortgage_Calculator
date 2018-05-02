#include "aboutdialog.h"
#include "ui_aboutdialog.h"

aboutDialog::aboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);
    this->setWindowTitle( "About"  );
    ui->versionLabel->setText( CURRENT_VERSION );
    ui->mattCalcVerLabel->setText( VERSION_OF_MATTCALCULATIONS );
    ui->MortVerLabel->setText( VERSION_OF_MORTGAGECALC_CLASS );
}

aboutDialog::~aboutDialog()
{
    delete ui;
}
