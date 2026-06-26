#include "welcometrainerdialog.h"
#include "ui_welcometrainerdialog.h"
#include <QTimer>
#include "membermaindialog.h"
//#include "trainerdialog.h"
#include <QRandomGenerator>
WelcomeTrainerDialog::WelcomeTrainerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeTrainerDialog)
{
    ui->setupUi(this);
    QStringList quotes;
    setWindowFlags(windowFlags() & ~Qt:: WindowContextHelpButtonHint);
    setWindowFlags(windowFlags() & ~Qt:: WindowCloseButtonHint);


    quotes << "YOU'RE NOT THE REAL G.O.A.T WITHOUT TRAINER"
           << "FAT HATER GYM = THE BEST OF THE BESTS"
           << "SUCCESS = IMMIGRATION "
           << "G.O.A.T"
           << "LEAVE IRAN, CHASE YOUR DREAM"
           <<"I'M THE BEST TRAINER OF ALL TIME"
           << "WITHOUT TRAINER YOU'RE TOTALLY NOTHING!";
    ui->expressionLabel->setStyleSheet(
        "color: #FFFF00;"
        "font-size: 14pt;"
        "font-weight: bold;"
    );

    int index = QRandomGenerator::global()->bounded(quotes.size());

    ui->expressionLabel->setText(
        "\"" + quotes[index] + "\""
    );

    QTimer::singleShot(5000, this, &QDialog::accept);
}

WelcomeTrainerDialog::~WelcomeTrainerDialog()
{
    delete ui;
}
void WelcomeTrainerDialog::setName(const QString &name)
{
    ui->nameLabel->setText(name);
    ui->nameLabel->setStyleSheet(
        "color: #FFFF00;"
        "font-size: 16pt;"
        "font-weight: bold;"
    );
}
