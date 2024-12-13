#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_ajouter_3_clicked();

    void on_supprimer_clicked();

    void on_afficher_clicked();

    void exporterVersPDF();

    void on_exporter_pdf_clicked();

    void on_pushButton_rechercher_3_clicked();

    void on_modifier_2_clicked();

    void retourVersMain();

    void on_boutonRetour_clicked();

    void on_showstats_clicked();

    void on_pushButton_clicked();

    void on_envoyerSMSButton_clicked();

    void on_comboBox_currentIndexChanged();

    void on_pushButton_rechercher_clicked();

    void on_passerAppelButton_clicked();

private:
    Ui::MainWindow *ui;
    client client;

    static const QRegularExpression emailRegex;
    static const QRegularExpression telRegex;

    void remplirChamps(const QModelIndex &index);
    void envoyerSMS(const QString &numero, const QString &message);
    void passerAppel(const QString &numero);
    void on_lerechercher_textChanged(const QString& critere);
    void appelerClientSlot();
    void envoyerSMSSlot();

};

#endif // MAINWINDOW_H
