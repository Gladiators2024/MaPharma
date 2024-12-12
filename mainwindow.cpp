#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "ui_mainwindow.h"
#include<QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include<QDebug>
#include"generateurpdf.h"
#include "arduino.h"
#include "arduino.cpp"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->framestat->hide();
    ui->type_r->hide();
    ui->date_r->hide();
    ui->tableView->setModel(Etmp.afficher());
    ui->tableView->hideColumn(8);
    test = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_ajouterButton_clicked_clicked()
{
    QString compteAssocie = ui->compteAssocieLineEdit->text();
    QString type = ui->type_combox->currentText();
    QDate date = ui->dateEdit_2->date();
    QString categorie = ui->categorie_box->currentText();
    double montant = ui->doubleSpinBox->value();
    QString modePaiement = ui->paymentbox->currentText();
    QString description = ui->descriptionLineEdit->text();
    QString idemp;




    Transactions trans( compteAssocie, type, date, categorie, montant, modePaiement, description,idemp );
    int test = trans.ajouter();

    if (test>0) {
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectué\n"), QMessageBox::Cancel);
            trans.crehistorique(test,"ajout");
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Ajout non effectué.\n"), QMessageBox::Cancel);
    }
    ui->tableView->setModel(trans.afficher());
    ui->tableView->hideColumn(8);
}


void MainWindow::on_modifierButton_clicked_clicked()
{
    if(ui->id_r->text().toInt()==0 || ui->id_r->text().toInt()==NULL){
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("chercher un id valide\n"), QMessageBox::Cancel);

    }
    else{

    QString compteAssocie = ui->compteAssocieLineEdit->text();
    QString type = ui->type_combox->currentText();
    QDate date = ui->dateEdit_2->date();
    QString categorie = ui->categorie_box->currentText();
    double montant = ui->doubleSpinBox->value();
    QString modePaiement = ui->paymentbox->currentText();
    QString description = ui->descriptionLineEdit->text();
    QString idemp;




    Transactions trans( compteAssocie, type, date, categorie, montant, modePaiement, description,idemp );
    bool test = trans.modifier(ui->id_lab->text().toInt());

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Modification effectué\n"), QMessageBox::Cancel);
        trans.crehistorique(ui->id_lab->text().toInt(),"modification");

    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Modification non effectué.\n"), QMessageBox::Cancel);
    }
    ui->tableView->setModel(trans.afficher());
    ui->tableView->hideColumn(8);}
}


void MainWindow::on_supprimerButton_clicked_clicked()
{
    if(ui->id_r->text().toInt()==0 || ui->id_r->text().toInt()==NULL){
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("chercher un id valide\n"), QMessageBox::Cancel);

    }
    else{
        Transactions trans;
        bool test = trans.supprimer(ui->id_lab->text().toInt());

        if (test) {
            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectué\n"), QMessageBox::Cancel);
            trans.crehistorique(ui->id_lab->text().toInt(),"Suppression");
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Suppression non effectué.\n"), QMessageBox::Cancel);
        }
        ui->tableView->setModel(trans.afficher());
        ui->tableView->hideColumn(8);
    }
    }





void MainWindow::on_recherche_combox_currentTextChanged(const QString &arg1)
{
    recherechtyp=ui->recherche_combox->currentText();
    if(recherechtyp=="ID"){
        ui->type_r->hide();
        ui->date_r->hide();
        ui->id_r->show();
    }
    else if(recherechtyp=="Categorie"){
        ui->type_r->show();
        ui->date_r->hide();
        ui->id_r->hide();
    }
    else if(recherechtyp=="Date"){
        ui->type_r->hide();
        ui->date_r->show();
        ui->id_r->hide();
    }
}
//// rech
void MainWindow::on_id_r_valueChanged(int arg1)
{

    int id =ui->id_r->value();
    Transactions tr;
    tr.rechercherParId(id);
    if(tr.getCompteAss()=="" || tr.getId_r()==NULL){
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("chercher un id valide\n"), QMessageBox::Cancel);

    }
    else{
    ui->id_lab->setNum(tr.getId_r());
    ui->compteAssocieLineEdit->setText(tr.getCompteAss());
    ui->type_combox->setCurrentText(tr.getTypeTr());
    ui->dateEdit_2->setDate(tr.getDateTr());
    ui->categorie_box->setCurrentText(tr.getCategorieTr());
    ui->doubleSpinBox->setValue(tr.getMontantTr());
    ui->paymentbox->setCurrentText(tr.getModePaiement());
    ui->descriptionLineEdit->setText(tr.getDescription());
    }
}

