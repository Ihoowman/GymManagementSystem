#include "hoomanform.h"
#include "ui_hoomanform.h"

hoomanForm::hoomanForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hoomanForm)
{
    ui->setupUi(this);
}

hoomanForm::~hoomanForm()
{
    delete ui;
}
