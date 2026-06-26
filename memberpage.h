#ifndef MEMBERPAGE_H
#define MEMBERPAGE_H

#include <QDialog>
#include <QEvent>

namespace Ui {
class MemberPage;
}

class MemberPage : public QDialog
{
    Q_OBJECT

public:
    explicit MemberPage(QWidget *parent = nullptr);
    ~MemberPage();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MemberPage *ui;
    const QString fixedDomain = "@gmail.com";
};

#endif // MEMBERPAGE_H