void MainWindow::on_type_r_currentTextChanged(const QString &arg1)
{
  QString  recherchepar=ui->type_r->currentText();
  QDate date;
    ui->tableView->setModel(Etmp.rechercher(recherechtyp,recherchepar,date));
    ui->tableView->hideColumn(8);

}

void MainWindow::on_date_r_userDateChanged(const QDate &date)
{
QDate recherpar=ui->date_r->date();
ui->tableView->setModel(Etmp.rechercher(recherechtyp,NULL,recherpar));
ui->tableView->hideColumn(8);

}
//tri





void MainWindow::on_radioButton_clicked()
{
    ui->tableView->setModel(Etmp.trier(ui->tri_combox->currentText(),true));
    ui->tableView->hideColumn(8);

}

void MainWindow::on_radioButton_2_clicked()
{
    ui->tableView->setModel(Etmp.trier(ui->tri_combox->currentText(),false));
    ui->tableView->hideColumn(8);

}

void MainWindow::on_pushButton_21_clicked()
{
    ui->tableView->setModel(Etmp.afficher());
ui->tableView->hideColumn(8);
}
void MainWindow::gethistorique(){
    Transactions trs;
   QWidget* scrollContent = new QWidget();
   QVBoxLayout* layout = new QVBoxLayout(scrollContent);
   layout->setAlignment(Qt::AlignTop);

   // Récupérer les messages
   QSqlQueryModel* model = trs.gethistorique();
   if (!model) {
       QLabel* errorLabel = new QLabel("Erreur : Impossible de récupérer les messages.");
       layout->addWidget(errorLabel);
       ui->scrollArea_3->setWidget(scrollContent);
       return;
   }
   qDebug()<<"HISTO" ;

   // Parcourir les messages et les afficher
   for (int row = 0; row < model->rowCount(); ++row) {

       QString Idtrans = model->data(model->index(row, 0)).toString();
       QString type = model->data(model->index(row, 1)).toString();
       QString date = model->data(model->index(row, 2)).toString();

       // Construire un format lisible pour le message
        QString messageText = QString("type: %1\nID transaction: %2\n fait a: %3")
                                 .arg(type)
                                 .arg(Idtrans)
                                 .arg(date);


       QLabel* messageLabel = new QLabel(messageText);
       messageLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
       messageLabel->setContentsMargins(0, 0, 0, 0);
       messageLabel->setWordWrap(true);

       messageLabel->setStyleSheet(
                   "background-color: rgb(174, 255, 123); "
                           "color: rgb(0, 51, 25); "
                           "font: 87 9pt 'Arial Black'; "
                           "border-radius: 10px; "
                           "border: 2px solid rgb(151, 181, 163); "
                           "padding: 10px; "
                           "margin: 5px;"
               );



    layout->addWidget(messageLabel);
   }

   // Configurer le QScrollArea avec le nouveau contenu
   scrollContent->setLayout(layout);
   ui->scrollArea_3->setWidget(scrollContent);
       }


