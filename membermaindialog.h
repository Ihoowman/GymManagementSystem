#ifndef MEMBERMAINDIALOG_H
#define MEMBERMAINDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <QPixmap>

namespace Ui {
class MemberMainDialog;
}

class MemberMainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MemberMainDialog(QWidget *parent = nullptr);
    ~MemberMainDialog();
    void setUserEmail(const QString &email);

signals:
    void backToMainWindow();

private:
    Ui::MemberMainDialog *ui;
    void applyMembership(const QString &plan);
    QString currentUserEmail;
    void saveCheckIn();
    void saveUserPhoto(const QPixmap &pixmap);
    void loadUserPhoto();
    void loadMembershipStatus();
    void saveCheckOut();
    void loadUserInfo();
    void closeEvent(QCloseEvent *event) override;
    void updateSessionsByTime();
    QJsonObject getCurrentUser();
    bool m_hasCheckedIn = false;

};

#endif
