#include "membermaindialog.h"
#include "ui_membermaindialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QByteArray>
#include <QBuffer>
#include <QDateTime>
#include <QCloseEvent>
#include "contactusdialog.h"
#include "renewmembershipdialog.h"
MemberMainDialog::MemberMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemberMainDialog),
    currentUserEmail("")
{
    ui->setupUi(this);
    connect(ui->pushButton_4, &QPushButton::clicked, this, [this]()
    {
        RenewMembershipDialog dlg(this);
        dlg.setEmail(currentUserEmail);
        dlg.exec();

        loadUserInfo();
        loadMembershipStatus();
    });
    connect(ui->pushButton_2, &QPushButton::clicked, this, [this]()
    {
        auto *dlg = new ContactUsDialog();
        dlg->setAttribute(Qt::WA_DeleteOnClose);
        dlg->show();
    });
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->widget()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    ui->scrollArea->widget()->layout()->setSizeConstraint(QLayout::SetMinimumSize);
    ui->scrollAreaWidgetContents_4->setSizePolicy(
        QSizePolicy::Preferred,
        QSizePolicy::Preferred
    );
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->label_31->setStyleSheet(
        "border:3px solid #FFD700;"
        "border-radius:60px;"
        "background-color:#1a2332;"
    );
    ui->statusCircleLabel_3->setStyleSheet(
        "background-color:red;"
        "border-radius:7px;"
    );

    loadUserPhoto();


    connect(ui->dashboardPushButton_2, &QPushButton::clicked,
            this, [this]()
    {
        saveCheckOut();
        accept();
    });

    connect(ui->changepicToolButton_3, &QToolButton::clicked, this, [this]() {

        QString fileName = QFileDialog::getOpenFileName(
            this,
            "Select Profile Picture",
            "",
            "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
        );

        if (!fileName.isEmpty()) {
            QPixmap pixmap(fileName);

            if (!pixmap.isNull()) {
                ui->label_31->setPixmap(
                    pixmap.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation)
                );

                saveUserPhoto(pixmap);

                QMessageBox::information(this, "Success", "Profile picture saved!");
            }
        }
    });

    connect(ui->pushButton, &QPushButton::clicked, this, [this]() {

        QPixmap defaultPixmap(":/icons/FILES/default_user.png");

        ui->label_31->setPixmap(
            defaultPixmap.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );

        saveUserPhoto(defaultPixmap);

        QMessageBox::information(this, "Reset", "Profile picture reset!");
    });
}

MemberMainDialog::~MemberMainDialog()
{
    delete ui;
}

void MemberMainDialog::setUserEmail(const QString &email)
{
    currentUserEmail = email;
    saveCheckIn();
    loadUserPhoto();
    loadMembershipStatus();
    loadUserInfo();
    updateSessionsByTime();
    loadUserInfo();
}

void MemberMainDialog::saveUserPhoto(const QPixmap &pixmap)
{
    if (currentUserEmail.isEmpty())
        return;

    QFile file("users.json");
    QJsonArray users;

    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        users = doc.array();
        file.close();
    }

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");

    QString imageData = QString::fromLatin1(byteArray.toBase64());

    bool found = false;

    for (int i = 0; i < users.size(); i++) {
        QJsonObject user = users[i].toObject();

        if (user["EMAIL"].toString() == currentUserEmail) {
            user["PROFILE_IMAGE"] = imageData;
            users[i] = user;
            found = true;
            break;
        }
    }

    if (!found) {
        QJsonObject newUser;
        newUser["EMAIL"] = currentUserEmail;
        newUser["PROFILE_IMAGE"] = imageData;
        users.append(newUser);
    }

    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(users);
        file.write(doc.toJson());
        file.close();
    }
}

void MemberMainDialog::loadUserPhoto()
{
    if (currentUserEmail.isEmpty()) {
        ui->label_31->setPixmap(
            QPixmap(":/icons/FILES/default_user.png")
            .scaled(120,120,Qt::KeepAspectRatio,Qt::SmoothTransformation)
        );
        return;
    }

    QFile file("users.json");

    if (!file.open(QIODevice::ReadOnly))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray users = doc.array();
    file.close();

    for (const QJsonValue &value : users) {
        QJsonObject user = value.toObject();

        if (user["EMAIL"].toString() == currentUserEmail) {
            if (user.contains("PROFILE_IMAGE")) {
                QByteArray byteArray =
                    QByteArray::fromBase64(user["PROFILE_IMAGE"].toString().toLatin1());

                QPixmap pixmap;

                if (pixmap.loadFromData(byteArray, "PNG")) {
                    ui->label_31->setPixmap(
                        pixmap.scaled(120,120,Qt::KeepAspectRatio,Qt::SmoothTransformation)
                    );
                    return;
                }
            }
        }
    }
}

