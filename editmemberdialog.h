#ifndef EDITMEMBERDIALOG_H
#define EDITMEMBERDIALOG_H

#include <QDialog>
#include "Member.h"

namespace Ui {
class EditMemberDialog;
}

class EditMemberDialog : public QDialog
{
    Q_OBJECT
    Member *member;

public:
    explicit EditMemberDialog(Member *member, QWidget *parent = nullptr);
    ~EditMemberDialog();

private:
    Ui::EditMemberDialog *ui;
private slots:
    void saveChanges();
};

#endif // EDITMEMBERDIALOG_H
