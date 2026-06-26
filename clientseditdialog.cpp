#include "clientseditdialog.h"
#include "ui_clientseditdialog.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
ClientsEditDialog::ClientsEditDialog(Member *member, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientsEditDialog) ,
    member(member)

{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt:: WindowContextHelpButtonHint);

    ui->lineEdit->setText(member->getName());
    ui->lineEdit_2->setText(member->getEmail());
    ui->lineEdit_3->setText(member->getPhone());
    ui->lineEdit_4->setText(member->getAddress());
    ui->lineEdit_5->setText(member->getMemberId());
    ui->lineEdit_6->setText(member->getMemberSince());
    ui->lineEdit_6->setEnabled(false);
    QFile file("users.json");

    if(file.open(QIODevice::ReadOnly))
    {
        QJsonArray users =
            QJsonDocument::fromJson(file.readAll()).array();

        file.close();

        for(const QJsonValue &val : users)
        {
            QJsonObject user = val.toObject();

            if(user["MEMBER_ID"].toString()
                    == member->getMemberId())
            {
                ui->spinBox->setValue(
                    user["WORKOUT_PLAN"].toInt()
                );

                ui->spinBox_2->setValue(
                    user["DIET_PLAN"].toInt()
                );

                break;
            }
        }
    }
    connect(ui->buttonBox,
            &QDialogButtonBox::accepted,
            this,
            &ClientsEditDialog::saveChanges);
    connect(ui->buttonBox,
            &QDialogButtonBox::rejected,
            this,
            &ClientsEditDialog::reject);
}

ClientsEditDialog::~ClientsEditDialog()
{
    delete ui;
}
void ClientsEditDialog::saveChanges()
{
    QFile file("users.json");

    if(!file.open(QIODevice::ReadOnly))
        return;

    QJsonDocument doc =
            QJsonDocument::fromJson(file.readAll());

    QJsonArray users = doc.array();

    file.close();

    for(int i = 0; i < users.size(); i++)
    {
        QJsonObject user = users[i].toObject();

        if(user["MEMBER_ID"].toString()
                == member->getMemberId())
        {
            user["FULL NAME"] = ui->lineEdit->text();
            user["EMAIL"] = ui->lineEdit_2->text();
            user["NUMBER"] = ui->lineEdit_3->text();
            user["ADDRESS"] = ui->lineEdit_4->text();
            user["WORKOUT_PLAN"] = ui->spinBox->value();
            user["DIET_PLAN"] = ui->spinBox_2->value();

            users[i] = user;

            break;
        }
    }

    if(file.open(QIODevice::WriteOnly))
    {
        QJsonDocument newDoc(users);

        file.write(
            newDoc.toJson(QJsonDocument::Indented));

        file.close();
    }
    member->setName(ui->lineEdit->text());
    member->setPhone(ui->lineEdit_3->text());
    member->setEmail(ui->lineEdit_2->text());
    member->setAddress(ui->lineEdit_4->text());
    accept();
}
