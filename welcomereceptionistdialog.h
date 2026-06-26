#ifndef WELCOMERECEPTIONISTDIALOG_H
#define WELCOMERECEPTIONISTDIALOG_H

#include <QDialog>

namespace Ui {
class WelcomereceptionistDialog;
}

class WelcomereceptionistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomereceptionistDialog(QWidget *parent = nullptr);
    ~WelcomereceptionistDialog();

    void setName(const QString &name);
    void setRole(const QString &role);

private:
    Ui::WelcomereceptionistDialog *ui;
    QString userRole;
};

#endif
