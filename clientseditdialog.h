#ifndef CLIENTSEDITDIALOG_H
#define CLIENTSEDITDIALOG_H

#include <QDialog>
#include "Member.h"
namespace Ui {
class ClientsEditDialog;
}

class ClientsEditDialog : public QDialog
{
    Q_OBJECT
    Member *member;

public:
    explicit ClientsEditDialog(Member *member, QWidget *parent = nullptr);
    ~ClientsEditDialog();

private:
    Ui::ClientsEditDialog *ui;
private slots:
    void saveChanges();
};


#endif // CLIENTSEDITDIALOG_H
