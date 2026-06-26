#ifndef WELCOMETRAINERDIALOG_H
#define WELCOMETRAINERDIALOG_H

#include <QDialog>

namespace Ui {
class WelcomeTrainerDialog;
}

class WelcomeTrainerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit WelcomeTrainerDialog(QWidget *parent = nullptr);
    ~WelcomeTrainerDialog();
    void setName(const QString &name);

private:
    Ui::WelcomeTrainerDialog *ui;
};

#endif // WELCOMETRAINERDIALOG_H
