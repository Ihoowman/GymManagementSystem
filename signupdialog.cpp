#include "signupdialog.h"
#include "ui_signupdialog.h"
#include <QColor>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "sgnupdonedialog.h"
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QRegularExpressionValidator>
#include <QSet>
#include <QRandomGenerator>
#include <QDateTime>
QString generateUniqueMemberId()
{
    QFile file("users.json");
    QJsonArray users;

    if (file.open(QIODevice::ReadOnly))
    {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        users = doc.array();
        file.close();
    }

    QSet<QString> existingIds;

    for (const QJsonValue &value : users)
    {
        QJsonObject obj = value.toObject();
        existingIds.insert(obj["MEMBER_ID"].toString());
    }

    QString newId;

    do {
        newId = "#" + QString::number(
            QRandomGenerator::global()->bounded(100000, 999999)
        );
    } while (existingIds.contains(newId));

    return newId;
}
SignupDialog::SignupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignupDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt:: WindowContextHelpButtonHint);
    QRegularExpression rx("^9\\d{9}$");
    ui->numberEdit->setValidator(
        new QRegularExpressionValidator(rx, this)
    );
    this->resize(900, 650);
}
SignupDialog::~SignupDialog()
{
    delete ui;
}
void SignupDialog::on_expandButton_clicked()
{
    if(isExpanded == false)
     {
         this->setFixedSize(700,600);

         ui->expandButton->setText("-");

         isExpanded = true;
     }
     else
     {
         this->setFixedSize(600, 470);

         ui->expandButton->setText("+");

         isExpanded = false;
     }
}
void SignupDialog::on_loginLinkButton_clicked()
{
    reject();
}

void SignupDialog::on_signupButton_clicked()
{
    if (!ui->fullNameEdit->text().isEmpty())
    {
        if (!ui->emailEdit->text().isEmpty())
        {
            if (!ui->addressEdit->toPlainText().isEmpty())
            {
                if (!ui->numberEdit->text().isEmpty())
                {
                    if(ui->radioButtonMale->isChecked() ||
                                       ui->radioButtonFemale->isChecked())
                    {
                    QFile file("users.json");

                    QJsonArray users;

                    if(file.open(QIODevice::ReadOnly))
                    {
                        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
                        users = doc.array();
                        file.close();
                    }

                    QJsonObject user;
                    user["FULL NAME"] = ui->fullNameEdit->text();
                    user["EMAIL"] = ui->emailEdit->text();
                    user["ADDRESS"] = ui->addressEdit->toPlainText();
                    user["NUMBER"] = ui->numberEdit->text();
                    user["MEMBER_ID"] = generateUniqueMemberId();
                    user["HAS_MEMBERSHIP"] = false;
                    user["SESSIONS_USED"] = 0;
                    user["SESSIONS_LEFT"] = 0;
                    user["TOTAL_SESSIONS"] = 0;
                    user["WORKOUT_PLAN"] = 0;
                    user["DIET_PLAN"] = 0;
                    QString gender;

                    if(ui->radioButtonMale->isChecked())
                    {
                        gender = "MALE";
                    }
                    else if(ui->radioButtonFemale->isChecked())
                    {
                        gender = "FEMALE";
                    }

                    user["GENDER"] = gender;
                    user["LAST_SESSION_UPDATE"] =
                        QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
                    user["ACTIVITY_LOG"] = QJsonArray();
                    QString now = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
                    user["MEMBER_SINCE"] = now;
                    for(const QJsonValue &value : users)
                    {
                        QJsonObject existingUser = value.toObject();

                        if(existingUser["EMAIL"].toString() ==
                           ui->emailEdit->text())
                        {
                            QMessageBox::warning(
                                this,
                                "EMAIL EXISTS",
                                "This email is already registered."
                            );
                            return;
                        }
                    }
                    users.append(user);

                    if(file.open(QIODevice::WriteOnly))
                    {
                        QJsonDocument doc(users);
                        file.write(doc.toJson());
                        file.close();
                    }

                    reject();

                    SgnupDoneDialog x;
                    x.exec();
                    }
                    else
                    {
                        QMessageBox::warning(this,    "GENDER",
                                             "Please select Male or Female.");
                    }
                }
                else
                {
                    QMessageBox::warning(this,"EMPTY BAHOOSH",
                                         "FILL THOSE FORMS");
                }
            }
            else
            {
                QMessageBox::warning(this,"EMPTY BAHOOSH",
                                     "FILL THOSE FORMS");
            }
        }
        else
        {
            QMessageBox::warning(this,"EMPTY BAHOOSH",
                                 "FILL THOSE FORMS");
        }
    }
    else
    {
        QMessageBox::warning(this,"EMPTY BAHOOSH",
                             "FILL THOSE FORMS");
    }
}
