#ifndef TRAINERPAGEDIALOG_H
#define TRAINERPAGEDIALOG_H

#include <QDialog>

namespace Ui {
class trainerPageDialog;
}

class trainerPageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit trainerPageDialog(QWidget *parent = nullptr);
    ~trainerPageDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::trainerPageDialog *ui;
};

#endif // TRAINERPAGEDIALOG_H
