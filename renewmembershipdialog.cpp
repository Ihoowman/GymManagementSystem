#include "renewmembershipdialog.h"
#include "ui_renewmembershipdialog.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QDateTime>
#include "fakedialog.h"

RenewMembershipDialog::RenewMembershipDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::RenewMembershipDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    connect(ui->pushButton, &QPushButton::clicked, this, [=]() {

        if(ui->comboBox->currentIndex() == 0) {
            QMessageBox::warning(this, "Error", "Select session plan");
            return;
        }
    });
    ui->comboBox->addItem("Choose your plan");
    ui->comboBox->addItem("🥉Basic - 12 Sessions", 16000000);
    ui->comboBox->addItem("🥈Silver- 20 Sessions",19500000);
    ui->comboBox->addItem("🥇Gold  - 30 Sessions" ,26000000);
    ui->comboBox_2->addItem("Choose your plan");
    ui->comboBox_2->addItem("😪 NO TRAINER",0);
    ui->comboBox_2->addItem("🙂 Mehrzad Shahcheraqian",4000000);
    ui->comboBox_2->addItem("🥶 Shayan Shahamiri",6000000);
    connect(ui->comboBox, &QComboBox::currentTextChanged,
            this, [this](const QString &) {
                updatePrice();
            });

    connect(ui->comboBox_2, &QComboBox::currentTextChanged,
            this, [this](const QString &) {
                updatePrice();
            });

    connect(ui->pushButton, &QPushButton::clicked, this, [=]() {

        QString plan = ui->comboBox->currentText();

        if(plan == "Choose your plan") {
            QMessageBox::warning(this, "Error", "Select a plan first");
            return;
        }
    });
}
RenewMembershipDialog::~RenewMembershipDialog()
{
    delete ui;
}

void RenewMembershipDialog::setEmail(const QString &email)
{
    currentEmail = email;
}

void RenewMembershipDialog::applyMembership(const QString &plan)
{
    QFile file("users.json");

    if(!file.open(QIODevice::ReadOnly))
        return;

    QJsonArray users = QJsonDocument::fromJson(file.readAll()).array();
    file.close();

    int sessions = 0;

    if(plan.contains("Basic")) sessions = 10;
    else if(plan.contains("Silver")) sessions = 20;
    else if(plan.contains("Gold")) sessions = 30;

    for(int i = 0; i < users.size(); i++)
    {
        QJsonObject u = users[i].toObject();

        if(u["EMAIL"].toString() == currentEmail)
        {
            u["HAS_MEMBERSHIP"] = true;
            u["MEMBERSHIP_TYPE"] = plan;
            u["TOTAL_SESSIONS"] = sessions;
            u["SESSIONS_LEFT"] = sessions;
            u["MEMBER_SINCE"] =
                QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

            users[i] = u;
            break;
        }
    }

    QFile w("users.json");
    if(w.open(QIODevice::WriteOnly))
        w.write(QJsonDocument(users).toJson());
}
void RenewMembershipDialog::saveToJson(
        const QString &plan,
        const QString &trainer,
        int sessions)
{
    QFile file("users.json");

    if(!file.open(QIODevice::ReadOnly))
        return;

    QJsonArray users =
        QJsonDocument::fromJson(file.readAll()).array();

    file.close();

    for(int i = 0; i < users.size(); i++)
    {
        QJsonObject user = users[i].toObject();

        if(user["EMAIL"].toString() == currentEmail)
        {
            user["TRAINER_NAME"] = trainer;

            user["LAST_PAYMENT"] = totalPrice;

            user["LAST_PAYMENT_DATE"] =
                    QDateTime::currentDateTime()
                    .toString("yyyy-MM-dd HH:mm:ss");

            QJsonArray history =
                    user["PAYMENT_HISTORY"].toArray();

            QJsonObject payment;

            payment["PLAN"] = plan;
            payment["TRAINER"] = trainer;
            payment["PRICE"] = totalPrice;
            payment["SESSIONS"] = sessions;
            payment["DATE"] =
                    QDateTime::currentDateTime()
                    .toString("yyyy-MM-dd HH:mm:ss");

            history.append(payment);

            user["PAYMENT_HISTORY"] = history;

            users[i] = user;

            break;
        }
    }

    QFile saveFile("users.json");

    if(saveFile.open(QIODevice::WriteOnly))
    {
        saveFile.write(
            QJsonDocument(users).toJson()
        );

        saveFile.close();
    }
}
void RenewMembershipDialog::on_pushButton_clicked()
{
    QString plan = ui->comboBox->currentText();

    FakeDialog dlg(plan, totalPrice, this);

    connect(&dlg,&FakeDialog::paymentSuccess,
            this,
            [=](QString selectedPlan)
    {
        applyMembership(selectedPlan);
        QString trainer =
                    ui->comboBox_2->currentText();

            int sessions = 0;

            if(selectedPlan.contains("Basic"))
                sessions = 12;
            else if(selectedPlan.contains("Silver"))
                sessions = 20;
            else if(selectedPlan.contains("Gold"))
                sessions = 30;

            saveToJson(
                selectedPlan,
                trainer,
                sessions
            );
        QMessageBox::information(
                    this,
                    "Success",
                    "Membership activated successfully!");

        accept();
    });

    dlg.exec();
}
void RenewMembershipDialog::updatePrice()
{
    sessionPrice = ui->comboBox->currentData().toInt();
    trainerPrice = ui->comboBox_2->currentData().toInt();

    totalPrice = sessionPrice + trainerPrice;

    ui->labelSessionsPrice->setText("Sessions: " + QString::number(sessionPrice) + " RIAL");
    ui->labelTrainerPrice->setText("Trainer: " + QString::number(trainerPrice) + " RIAL");
    ui->labelTotalPrice->setText("TOTAL: " + QString::number(totalPrice) + " RIAL");
}
