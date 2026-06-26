#ifndef HOOMANFORM_H
#define HOOMANFORM_H

#include <QWidget>

namespace Ui {
class hoomanForm;
}

class hoomanForm : public QWidget
{
    Q_OBJECT

public:
    explicit hoomanForm(QWidget *parent = nullptr);
    ~hoomanForm();

private:
    Ui::hoomanForm *ui;
};

#endif // HOOMANFORM_H
