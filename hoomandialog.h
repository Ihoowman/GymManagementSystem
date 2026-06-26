#ifndef HOOMANDIALOG_H
#define HOOMANDIALOG_H

#include <QDialog>

namespace Ui {
class HoomanDialog;
}

class HoomanDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HoomanDialog(QWidget *parent = nullptr);
    ~HoomanDialog();

private:
    Ui::HoomanDialog *ui;
};

#endif // HOOMANDIALOG_H
