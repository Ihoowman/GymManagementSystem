#ifndef CONTACTUSDIALOG_H
#define CONTACTUSDIALOG_H

#include <QDialog>

namespace Ui {
class ContactUsDialog;
}

class ContactUsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContactUsDialog(QWidget *parent = nullptr);
    ~ContactUsDialog();

private:
    Ui::ContactUsDialog *ui;
};

#endif // CONTACTUSDIALOG_H
