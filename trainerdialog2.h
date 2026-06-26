#ifndef TRAINERDIALOG2_H
#define TRAINERDIALOG2_H

#include <QDialog>

namespace Ui {
class TrainerDialog2;
}

class TrainerDialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit TrainerDialog2(QWidget *parent = nullptr);
    ~TrainerDialog2();

private:
    Ui::TrainerDialog2 *ui;
    void search();
};

#endif // TRAINERDIALOG2_H
