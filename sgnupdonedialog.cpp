#include "sgnupdonedialog.h"
#include "ui_sgnupdonedialog.h"

SgnupDoneDialog::SgnupDoneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SgnupDoneDialog)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(":/icons/FILES/checkmark.png").scaled(500, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

}

SgnupDoneDialog::~SgnupDoneDialog()
{
    delete ui;
}
