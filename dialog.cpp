#include "dialog.h"
#include "ui_dialog.h"
#include"transaction.h"
#include"mainwindow.h"
#include<QMessageBox>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    int id =ui->id->text().toInt();
    QString password=ui->password->text();
    Transactions t;
    bool test=t.connexion(id,password);
    if(test){ QMessageBox::information (nullptr, QObject::tr("OK"),
                                 QObject::tr("Connection effectué  avec succee\n"
                                             "Click Cancel to exit."), QMessageBox::Ok);
        MainWindow *w = new MainWindow();
        w->show();
        this->hide();


    }
    else{
        QMessageBox::information (nullptr, QObject::tr("warning"),
                                 QObject::tr("verifier votre corrdonait\n"
                                             "Click Cancel to exit."), QMessageBox::Ok);
    }
}

