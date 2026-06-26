#include "memberpagedialog.h"
#include "ui_memberpage.h"
#include "signupdialog.h"
#include <QKeyEvent>
MemberPage::MemberPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemberPage)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt:: WindowContextHelpButtonHint);
    ui->lineEdit->setText(fixedDomain);
    ui->lineEdit->setCursorPosition(0);
    ui->lineEdit->installEventFilter(this);
    this->setWindowTitle("MEMBER LOGIN");
    this->setWindowIcon(QIcon(":/icons/FILES/LOGO.png"));
}
MemberPage::~MemberPage()
{
    delete ui;
}
void MemberPage::on_lineEdit_textChanged(const QString &arg1)
{
}

void MemberPage::on_pushButton_clicked()
{
    SignupDialog x(this);
    x.exec();
}
bool MemberPage::eventFilter(QObject *obj, QEvent *event)
{
    if (obj != ui->lineEdit)
        return QDialog::eventFilter(obj, event);

    QString text = ui->lineEdit->text();

    if (!text.endsWith(fixedDomain)) {
        int atPos = text.indexOf('@');
        QString userPart = (atPos >= 0) ? text.left(atPos) : text;
        ui->lineEdit->setText(userPart + fixedDomain);
    }

    int domainStart = ui->lineEdit->text().size() - fixedDomain.size();
    int cursorPos = ui->lineEdit->cursorPosition();
    if (cursorPos > domainStart)
        ui->lineEdit->setCursorPosition(domainStart);
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent*>(event);
        cursorPos = ui->lineEdit->cursorPosition();
        if (ke->key() == Qt::Key_Backspace) {
            if (cursorPos <= domainStart && cursorPos > 0)
                return QDialog::eventFilter(obj, event);
            return true;
        }
        if (ke->key() == Qt::Key_Delete) {
            if (cursorPos < domainStart)
                return QDialog::eventFilter(obj, event);
            return true;
        }
        if (ke->key() == Qt::Key_End) {
            ui->lineEdit->setCursorPosition(domainStart);
            return true;
        }
        if (ke->matches(QKeySequence::Paste)) {
            return true;
        }
    }
    return QDialog::eventFilter(obj, event);
}
