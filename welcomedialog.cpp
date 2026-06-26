#include "welcomedialog.h"
#include "ui_welcomedialog.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QStringList>

WelcomeDialog::WelcomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeDialog)
{
    ui->setupUi(this);
    QStringList quotes;
    setWindowFlags(windowFlags() & ~Qt:: WindowContextHelpButtonHint);
    setWindowFlags(windowFlags() & ~Qt:: WindowCloseButtonHint);


    quotes << "HAVE PAIN WITH GAIN"
           << "EVERYONE HAS PROBLEMS (NOT JUST YOU)"
           << "NEVER PUSH YOUR LIMITS"
           << "YOU'RE JUST A SPOILED CHILD "
           << "SUCCESS IS EARNED UNLESS YOU LIVE IN IRAN"
           << "THEY HATE YOU"
           << "YOU ARE NOTHING SPECIAL BELIEVE ME";
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

WelcomeDialog::~WelcomeDialog()
{
    delete ui;
}

void WelcomeDialog::setName(const QString &name)
{
    ui->nameLabel->setText(
        name.toUpper() + " !!"
    );
    ui->nameLabel->setStyleSheet(
        "color: #FFFF00;"
        "font-size: 14pt;"
        "font-weight: bold;"
    );
}
