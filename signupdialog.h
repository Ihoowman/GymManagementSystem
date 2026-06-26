#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H
#include <QDialog>

namespace Ui {
class SignupDialog;
}

class SignupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignupDialog(QWidget *parent = nullptr);
    ~SignupDialog();
private slots:
    void on_expandButton_clicked();

    void on_loginLinkButton_clicked();

    void on_signupButton_clicked();

private:
    Ui::SignupDialog *ui;
    bool isExpanded = false;
};

#endif // SIGNUPDIALOG_H
