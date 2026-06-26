#include "welcometrainerdialog2.h"
#include "ui_welcometrainerdialog2.h"

WelcomeTrainerDialog2::WelcomeTrainerDialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeTrainerDialog2)
{
    ui->setupUi(this);
}

WelcomeTrainerDialog2::~WelcomeTrainerDialog2()
{
    delete ui;
}
