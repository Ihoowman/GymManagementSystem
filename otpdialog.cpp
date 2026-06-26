#include "otpdialog.h"
#include "ui_otpdialog.h"
#include <QRegularExpressionValidator>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>
#include "welcomedialog.h"
//#include <QNetworkAccessManager>
//#include <QNetworkRequest>
//#include <QNetworkReply>
#include "membermaindialog.h"
OtpDialog::OtpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OtpDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt:: WindowContextHelpButtonHint);
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    ui->icon->setPixmap(QPixmap(":/icons/FILES/bale-column-text-black.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    this->setWindowTitle("Two-factor authentication (2FA)");
    this->setWindowIcon(QIcon(":/icons/FILES/LOGO.png"));
    QRegularExpression rx("[0-9]{0,6}");
    ui->lineEdit->setValidator(
        new QRegularExpressionValidator(rx, this));

    ui->lineEdit->setMaxLength(6);
    timeLeft = 180;
    resendTimeLeft = 180;

    ui->pushButton->setEnabled(false);
    ui->pushButton->setText("Resend (180)");
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]()
    {
        timeLeft--;
        resendTimeLeft--;

        ui->pushButton->setText(
            "Resend (" + QString::number(resendTimeLeft) + ")"
        );
        ui->labelTimer->setText(
            "Time left: " + QString::number(timeLeft) + " sec"

        );

        if(timeLeft <= 0)
        {
            timer->stop();

            ui->pushButton->setEnabled(true);
            ui->pushButton->setText("Resend");

        }
    });

    timer->start(1000);
}

OtpDialog::~OtpDialog()
{
    delete ui;
}
void OtpDialog::setOtp(const QString &otp)
{
    realOtp = otp;

    QMessageBox msg(this);

    msg.setWindowTitle("OTP CODE");
    msg.setText("Your OTP Code Is:\n\n" + realOtp);

    msg.setStyleSheet(
        "QMessageBox{"
        "background-color:#111111;"
        "}"

        "QLabel{"
        "color:#FFD700;"
        "font-size:18px;"
        "font-weight:bold;"
        "border:none;"
        "background:transparent;"
        "}"

        "QPushButton{"
        "background-color:#FFD700;"
        "color:black;"
        "border:none;"
        "padding:5px 15px;"
        "border-radius:4px;"
        "}"
    );

    msg.exec();
}
void OtpDialog::setEmail(const QString &email)
{
    userEmail = email;
}

void OtpDialog::on_pushButton_clicked()
{
    if(!ui->pushButton->isEnabled())
        return;

    QFile file("users.json");

    if(!file.open(QIODevice::ReadOnly))
        return;

    QJsonDocument doc =
            QJsonDocument::fromJson(file.readAll());

    file.close();

    QJsonArray users = doc.array();

    realOtp = QString::number(
        QRandomGenerator::global()->bounded(
            100000,
            999999));

    for(int i = 0; i < users.size(); i++)
    {
        QJsonObject u = users[i].toObject();

        if(u["EMAIL"].toString() == userEmail)
        {
            u["LAST_OTP"] = realOtp;

            u["OTP_TIME"] =
                    QDateTime::currentDateTime()
                    .toString("yyyy-MM-dd HH:mm:ss");

            users[i] = u;
            break;
        }
    }

    QFile writeFile("users.json");

    if(writeFile.open(QIODevice::WriteOnly))
    {
        QJsonDocument newDoc(users);
        writeFile.write(newDoc.toJson());
        writeFile.close();
    }

    ui->lineEdit->clear();

    timeLeft = 180;
    resendTimeLeft = 180;

    ui->pushButton->setEnabled(false);
    ui->pushButton->setText("Resend (180)");

    timer->start(1000);

    QMessageBox msg(this);

    msg.setWindowTitle("NEW OTP");
    msg.setText("Your New OTP Code Is:\n\n" + realOtp);

    msg.setStyleSheet(
        "QMessageBox{"
        "background-color:#111111;"
        "}"

        "QLabel{"
        "color:#FFD700;"
        "font-size:18px;"
        "font-weight:bold;"
        "border:none;"
        "background:transparent;"
        "}"

        "QPushButton{"
        "background-color:#FFD700;"
        "color:black;"
        "border:none;"
        "padding:5px 15px;"
        "border-radius:4px;"
        "}"
    );

    msg.exec();
}

    /*QNetworkAccessManager *manager =
            new QNetworkAccessManager(this);

    QNetworkRequest request(
        QUrl("https://s.api.ir/api/sw1/SmsOTP"));

    request.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/json");

    request.setRawHeader(
        "Authorization",
        "Bearer CxiYDsZ5g70oMHiXhmlVqtkidh8jZn8YjHuU6lAiY5jnS9jXEeEbE4CELVfp1Jwpr6jwhGeQe4BqwLhkPYwXFGgLLyW7u/d/BcT++KCqN+Q=");

    QJsonObject json;
    json["code"] = realOtp;
    json["mobile"] = mobile;
    json["template"] = 2;

    manager->post(
        request,
        QJsonDocument(json).toJson());*/
void OtpDialog::on_pushButton_2_clicked()
{
    QFile file("users.json");

    if(file.open(QIODevice::ReadOnly))
    {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();

        QJsonArray users = doc.array();

        for(int i = 0; i < users.size(); i++)
        {
            QJsonObject u = users[i].toObject();

            if(u["LAST_OTP"].toString() == realOtp)
            {
                QDateTime otpTime = QDateTime::fromString(
                    u["OTP_TIME"].toString(),
                    "yyyy-MM-dd HH:mm:ss"
                );

                int seconds = otpTime.secsTo(QDateTime::currentDateTime());

                if(seconds > 180)
                {
                    QMessageBox::warning(this, "ERROR", "OTP expired (3 minutes)");
                    return;
                }

                if(ui->lineEdit->text() == realOtp)
                {
                    u["IS_LOGGED_IN"] = true;
                    u["LAST_LOGIN"] = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
                    users[i] = u;
                    QString fullName = u["FULL NAME"].toString();
                    QFile w("users.json");
                    if(w.open(QIODevice::WriteOnly))
                    {
                        QJsonDocument newDoc(users);
                        w.write(newDoc.toJson());
                        w.close();
                    }
                    if(timer)
                    {
                        timer->stop();
                    }

                    WelcomeDialog dlg(this);
                    dlg.setName(fullName);
                    dlg.exec();

                    this->close();



                    MemberMainDialog *member = new MemberMainDialog();
                    member->setUserEmail(userEmail);
                    member->show();

                    return;
                }
            }
        }
    }

    QMessageBox msg(this);

    msg.setIcon(QMessageBox::Warning);
    msg.setWindowTitle("ERROR");
    msg.setText("Incorrect OTP");

    msg.setStyleSheet(
        "QMessageBox{"
        "background-color:#111111;"
        "}"

        "QLabel{"
        "color:#FFD700;"
        "border:none;"
        "background:transparent;"
        "}"

        "QPushButton{"
        "background-color:#FFD700;"
        "color:black;"
        "border:none;"
        "padding:5px 15px;"
        "border-radius:4px;"
        "}"
    );

    msg.exec();
}