void MainWindow::on_pushButton_22_clicked()
{
    ui->date_r->hide();
    ui->frame2->hide();
    ui->id_r->hide();
    ui->label_28->hide();
    ui->label_8->hide();
    ui->pushButton_21->hide();
    ui->pushButton_22->hide();
    ui->radioButton->hide();
    ui->radioButton_2->hide();
    ui->recherche_combox->hide();
    ui->tableView->hide();
    ui->tri_combox->hide();
    ui->type_r->hide();
    ui->framestat->show();
        gethistorique();
    QMap<QString, int> stats = Etmp.statistiquesParTypeEtCategorie();


    QPieSeries *series = new QPieSeries();
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        series->append(it.key(), it.value());
    }

    QChart *chart = new QChart();
        chart->addSeries(series);
    chart->setTitle("Statistiques des Transaction par Type");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(571, 291);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addWidget(chartView);
    ui->graphicsView_6->setScene(scene);



}

void MainWindow::on_pushButton_28_clicked()
{
    ui->date_r->show();
    ui->frame2->show();
    ui->id_r->show();
    ui->label_28->show();
    ui->label_8->show();
    ui->pushButton_21->show();
    ui->pushButton_22->show();
    ui->radioButton->show();
    ui->radioButton_2->show();
    ui->recherche_combox->show();
    ui->tableView->show();
    ui->tri_combox->show();
    ui->type_r->show();
    ui->framestat->hide();
}


void MainWindow::on_pdfbtn_clicked()
{
    QString nomFichierPDF = QFileDialog::getSaveFileName(this, "Enregistrer PDF", "", "Fichiers PDF (*.pdf)");

            if (!nomFichierPDF.isEmpty()) {
                QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tableView->model());

                if (model) {
                    GenerateurPDF::genererPDF(model, nomFichierPDF);
                } else {
                    QMessageBox::warning(this, "Erreur", "Le modèle n'est pas de type QSqlQueryModel.");
                }
            }
}

void MainWindow::openDoor() {
    QByteArray command = "open\n";  // Command to send to Arduino
    command = command.toLower();   // Convert to lowercase
    qDebug() << "Sending command to Arduino:" << command;
    A.write_to_arduino(command);    // Send the command
}

QString buffer;  // Declare a buffer to accumulate fragments

void MainWindow::update_label() {
    QByteArray data = A.read_from_arduino();  // Read data from Arduino
    qDebug() << "Raw data received from Arduino:" << data;

    buffer.append(QString(data));  // Append the new fragment to the buffer

    // Check if the buffer contains the delimiter for the end of the UID
    if (buffer.contains("\r\n")) {
        QString UID = buffer.trimmed();  // Trim spaces or newlines
        buffer.clear();  // Clear the buffer after processing the UID
        qDebug() << "Complete UID received:" << UID;

        // Convert UID to uppercase to ensure case consistency
        UID = UID.toUpper();
        if (!UID.isEmpty()) {
            QSqlQuery query;
            query.prepare("SELECT NOM_EMP, PRENOM_EMP FROM EYA.EMPLOYES WHERE CARD_UID = :uid");
            query.bindValue(":uid", UID);

            if (query.exec() && query.next()) {
                QString name = query.value("NOM_EMP").toString();  // Fetch name
                QString last_name = query.value("PRENOM_EMP").toString();
                QString fullName = name + " " + last_name;
                qDebug() << "Access granted for:" << name;
                ui->label_14->setText("Access granted!");
                ui->label_17->setText("Employee: " + fullName);
                openDoor();
                QTimer::singleShot(4000, this, [this]() {
                        ui->label_14->clear();
                        ui->label_17->clear();
                });

            } else {
                qDebug() << "Access denied: UID not found in database.";
                QTimer::singleShot(3000, this, [this]() {
                        ui->label_16->setText("Access denied: Invalid UID!");

                });
                ui->label_16->clear();
            }
        } else {
            qDebug() << "Empty UID detected.";
            ui->label_16->setText("No UID detected!");
        }
    } else {
        qDebug() << "Waiting for more data to complete the UID.";
    }
}

