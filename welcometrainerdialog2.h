#ifndef WELCOMETRAINERDIALOG2_H
#define WELCOMETRAINERDIALOG2_H

#include <QDialog>

namespace Ui {
class WelcomeTrainerDialog2;
}

class WelcomeTrainerDialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeTrainerDialog2(QWidget *parent = nullptr);
    ~WelcomeTrainerDialog2();

private:
    Ui::WelcomeTrainerDialog2 *ui;
};

#endif // WELCOMETRAINERDIALOG2_H
