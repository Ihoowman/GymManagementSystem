#ifndef MEMBERPAGEDIALOG_H
#define MEMBERPAGEDIALOG_H

#include <QDialog>

namespace Ui {
class MemberPageDialog;
}

class MemberPageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MemberPageDialog(QWidget *parent = nullptr);
    ~MemberPageDialog();

private:
    Ui::MemberPageDialog *ui;
};

#endif // MEMBERPAGEDIALOG_H