void MemberMainDialog::loadMembershipStatus()
{
    QFile file("users.json");

    if (!file.open(QIODevice::ReadOnly))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray users = doc.array();
    file.close();

    for (const QJsonValue &value : users) {
        QJsonObject user = value.toObject();

        if (user["EMAIL"].toString() == currentUserEmail) {

            bool hasMembership = user["HAS_MEMBERSHIP"].toBool(false);

            ui->statusCircleLabel_3->setStyleSheet(
                hasMembership
                    ? "background-color:#00d26a;border-radius:7px;"
                    : "background-color:red;border-radius:7px;"
            );

            return;
        }
    }
}

QJsonObject MemberMainDialog::getCurrentUser()
{

    QFile file("users.json");

    if (!file.open(QIODevice::ReadOnly))
        return QJsonObject();

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray users = doc.array();
    file.close();

    for (const QJsonValue &value : users) {
        QJsonObject obj = value.toObject();

        if (obj["EMAIL"].toString() == currentUserEmail)
            return obj;
    }

    return QJsonObject();
}

void MemberMainDialog::loadUserInfo()
{
    QFile file("users.json");

    if (!file.open(QIODevice::ReadOnly))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    QJsonArray users = doc.array();

    for (const QJsonValue &value : users)
    {
        QJsonObject user = value.toObject();

        if (user["EMAIL"].toString() == currentUserEmail)
        {
            ui->label_32->setText("FULL NAME: " + user["FULL NAME"].toString());
            ui->label_33->setText("EMAIL: " + user["EMAIL"].toString());
            QJsonArray log = user["ACTIVITY_LOG"].toArray();

            QString history;

            for(int i = log.size() - 1; i >= 0; i--)
            {
                history += log[i].toString() + "\n";
            }

            ui->plainTextEdit->setPlainText(history);
            ui->label_36->setText("MEMBER ID: " + user.value("MEMBER_ID").toString("NONE"));            QString membershipText;
            ui->label_37->setText("MEMBER SINCE: " + user.value("MEMBER_SINCE").toString("UNKNOWN"));
            ui->label_42->setText(
                QString::number(user["SESSIONS_USED"].toInt())
            );

            ui->label_44->setText(
                QString::number(user["SESSIONS_LEFT"].toInt())
            );

            ui->label_46->setText(QString::number(user["TOTAL_SESSIONS"].toInt())

            );
            ui->lcdNumber_3->display(
                user.value("WORKOUT_PLAN").toInt()
            );

            ui->lcdNumber_4->display(
                user.value("DIET_PLAN").toInt()
            );

            ui->progressBar_2->setMaximum(user["TOTAL_SESSIONS"].toInt());
            ui->progressBar_2->setValue(user["SESSIONS_USED"].toInt());
            if (!user["HAS_MEMBERSHIP"].toBool(false))
            {
                membershipText = "NONE";
            }
            else
            {
                membershipText = user.value("MEMBERSHIP_TYPE").toString("NONE");
                QString trainer = user.value("TRAINER_NAME").toString();

                if (trainer.isEmpty())
                    trainer = "NONE";

                ui->trainerLabel_2->setText(
                    "Trainer\n" + trainer
                );
            }

            ui->label_35->setText("ACCOUNT TYPE: " + membershipText);
            QString trainer = user.value("TRAINER_NAME").toString();

            if (trainer.contains("Mehrzad")) {
                trainer = "🙂 Mehrzad Shahcheraqian";
            }
            else if (trainer.contains("Shayan")) {
                trainer = "🥶 Shayan Shahamiri";
            }
            else {
                trainer = "😪 NO TRAINER";
            }

            ui->trainerLabel_2->setText(
                "<div style='text-align:center;'>"
                "<span style='font-size:12pt;'>Trainer</span><br>"
                "<span style='font-size:22pt; font-weight:bold; color:#FFD700;'>"
                + trainer +
                "</span></div>"
            );

            return;
        }
    }
}
void MemberMainDialog::saveCheckOut()
{
    QFile file("users.json");

    if (!file.open(QIODevice::ReadOnly))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray users = doc.array();
    file.close();

    for(int i = 0; i < users.size(); i++)
    {
        QJsonObject user = users[i].toObject();

        if(user["EMAIL"].toString() == currentUserEmail)
        {
            user["LAST_CHECKOUT"] =
                QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
            QJsonArray log = user["ACTIVITY_LOG"].toArray();

            log.append(
                QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
                + " - CHECKED OUT"
            );

            user["ACTIVITY_LOG"] = log;
            users[i] = user;
            break;
        }
    }

    if(file.open(QIODevice::WriteOnly))
    {
        file.write(QJsonDocument(users).toJson());
        file.close();
    }
}
void MemberMainDialog::closeEvent(QCloseEvent *event)
{
    saveCheckOut();
    QDialog::closeEvent(event);
}
void MemberMainDialog::saveCheckIn()
{
    QFile file("users.json");
    if (!file.open(QIODevice::ReadOnly))
        return;

    QJsonArray users = QJsonDocument::fromJson(file.readAll()).array();
    file.close();

    for (int i = 0; i < users.size(); i++)
    {
        QJsonObject user = users[i].toObject();

        if (user["EMAIL"].toString() == currentUserEmail)
        {

            user["LAST_LOGIN"] =
                QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
            QJsonArray log = user["ACTIVITY_LOG"].toArray();

            log.append(
                QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
                + " - CHECKED IN"
            );

            user["ACTIVITY_LOG"] = log;

            users[i] = user;
            break;
        }
    }

    file.open(QIODevice::WriteOnly);
    file.write(QJsonDocument(users).toJson());
    file.close();
}
void MemberMainDialog::applyMembership(const QString &plan)
{
    QFile file("users.json");
    if(!file.open(QIODevice::ReadOnly)) return;

    QJsonArray users = QJsonDocument::fromJson(file.readAll()).array();
    file.close();

    int sessions = 0;

    if(plan.contains("Gold")) sessions = 30;
    else if(plan.contains("Silver")) sessions = 20;
    else if(plan.contains("Basic")) sessions = 10;

    for(int i=0;i<users.size();i++)
    {
        QJsonObject u = users[i].toObject();

        if(u["EMAIL"].toString() == currentUserEmail)
        {
            u["HAS_MEMBERSHIP"] = true;
            u["MEMBERSHIP_TYPE"] = plan;
            u["TOTAL_SESSIONS"] = sessions;
            u["SESSIONS_USED"] = 0;
            u["SESSIONS_LEFT"] = sessions;

            users[i] = u;
            break;
        }
    }

    QFile w("users.json");
    if(w.open(QIODevice::WriteOnly))
        w.write(QJsonDocument(users).toJson());

    loadMembershipStatus();
    loadUserInfo();
}
void MemberMainDialog::updateSessionsByTime()
{
    QFile file("users.json");
    if (!file.open(QIODevice::ReadOnly))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray users = doc.array();
    file.close();

    QDateTime now = QDateTime::currentDateTime();

    for (int i = 0; i < users.size(); i++)
    {
        QJsonObject u = users[i].toObject();

        if (u["EMAIL"].toString() == currentUserEmail)
        {
            QDateTime last = QDateTime::fromString(
                u.value("PAYMENT_HISTORY").toArray().last().toObject().value("DATE").toString(),
                "yyyy-MM-dd HH:mm:ss"
            );

            if (!last.isValid())
                last = now;

            int daysPassed = last.daysTo(now);

            if (daysPassed >= 2)
            {
                int times = daysPassed / 2;

                int used = u["SESSIONS_USED"].toInt();
                int left = u["SESSIONS_LEFT"].toInt();

                used += times;
                left -= times;

                if (left < 0) left = 0;

                u["SESSIONS_USED"] = used;
                u["SESSIONS_LEFT"] = left;

                u["LAST_SESSION_UPDATE"] =
                    now.toString("yyyy-MM-dd HH:mm:ss");

                users[i] = u;
                break;
            }
        }
    }

    QFile w("users.json");
    if (w.open(QIODevice::WriteOnly))
    {
        w.write(QJsonDocument(users).toJson());
        w.close();
    }
}
