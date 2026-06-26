#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contactusdialog.h"
#include "logindialog.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QValueAxis>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QFontDatabase>
QT_CHARTS_USE_NAMESPACE
using namespace QtCharts;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(
        QPixmap(":/icons/FILES/LOGO.png")
        .scaled(220,78,Qt::KeepAspectRatio,Qt::SmoothTransformation)
    );
    ui->label_2->setPixmap(QPixmap(":/icons/FILES/FAT_HATER_GYM_dark.png").scaled(1100, 1100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_3->setPixmap(QPixmap(":/icons/FILES/GYM1979.png").scaled(500, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_7->setPixmap(QPixmap(":/icons/FILES/GYMNOW.png").scaled(500, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_7->setPixmap(
        QPixmap(":/icons/FILES/GYMNOW.png")
        .scaled(500,300,Qt::KeepAspectRatio,Qt::SmoothTransformation)
    );
    setupChart();
    clockLabel = new QLabel(this);
    dateLabel = new QLabel(this);
    statusBar()->addPermanentWidget(dateLabel);
    statusBar()->addPermanentWidget(clockLabel);

    dateLabel->setStyleSheet(
        "color: #ffcc00;"
        "background-color: black;"
        "padding: 4px 10px;"
        "border-radius: 6px;"
    );

    clockLabel->setStyleSheet(
        "color: #00ffcc;"
        "background-color: black;"
        "padding: 4px 10px;"
        "border-radius: 6px;"
    );
    int fontId = QFontDatabase::addApplicationFont(":/fonts/digital-7.ttf");

    QString family;

    if (fontId != -1 && !QFontDatabase::applicationFontFamilies(fontId).isEmpty())
    {
        family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    }
    else
    {
        family = "Consolas";
    }

    QFont font(family);
    font.setPointSize(14);
    clockLabel->setFont(font);

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this]() {
        QString time = QDateTime::currentDateTime().toString("HH:mm:ss");
        QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd");

        clockLabel->setText(time);
        dateLabel->setText(date);

    });

    timer->start(1000);
    generateDayData();
    updateChart();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_contactusbtn_clicked()
{
    ContactUsDialog x;
    x.exec();
}

void MainWindow::on_loginbtn_clicked()
{
    LoginDialog x;
    x.exec();
}
void MainWindow::setupChart()
{
    auto *series = new QLineSeries();

    series->append(5, 5);
    series->append(6, 8);
    series->append(7, 12);
    series->append(8, 20);
    series->append(9, 35);
    series->append(10, 50);
    series->append(11, 65);
    series->append(12, 70);
    series->append(13, 80);
    series->append(14, 60);
    series->append(15, 55);
    series->append(16, 75);
    series->append(17, 90);
    series->append(18, 85);
    series->append(19, 70);
    series->append(20, 60);
    series->append(21, 40);
    series->append(22, 25);
    series->append(23, 10);

    auto *bottomSeries = new QLineSeries();
    bottomSeries->append(5, 0);
    bottomSeries->append(23, 0);

    auto *area = new QAreaSeries(series, bottomSeries);

    QPen pen(QColor("#4da3ff"));
    pen.setWidth(2);
    area->setPen(pen);

    area->setBrush(QColor(77, 163, 255, 120));

    auto *chart = new QChart();
    chart->addSeries(area);

    chart->setBackgroundBrush(QColor("#0b1b2b"));
    chart->setBackgroundRoundness(10);

    chart->legend()->hide();

    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(5, 23);
    axisX->setLabelFormat("%d");
    axisX->setTitleText("Hour");

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);
    axisY->setTitleText("Crowd");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    area->attachAxis(axisX);
    area->attachAxis(axisY);

    auto *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);

    view->setStyleSheet("background: transparent;");

    QVBoxLayout *layout = new QVBoxLayout(ui->chartWidget);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(view);
}

int MainWindow::generateCrowd(QRandomGenerator &rng)
{
    return rng.bounded(5, 100);
}
void MainWindow::generateDayData()
{
    crowdData.clear();

    quint32 seed = QDate::currentDate().toJulianDay();
    QRandomGenerator rng(seed);

    for (int hour = 5; hour <= 23; hour++)
    {
        crowdData.append(generateCrowd(rng));
    }
}
void MainWindow::updateChart()
{
    auto *series = new QLineSeries();

    int hour = 5;
    for (int value : crowdData)
        series->append(hour++, value);

    auto *bottom = new QLineSeries();
    bottom->append(5, 0);
    bottom->append(23, 0);

    auto *area = new QAreaSeries(series, bottom);

    QPen pen(QColor("#4da3ff"));
    pen.setWidth(2);
    area->setPen(pen);
    area->setBrush(QColor(77, 163, 255, 120));

    auto *chart = new QChart();
    chart->addSeries(area);
    chart->setBackgroundBrush(QColor("#0b1b2b"));
    chart->legend()->hide();

    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(5, 23);
    axisX->setTitleText("Hour");

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);
    axisY->setTitleText("Crowd");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    area->attachAxis(axisX);
    area->attachAxis(axisY);

    auto *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setStyleSheet("background: transparent;");

    if (!ui->chartWidget->layout())
        ui->chartWidget->setLayout(new QVBoxLayout());

    QLayoutItem *item;
    while ((item = ui->chartWidget->layout()->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }

    ui->chartWidget->layout()->addWidget(view);
}
