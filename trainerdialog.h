#ifndef TRAINERDIALOG_H
#define TRAINERDIALOG_H

#include <QDialog>

namespace Ui {
class TrainerDialog;
}

class TrainerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrainerDialog(QWidget *parent = nullptr);
    ~TrainerDialog();

private:
    Ui::TrainerDialog *ui;
    void search();
};

#endif // TRAINERDIALOG_H
