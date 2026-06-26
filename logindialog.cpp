#include "logindialog.h"
#include "ui_logindialog.h"
#include "memberpage.h"
#include <QDialog>
#include "receptionistpagedialog.h"
#include "trainerpagedialog.h"
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_2_clicked()
{
    this->reject();

    MemberPage memberPage(this);
    memberPage.exec();
}



void LoginDialog::on_pushButton_clicked()
{
    this->reject();

    ReceptionistPageDialog x;
    x.exec();
}

void LoginDialog::on_pushButton_3_clicked()
{
    this->reject();

    trainerPageDialog y(this);
    y.exec();
}
