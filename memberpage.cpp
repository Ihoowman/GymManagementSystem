#include "memberpage.h"
#include "ui_memberpage.h"
#include "signupdialog.h"
#include <QKeyEvent>
#include <QFile>
//#include <QNetworkAccessManager>
//#include <QNetworkRequest>
//#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include "otpdialog.h"
#include <QRandomGenerator>
//#include "smtpclient.h"
//#include "mimemessage.h"
//#include "mimetext.h"
//#include <QCoreApplication>    //movaghat

MemberPage::MemberPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemberPage)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt:: WindowContextHelpButtonHint);
    ui->lineEdit->setText(fixedDomain);
    ui->lineEdit->setCursorPosition(0);
    ui->lineEdit->installEventFilter(this);
    this->setWindowTitle("MEMBER LOGIN");
    this->setWindowIcon(QIcon(":/icons/FILES/LOGO.png"));
   // qDebug() << "SSL Supported =" << QSslSocket::supportsSsl();  //movaghat
    //qDebug() << "Run SSL =" << QSslSocket::sslLibraryVersionString();     //movaghat
   // qDebug() << QCoreApplication::libraryPaths();  //movaghat
}

MemberPage::~MemberPage()
{
    delete ui;
}

void MemberPage::on_lineEdit_textChanged(const QString &arg1)
{
}

void MemberPage::on_pushButton_clicked()
{
    SignupDialog x(this);
    x.exec();
}

bool MemberPage::eventFilter(QObject *obj, QEvent *event)
{
    if (obj != ui->lineEdit)
        return QDialog::eventFilter(obj, event);

    QString text = ui->lineEdit->text();

    if (!text.endsWith(fixedDomain)) {
        int atPos = text.indexOf('@');
        QString userPart = (atPos >= 0) ? text.left(atPos) : text;
        ui->lineEdit->setText(userPart + fixedDomain);
    }

    int domainStart = ui->lineEdit->text().size() - fixedDomain.size();
    int cursorPos = ui->lineEdit->cursorPosition();

    if (cursorPos > domainStart)
        ui->lineEdit->setCursorPosition(domainStart);

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent*>(event);
        cursorPos = ui->lineEdit->cursorPosition();

        if (ke->key() == Qt::Key_Backspace) {
            if (cursorPos <= domainStart && cursorPos > 0)
                return QDialog::eventFilter(obj, event);
            return true;
        }

        if (ke->key() == Qt::Key_Delete) {
            if (cursorPos < domainStart)
                return QDialog::eventFilter(obj, event);
            return true;
        }

        if (ke->key() == Qt::Key_End) {
            ui->lineEdit->setCursorPosition(domainStart);
            return true;
        }

        if (ke->matches(QKeySequence::Paste)) {
            return true;
        }
    }

    return QDialog::eventFilter(obj, event);
}

bool emailExists(QString email)
{
    QFile file("users.json");

    if(!file.open(QIODevice::ReadOnly))
        return false;

    QJsonDocument doc =
            QJsonDocument::fromJson(file.readAll());

    QJsonArray users = doc.array();

    file.close();

    for(const QJsonValue &value : users)
    {
        QJsonObject user = value.toObject();

        if(user["EMAIL"].toString() == email)
            return true;
    }

    return false;
}

/*
void sendOtpEmail(const QString &receiverEmail, const QString &otp)
{
    SmtpClient smtp("smtp.gmail.com", 587, SmtpClient::TlsConnection);

    MimeMessage message;

    message.setSender(
        EmailAddress(
            "fathatergymofficial@gmail.com",
            "FAT HATER GYM"));

    message.addRecipient(
        EmailAddress(receiverEmail));

    message.setSubject("Your OTP Code");

    MimeText *text = new MimeText;

    text->setText(
        "Your verification code is: " + otp);

    message.addPart(text);

    smtp.connectToHost();

    smtp.login(
        "fathatergymofficial@gmail.com",
        "gkiexflptlpevqtb");

    qDebug() << smtp.waitForAuthenticated();   //movaghat

    smtp.sendMail(message);

    QMessageBox::information(nullptr,
                             "SMTP",
                             "SendMail Finished");     //movaghat

    smtp.quit();
}
*/
/*void sendOtpSms(const QString &mobile,
                const QString &otp)
{
    QNetworkAccessManager *manager =
            new QNetworkAccessManager();

    QNetworkRequest request(
        QUrl("https://s.api.ir/api/sw1/SmsOTP"));

    request.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/json");

    request.setRawHeader(
        "Authorization",
        "Bearer CxiYDsZ5g70oMHiXhmlVqtkidh8jZn8YjHuU6lAiY5jnS9jXEeEbE4CELVfp1Jwpr6jwhGeQe4BqwLhkPYwXFGgLLyW7u/d/BcT++KCqN+Q=");

    QJsonObject json;
    json["code"] = otp;
    json["mobile"] = mobile;
    json["template"] = 2;

    QByteArray data =
            QJsonDocument(json).toJson();

    QNetworkReply *reply =
            manager->post(request, data);

    QObject::connect(reply,
                     &QNetworkReply::finished,
                     [reply]()
    {
        qDebug() << reply->readAll();
        reply->deleteLater();
    });
}*/
void MemberPage::on_pushButton_2_clicked()
{
    QString email = ui->lineEdit->text();

    if(!emailExists(email))
    {
        QMessageBox::warning(this,
                             "ERROR",
                             "No account found!");
        return;
    }

    QFile file("users.json");

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "ERROR", "Cannot open database");
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    QJsonArray users = doc.array();

    QJsonObject user;
    bool found = false;

    for(const QJsonValue &value : users)
    {
        QJsonObject u = value.toObject();

        if(u["EMAIL"].toString() == email)
        {
            user = u;
            found = true;
            break;
        }
    }

    if(!found)
    {
        QMessageBox::warning(this, "ERROR", "User not found");
        return;
    }

    QString mobile = user["NUMBER"].toString();
    if(!mobile.startsWith("0"))
    {
        mobile = "0" + mobile;
    }
    QString otp = QString::number(
        QRandomGenerator::global()->bounded(100000, 999999)
    );
    QString now = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    for(int i = 0; i < users.size(); i++)
    {
        QJsonObject u = users[i].toObject();

        if(u["EMAIL"].toString() == email)
        {
            u["LAST_OTP"] = otp;
            u["OTP_TIME"] = now;
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

    //sendOtpSms(mobile, otp);

    OtpDialog *dlg = new OtpDialog();
    dlg->setOtp(otp);
    dlg->setEmail(email);
    //dlg->setRole("member");
    dlg->exec();
    this->reject();
}

    /*
    QString otp = QString::number(
        QRandomGenerator::global()->bounded(100000, 999999)
    );

    OtpDialog x;

    x.setOtp(otp);

    sendOtpEmail(email, otp);

    x.exec();
    */

