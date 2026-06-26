#ifndef RECEPTIONISTDIALOG_H
#define RECEPTIONISTDIALOG_H

#include <QDialog>
#include <QTimer>
namespace Ui {
class ReceptionistDialog;
}

class ReceptionistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReceptionistDialog(QWidget *parent = nullptr);
    ~ReceptionistDialog();

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::ReceptionistDialog *ui;
    QTimer *statusTimer;
    bool greenVisible;

    void search();
};

#endif // RECEPTIONISTDIALOG_H
