#ifndef FAKEPAYMENTDIALOG_H
#define FAKEPAYMENTDIALOG_H

#include <QDialog>

namespace Ui {
class FakePaymentDialog;
}

class FakePaymentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FakePaymentDialog(QWidget *parent = nullptr);
    ~FakePaymentDialog();

private:
    Ui::FakePaymentDialog *ui;
};

#endif // FAKEPAYMENTDIALOG_H
