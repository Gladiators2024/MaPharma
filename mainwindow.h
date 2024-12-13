#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "medicament.h"
#include <QRegularExpression>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
    void verifier_quantites_med();

private slots:
    void on_on_pushButton_ajouterMed_clicked();
    void on_pushButton_3_clicked();


    void on_modifier1_clicked();

    void on_modifier2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_clicked();

    void on_pushButton_8_clicked();

    void on_cancel_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Medicament medTmp;

};

#endif // MAINWINDOW_H
