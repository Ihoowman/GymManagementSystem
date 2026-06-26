#include "trainerpagedialog.h"
#include "ui_trainerpagedialog.h"
#include <QKeyEvent>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include "welcometrainerdialog.h"
#include "trainerdialog.h"
#include "trainerdialog2.h"
trainerPageDialog::trainerPageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::trainerPageDialog)
  {
      ui->setupUi(this);

      setWindowFlags(windowFlags() &
                     ~Qt::WindowContextHelpButtonHint);

      setWindowTitle("TRAINER LOGIN");
      setWindowIcon(QIcon(":/icons/FILES/LOGO.png"));
  }
void trainerPageDialog::on_pushButton_clicked()
{
    QString email =
        ui->emailLineEdit->text().trimmed();

    QString password =
        ui->passwordLineEdit->text();

    if(email.isEmpty())
    {
        QMessageBox::warning(
            this,
            "ERROR",
            "Please enter your email."
        );
        return;
    }

    if(password.isEmpty())
    {
        QMessageBox::warning(
            this,
            "ERROR",
            "Please enter your password."
        );
        return;
    }

    const QString trainerEmail =
        "shayan@gmail.com";

    const QString trainerPassword =
        "nomre200bede";
    const QString trainer2Email =
        "mehrzad@gmail.com";

    const QString trainer2Password =
        "nomre200bede";
    WelcomeTrainerDialog welcome;

    if(email==trainerEmail){
        if(password==trainerPassword){
            welcome.setName("SHAYAN!!");
            this->reject();
            welcome.exec();

            TrainerDialog x;
            x.exec();

            accept();
        }
        else{
            QMessageBox::warning(
                this,
                "ACCESS DENIED",
                "Wrong password."
            );
            return;
        }

    }
    else if (email==trainer2Email){
        if(password==trainer2Password){
            welcome.setName("MEHRZAD!!");
            this->reject();
            welcome.exec();

            TrainerDialog2 x;
            x.exec();

            accept();
        }
        else{
            QMessageBox::warning(
                this,
                "ACCESS DENIED",
                "Wrong password."
            );
            return;
        }
    }
    else{
        QMessageBox::warning(
            this,
            "ACCESS DENIED",
            "Invalid trainer email."
        );
        return;
    }
}
trainerPageDialog::~trainerPageDialog()
{
    delete ui;
}

