#include "fakedialog.h"
#include "ui_fakedialog.h"

FakeDialog::FakeDialog(const QString &plan, int totalPrice, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::FakeDialog),
      currentPlan(plan),
      timer(new QTimer(this)),
      progressValue(0),
      finalPrice(totalPrice)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->label_6->setText(
        QLocale(QLocale::English).toString(finalPrice) + " RIAL"
    );

    ui->label_6->setStyleSheet(
        "QLabel{"
        "color:#00C853;"
        "font-size:28px;"
        "font-weight:900;"
        "background-color:#0F172A;"
        "border:2px solid #00C853;"
        "border-radius:12px;"
        "padding:12px;"
        "}"
    );
    ui->progressBar->setValue(0);
    ui->pushButton->setText("PAY NOW");
    ui->pushButton->setStyleSheet(
        "background-color:#00c853;"
        "color:white;"
        "font-weight:bold;"
        "padding:8px;"
        "border-radius:8px;"
    );


    connect(ui->pushButton, &QPushButton::clicked,
            this, &FakeDialog::startFake);
}

FakeDialog::~FakeDialog()
{
    delete ui;
}
void FakeDialog::startFake()
{
    ui->pushButton->setEnabled(false);

    ui->pushButton->setText("Processing...");
    ui->pushButton->setStyleSheet(
        "background-color:#ffb300;"
        "color:black;"
        "font-weight:bold;"
        "border-radius:8px;"
    );

    ui->label_3->setText("🔄 Redirecting to secure gateway...");
    ui->label_3->setStyleSheet("color:#ff9800;font-weight:bold;");

    progressValue = 0;
    ui->progressBar->setValue(0);

    connect(timer, &QTimer::timeout, this, [=]() mutable {

        progressValue += 10;
        ui->progressBar->setValue(progressValue);

        if (progressValue >= 100) {
            timer->stop();
            onSuccess();
        }
    });

    timer->start(150);
}
void FakeDialog::onSuccess()
{
    ui->label_3->setText("✔ PAYMENT SUCCESSFUL");
    ui->label_3->setStyleSheet("color:#00c853;font-weight:bold;");

    ui->pushButton->setText("DONE");
    ui->pushButton->setStyleSheet(
        "background-color:#00c853;"
        "color:white;"
        "font-weight:bold;"
        "border-radius:8px;"
    );

    emit paymentSuccess(currentPlan);

    QTimer::singleShot(1000, this, [=]() {
        accept();
    });
}
