#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "fournisseur.h"
#include <QMainWindow>
#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QDebug>
#include <QMainWindow>
#include <QCalendarWidget>
#include <QMessageBox>
#include <QMap>
#include <QDate>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void onAPIResponseReceived(QNetworkReply *reply, QTextEdit *chatTextEdit, QLineEdit *inputLineEdit);
    void sendRequestToOpenAI(const QString &userInput, QTextEdit *chatTextEdit, QLineEdit *inputLineEdit);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_modif_clicked();
    void on_pushButton_2_clicked();
    void on_afficher_clicked();
    void on_rechercher_clicked();

    void on_pushButton_trier_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_stat_clicked();

    void on_pushButton_4_clicked();

    void on_onDate_clicked(const QDate &date);

private:
    Ui::MainWindow *ui;
    Fournisseur fr;
    QMap<QDate, QStringList> events;
};

#endif // MAINWINDOW_H
