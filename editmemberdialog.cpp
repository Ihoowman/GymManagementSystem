#include "editmemberdialog.h"
#include "ui_editmemberdialog.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
EditMemberDialog::EditMemberDialog(Member *member, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMemberDialog),
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
    connect(ui->buttonBox,
            &QDialogButtonBox::accepted,
            this,
            &EditMemberDialog::saveChanges);
}
void EditMemberDialog::saveChanges()
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
EditMemberDialog::~EditMemberDialog()
{
    delete ui;
}
