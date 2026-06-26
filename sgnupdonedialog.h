#ifndef SGNUPDONEDIALOG_H
#define SGNUPDONEDIALOG_H

#include <QDialog>

namespace Ui {
class SgnupDoneDialog;
}

class SgnupDoneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SgnupDoneDialog(QWidget *parent = nullptr);
    ~SgnupDoneDialog();

private:
    Ui::SgnupDoneDialog *ui;
};

#endif // SGNUPDONEDIALOG_H
