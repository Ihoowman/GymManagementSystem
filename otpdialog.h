#ifndef OTPDIALOG_H
#define OTPDIALOG_H
#include <QDialog>
#include <QTimer>
#include <QDateTime>

namespace Ui {
class OtpDialog;
}

class OtpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OtpDialog(QWidget *parent = nullptr);
    ~OtpDialog();
    void setOtp(const QString &otp);
    void setEmail(const QString &email);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::OtpDialog *ui;
    QString realOtp;
    QString userEmail;
    QTimer *timer;
    int timeLeft;
    int resendTimeLeft;
};

#endif // OTPDIALOG_H
