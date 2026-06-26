#include "receptionistpagedialog.h"
#include "ui_receptionistpagedialog.h"
#include "signupdialog.h"
#include <QKeyEvent>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include "otpdialog.h"
#include <QRandomGenerator>
#include "welcomereceptionistdialog.h"
#include "receptionistdialog.h"
ReceptionistPageDialog::ReceptionistPageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceptionistPageDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt:: WindowContextHelpButtonHint);

    ui->lineEdit->setCursorPosition(0);
    this->setWindowTitle("RECEPTIONIST LOGIN");
    this->setWindowIcon(QIcon(":/icons/FILES/LOGO.png"));
}

ReceptionistPageDialog::~ReceptionistPageDialog()
{
    delete ui;
}
void ReceptionistPageDialog::on_pushButton_2_clicked()
{
    QString email = "homanfatemifard@gmail.com";
    if(email != ui->lineEdit->text().trimmed())
    {
        QMessageBox::warning(
            this,
            "ACCESS DENIED",
            "Only the receptionist account can login."
        );
        return;
    }
    WelcomereceptionistDialog x;
    x.exec();

    this->reject();
    ReceptionistDialog y;
    y.exec();
}

