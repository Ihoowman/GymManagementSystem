#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QLabel>
#include <QTimer>
#include <QVector>
#include <QDate>
#include <QRandomGenerator>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_contactusbtn_clicked();

    void on_loginbtn_clicked();

private:
    Ui::MainWindow *ui;
    void setupChart();
    QLabel *clockLabel;
    QTimer *timer;
    QLabel *dateLabel;
    QVector<int> crowdData;

        int generateCrowd(QRandomGenerator &rng);
        void generateDayData();
        void updateChart();

};
#endif // MAINWINDOW_H
