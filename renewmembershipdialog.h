#ifndef RENEWMEMBERSHIPDIALOG_H
#define RENEWMEMBERSHIPDIALOG_H

#include <QDialog>
#include <QJsonObject>

namespace Ui {
class RenewMembershipDialog;
}

class RenewMembershipDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RenewMembershipDialog(QWidget *parent = nullptr);
    ~RenewMembershipDialog();

    void setEmail(const QString &email);

private slots:
    void on_pushButton_clicked();

private:
    Ui::RenewMembershipDialog *ui;

    void updatePrice();
    void applyMembership(const QString &plan);
    void saveToJson(const QString &plan,
                    const QString &trainer,
                    int sessions);

    int sessionPrice = 0;
    int trainerPrice = 0;
    int totalPrice = 0;

    QString currentEmail;
    bool isPaid = false;
};

#endif
