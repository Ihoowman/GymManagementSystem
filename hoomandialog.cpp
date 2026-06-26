#include "hoomandialog.h"
#include "ui_hoomandialog.h"

HoomanDialog::HoomanDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HoomanDialog)
{
    ui->setupUi(this);
}

HoomanDialog::~HoomanDialog()
{
    delete ui;
}
