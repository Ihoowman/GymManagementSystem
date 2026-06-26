#ifndef RECEPTIONISTPAGEDIALOG_H
#define RECEPTIONISTPAGEDIALOG_H

#include <QDialog>

namespace Ui {
class ReceptionistPageDialog;
}

class ReceptionistPageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReceptionistPageDialog(QWidget *parent = nullptr);
    ~ReceptionistPageDialog();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::ReceptionistPageDialog *ui;
    const QString fixedDomain = "@gmail.com";
};

#endif // RECEPTIONISTPAGEDIALOG_H
