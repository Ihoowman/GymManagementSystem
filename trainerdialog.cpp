#include "trainerdialog.h"
#include "ui_trainerdialog.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDate>
#include <QRandomGenerator>
#include "Member.h"
#include "clientseditdialog.h"

TrainerDialog::TrainerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrainerDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt:: WindowContextHelpButtonHint);

    ui->label_39->setPixmap(
        QPixmap(":/icons/FILES/LOGO.png")
        .scaled(220,78,Qt::KeepAspectRatio,Qt::SmoothTransformation)
    );

    QFile file("users.json");
    QJsonArray users;

    if (file.open(QIODevice::ReadOnly))
    {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        users = doc.array();

    }

    int numClients = 0;

    for(const QJsonValue &val: users){
        QJsonObject user= val.toObject();
        QString trainer= user.value("PAYMENT_HISTORY").toArray().last().toObject().value("TRAINER").toString();
        if (trainer.contains("Shayan")){
            numClients++;
        }
    }


    file.close();

    quint32 seed = QDate::currentDate().toJulianDay();
    QRandomGenerator rng(seed+1);


    ui->lcdNumber_5->display(numClients);
    ui->lcdNumber_6->display(rng.bounded(1,6));

    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, [=]{
        search();
    });
    connect(ui->comboBox_7, &QComboBox::currentTextChanged, this, [=]{
        search();
    });
    connect(ui->comboBox_8, &QComboBox::currentTextChanged, this, [=]{
        search();
    });
    connect(ui->listWidget_3,
            &QListWidget::itemDoubleClicked,
            this,
            [=](QListWidgetItem *item){

        Member *member =
                item->data(Qt::UserRole).value<Member*>();

        if(member){
            ClientsEditDialog dlg(member,this);
            dlg.exec();
        }
    });
    search();
}
TrainerDialog::~TrainerDialog()
{
    delete ui;
}
void TrainerDialog::search()
{
    ui->listWidget_3->clear();

    QFile file("users.json");
    QJsonArray users;

    if(file.open(QIODevice::ReadOnly))
    {
        QJsonDocument doc =
            QJsonDocument::fromJson(file.readAll());

        users = doc.array();
        file.close();
    }

    QString searchTerm =
        ui->lineEdit_3->text().trimmed();

    int planTypeIndex =
        ui->comboBox_7->currentIndex();

    int genderIndex =
        ui->comboBox_8->currentIndex();

    for(const QJsonValue &val : users)
    {
        QJsonObject user = val.toObject();

        QJsonArray history =
            user.value("PAYMENT_HISTORY").toArray();

        if(history.isEmpty())
            continue;

        QString trainer =
            history.last()
            .toObject()
            .value("TRAINER")
            .toString();

        bool trainerCondition =
            trainer.contains("Shayan");

        QString userPlanType =
            user.value("MEMBERSHIP_TYPE").toString();

        bool planType = true;

        switch(planTypeIndex)
        {
        case 1:
            planType = userPlanType.contains("Basic");
            break;

        case 2:
            planType = userPlanType.contains("Silver");
            break;

        case 3:
            planType = userPlanType.contains("Gold");
            break;
        }

        QString userGender =
            user.value("GENDER").toString();

        bool gender = true;

        switch(genderIndex)
        {
        case 1:
            gender = userGender.contains("MALE");
            break;

        case 2:
            gender = userGender.contains("FEMALE");
            break;
        }

        bool searchTermCondition =
            searchTerm.isEmpty()
            ||
            user.value("FULL NAME")
            .toString()
            .toLower()
            .contains(searchTerm.toLower());

        if(trainerCondition &&
           planType &&
           gender &&
           searchTermCondition)
        {
            Member *member =
                new Member(
                    0,
                    user.value("FULL NAME").toString(),
                    user.value("NUMBER").toString(),
                    user.value("EMAIL").toString(),
                    user.value("MEMBER_ID").toString(),
                    user.value("ADDRESS").toString(),
                    user.value("MEMBER_SINCE").toString()
                );

            QListWidgetItem *item =
                new QListWidgetItem(
                    user.value("FULL NAME").toString()
                );

            item->setData(
                Qt::UserRole,
                QVariant::fromValue(member)
            );

            ui->listWidget_3->addItem(item);
        }
    }
}
