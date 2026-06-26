#include "contactusdialog.h"
#include "ui_contactusdialog.h"

ContactUsDialog::ContactUsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContactUsDialog)
{
    ui->setupUi(this);
    ui->label_6->setText(R"(<a href="https://maps.app.goo.gl/Bd8FqDN7jaLFX2qx9">📍 LOCATION</a>)");
    ui->label_6->setTextFormat(Qt::RichText);
    ui->label_6->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->label_6->setOpenExternalLinks(true);
    setWindowFlags(windowFlags() & ~Qt:: WindowContextHelpButtonHint);
}
ContactUsDialog::~ContactUsDialog()
{
    delete ui;
}
