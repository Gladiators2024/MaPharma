#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "transaction.h"
#include "arduino.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openDoor();
    void update_label();

private slots:







    void on_recherche_combox_currentTextChanged(const QString &arg1);

    void on_id_r_valueChanged(int arg1);

    void on_type_r_currentTextChanged(const QString &arg1);

    void on_date_r_userDateChanged(const QDate &date);

    void on_ajouterButton_clicked_clicked();

    void on_modifierButton_clicked_clicked();

    void on_supprimerButton_clicked_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();


    void on_pushButton_21_clicked();
    void gethistorique();


    void on_pushButton_22_clicked();

    void on_pushButton_28_clicked();


    void on_pdfbtn_clicked();


private:
    Ui::MainWindow *ui;
    Transactions Etmp; // Remplacer l'objet Client par un objet Transaction
     bool test; // Ajout de la déclaration de la variable 'test'
     QString recherechtyp;
     arduino A;               // Arduino object for communication

};






#endif // MAINWINDOW_H
