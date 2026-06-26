#ifndef FAKEDIALOG_H
#define FAKEDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class FakeDialog;
}

class FakeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FakeDialog(const QString &plan, int totalPrice, QWidget *parent = nullptr);
    ~FakeDialog();

signals:
    void paymentSuccess(QString plan);

private:
    Ui::FakeDialog *ui;
    QString currentPlan;
    int finalPrice;
    QTimer *timer;
    int progressValue;
    void startFake();
    void onSuccess();
};

#endif
