#include "welcomereceptionistdialog.h"
#include "ui_welcomereceptionistdialog.h"
#include <QTimer>
#include "receptionistdialog.h"
#include "membermaindialog.h"
//#include "trainerdialog.h"
#include "welcomereceptionistdialog.h"
#include <QRandomGenerator>
#include "receptionistdialog.h"
WelcomereceptionistDialog::WelcomereceptionistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomereceptionistDialog)
{
    ui->setupUi(this);
    QStringList quotes;
    setWindowFlags(windowFlags() & ~Qt:: WindowContextHelpButtonHint);
    setWindowFlags(windowFlags() & ~Qt:: WindowCloseButtonHint);


    quotes << "YOU'RE THE REAL G.O.A.T"
           << "EVERYONE WANTS TO BE LIKE YOU"
           << "THEY CAN'T BEAT YOU"
           << "G.O.A.T"
           << "LEAVE IRAN, CHASE YOUR DREAM"
           << "THEY LOVE YOU"
           << "YOU ARE SPECIAL BELIEVE ME";
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

WelcomereceptionistDialog::~WelcomereceptionistDialog()
{
    delete ui;
}

