#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include"employes.h"
#include<QProcess>
#include"arduino.h"
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
    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_lineEdit_textChanged();

    void on_comboBox_currentIndexChanged();

    void on_exporter_clicked();

    void on_stats_clicked();

    void on_email_to_textChanged(const QString &text);

    void on_send_clicked();

    void on_save_f_clicked();

    void on_recognise_f_clicked();

    void update_label();
    void openDoor();

private:
    Ui::MainWindow *ui;
    void exportTableViewToPDF(QTableView *tablevView);
    void showSalaryStatsInTab();
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    employes e;
    QStringList emailList;
    QByteArray data;
    arduino A;
};
#endif // MAINWINDOW_H
