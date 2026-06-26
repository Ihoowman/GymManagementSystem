#include "receptionistdialog.h"
#include "ui_receptionistdialog.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDateTime>
#include <QComboBox>
#include <QMessageBox>
#include "signupdialog.h"
#include "Member.h"
#include "editmemberdialog.h"


ReceptionistDialog::ReceptionistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceptionistDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt:: WindowContextHelpButtonHint);

    QFile file("users.json");
    QJsonArray users;

    if (file.open(QIODevice::ReadOnly))
    {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        users = doc.array();
        file.close();
    }

    ui->label_29->setText(QString::number(users.size()));
    int todaycheckincount=0;
    int todayrenewcount=0;
    for(const QJsonValue &val: users){
        QJsonObject user = val.toObject();
        QDateTime now = QDateTime :: currentDateTime();

        QDateTime lastLogin =
            QDateTime::fromString(
                user.value("LAST_LOGIN").toString(),
                "yyyy-MM-dd HH:mm:ss"
            );
        if(lastLogin.isValid()){

            if(now.date()==lastLogin.date()){
                todaycheckincount +=1;
            }
        }
        QDateTime lastRenew =
            QDateTime::fromString(
                user.value("PAYMENT_HISTORY").toArray().last().toObject().value("DATE").toString(),
                "yyyy-MM-dd HH:mm:ss"
            );

        if(lastRenew.isValid()){
            if(now.date()==lastRenew.date()){
                todayrenewcount ++;
            }
        }
    }
    ui->label_31->setText(QString::number(todaycheckincount));
    ui->label_33->setText(QString::number(todayrenewcount));
    connect(ui->lineEdit_3, &QLineEdit:: textChanged, this, [=](){
        search();
    });
    connect(ui->comboBox_7, &QComboBox::currentTextChanged, this, [=](){
        search();
    });
    connect(ui->comboBox_8, &QComboBox::currentTextChanged, this, [=](){
        search();
    });
    connect(ui->comboBox_9, &QComboBox::currentTextChanged, this, [=](){
        search();
    });
}

ReceptionistDialog::~ReceptionistDialog()
{
    delete ui;
}
void ReceptionistDialog::search(){
    ui->listWidget_3->clear();

    QFile file("users.json");
    QJsonArray users;

    if (file.open(QIODevice::ReadOnly))
    {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        users = doc.array();
        file.close();
    }
    for(const QJsonValue &val: users){
        QJsonObject user = val.toObject();
        QString searchTerm = ui->lineEdit_3->text().trimmed();
        if(!searchTerm.isEmpty()){
            int planTypeIndex = ui->comboBox_7->currentIndex();
            bool planType;

            QString userplanType = user.value("MEMBERSHIP_TYPE").toString();

            switch(planTypeIndex){

            case 1:{
                planType = userplanType.contains("Basic");
                break;
            }
            case 2:{
                planType = userplanType.contains("Silver");
                break;
            }
            case 3:{
                planType = userplanType.contains("Gold");
                break;
            }
            default: {
                planType = true;
            }
            }

            int genderIndex = ui->comboBox_8->currentIndex();
            bool gender;

            QString userGender= user.value("GENDER").toString();

            switch(genderIndex){

            case 1:{
                gender = userGender.contains("MALE");
                break;
            }
            case 2:{
                gender = userGender.contains("FEMALE");
                break;
            }

            default: {
                gender = true;
            }
            }

            int trainerIndex = ui->comboBox_9->currentIndex();
            bool trainer;

            QString userTrainer= user.value("PAYMENT_HISTORY").toArray().last().toObject().value("TRAINER").toString();

            switch(trainerIndex){

            case 1:{
                trainer = userTrainer.contains("Shayan");
                break;
            }
            case 2:{
                trainer = userTrainer.contains("Mehrzad");
                break;
            }

            default: {
                trainer = true;
            }
            }

            bool searchTermCondition = user.value("MEMBER_ID").toString().contains(searchTerm)||user.value("FULL NAME").toString().toLower().contains(searchTerm.toLower());

            if(searchTermCondition && planType && gender && trainer){
                Member *member= new Member(0, user.value("FULL NAME").toString(),user.value("NUMBER").toString(),
                                           user.value("EMAIL").toString(),user.value("MEMBER_ID").toString(),
                                           user.value("ADDRESS").toString(),user.value("MEMBER_SINCE").toString());
                QListWidgetItem *item = new QListWidgetItem (user.value("FULL NAME").toString());
                item->setData(Qt::ItemDataRole::UserRole,QVariant::fromValue(member));
                ui->listWidget_3->addItem(item);
            }
        }


    }

}

void ReceptionistDialog::on_pushButton_6_clicked()
{
    SignupDialog signup(this);

    signup.exec();

    QFile file("users.json");
    QJsonArray users;

    if(file.open(QIODevice::ReadOnly))
    {
        QJsonDocument doc =
                QJsonDocument::fromJson(
                    file.readAll());

        users = doc.array();

        file.close();
    }

    ui->label_29->setText(
                QString::number(users.size()));
}

void ReceptionistDialog::on_pushButton_5_clicked()
{
    if(!ui->listWidget_3->currentItem())
        return;
    Member *member = ui->listWidget_3->currentItem()->data(Qt::ItemDataRole::UserRole).value<Member*>();
    if (member){
        EditMemberDialog x(member);
        x.exec();
    }
}
