#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "medicament.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QRegularExpression>
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QSqlError>
#include "qrcode.h"
#include "qrcodegen.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <QPixmap>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QSvgGenerator>
#include <QPainter>
#include <QLabel>
#include <QTimer>
#include <QScreen>
#include <QGuiApplication>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(medTmp.afficher());
    verifier_quantites_med();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_on_pushButton_ajouterMed_clicked()
{
    if (ui->lineEdit_ID->text().isEmpty() || ui->lineEdit_Quantite->text().isEmpty() || ui->lineEdit_Prix->text().isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Veuillez remplir tous les champs obligatoires avec des valeurs valides."), QMessageBox::Ok);
        return;
    }

    int id_medicament = ui->lineEdit_ID->text().toInt();
    QString nom_med = ui->lineEdit_nom_med->text();
    int dosage_med = ui->lineEdit_Dosage_2->text().toInt();
    QString date_expiration_med = ui->lineEdit_Date->text();
    int quantite_med = ui->lineEdit_Quantite->text().toInt();
    double prix_med = ui->lineEdit_Prix->text().toDouble();

    if (id_medicament <= 0 || quantite_med <= 0 || prix_med <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Les valeurs numériques doivent être supérieures à zéro."), QMessageBox::Ok);
        return;
    }
    QRegularExpression regex("^[a-zA-Z\\s]+$");
        if (!regex.match(nom_med).hasMatch()) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("Le nom doit contenir uniquement des lettres et des espaces."), QMessageBox::Ok);
            return;
        }

        if (nom_med.length() < 3 || nom_med.length() > 50) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("Le nom doit contenir entre 3 et 50 caractères."), QMessageBox::Ok);
            return;
        }


    Medicament med(id_medicament, nom_med, dosage_med, date_expiration_med, quantite_med, prix_med);

    bool test = med.ajouter_med();
    if (test) {
        ui->tableView->setModel(medTmp.afficher());
        verifier_quantites_med();
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    int id = ui->lineEdit->text().toInt();
    bool test = medTmp.supprimer_med(id);

    if (test)
    {   ui->tableView->setModel(medTmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}




void MainWindow::on_modifier1_clicked()
{
     int id_medicament = ui->lineEdit->text().toInt();

    QSqlQuery query;
    query.prepare("SELECT * FROM medicament WHERE id_medicament = :id_medicament");
    query.bindValue(":id_medicament", id_medicament);

    if (query.exec()) {
        if (query.next()) {
            ui->lineEdit_ID_2->setText(query.value("id_medicament").toString());
            ui->lineEdit_nom_med_2->setText(query.value("nom_med").toString());
            ui->lineEdit_Dosage_4->setText(query.value("dosage_med").toString());
            ui->lineEdit_Date_2->setText(query.value("date_expiration_med").toString());
            ui->lineEdit_Quantite_2->setText(query.value("quantite_med").toString());
            ui->lineEdit_Prix_2->setText(query.value("prix_med").toString());

            ui->stackedWidget->setCurrentIndex(1);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("Aucun médicament trouvé avec cet ID."), QMessageBox::Ok);
        }
    }
}


void MainWindow::on_modifier2_clicked()
{

        int id_medicament = ui->lineEdit_ID_2->text().toInt();
        QString nom_med = ui->lineEdit_nom_med_2->text();
        int dosage_med = ui->lineEdit_Dosage_4->text().toInt();;
        QString date_expiration_med = ui->lineEdit_Date_2->text();
        int quantite_med = ui->lineEdit_Quantite_2->text().toInt();
        double prix_med = ui->lineEdit_Prix_2->text().toDouble();

        if (id_medicament <= 0 || quantite_med <= 0 || prix_med <= 0) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("Les valeurs numériques doivent être supérieures à zéro."), QMessageBox::Ok);
            return;
        }
        QRegularExpression regex("^[a-zA-Z\\s]+$");
            if (!regex.match(nom_med).hasMatch()) {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                      QObject::tr("Le nom doit contenir uniquement des lettres et des espaces."), QMessageBox::Ok);
                return;
            }

            if (nom_med.length() < 3 || nom_med.length() > 50) {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                      QObject::tr("Le nom doit contenir entre 3 et 50 caractères."), QMessageBox::Ok);
                return;
            }

        Medicament med;
        if (med.modifier_med(id_medicament, nom_med, dosage_med, date_expiration_med, quantite_med, prix_med)) {
            verifier_quantites_med();
            QMessageBox::information(nullptr, QObject::tr("Succès"),
                                     QObject::tr("Mise à jour effectuée avec succès."), QMessageBox::Ok);
            ui->tableView->setModel(medTmp.afficher());
            ui->stackedWidget->setCurrentIndex(0);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("La mise à jour a échoué."), QMessageBox::Ok);
        }
}


void MainWindow::on_pushButton_4_clicked()
{
    Medicament m;
        int id = ui->lineEdit_2->text().toInt();
        qDebug() << "ID saisi pour la recherche :" << id;

        QSqlQueryModel* model = m.chercher_med(id);

        if (model->rowCount() == 0) {

            QMessageBox::information(this, "Recherche", "Aucun médicament trouvé avec cet ID.");
        } else {

            ui->tableView_6->setModel(model);
            qDebug() << "Nombre de lignes trouvées :" << model->rowCount(); // Affichez le nombre de lignes
        }
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->tableView->setModel(medTmp.trier_par_id());
}


void MainWindow::on_pushButton_10_clicked()
{
    ui->tableView->setModel(medTmp.trier_par_quantite());
}


void MainWindow::on_pushButton_clicked()
{
    QString strStream;
        QTextStream out(&strStream);

        const int rowCount = ui->tableView->model()->rowCount();
        const int columnCount = ui->tableView->model()->columnCount();

        out << "<html>\n"
               "<head>\n"
               "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            << QString("<title>%1</title>\n").arg("Liste des Médicaments")
            << "</head>\n"
               "<body bgcolor=#c4e1c8 link=#5000A0>\n"
               "<h1>Liste des Médicaments</h1>"
               "<table border=1 cellspacing=0 cellpadding=2>\n";

        // En-têtes
        out << "<thead><tr bgcolor=#f0f0f0>";
        for (int column = 0; column < columnCount; column++) {
            out << QString("<th>%1</th>")
                       .arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
        }
        out << "</tr></thead>\n";

        // Données de la table
        for (int row = 0; row < rowCount; row++) {
            out << "<tr>";
            for (int column = 0; column < columnCount; column++) {
                QString data = ui->tableView->model()
                                   ->data(ui->tableView->model()->index(row, column))
                                   .toString()
                                   .simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
            out << "</tr>\n";
        }
        out << "</table>\n"
               "</body>\n"
               "</html>\n";

        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);

        // Créez un dialogue pour que l'utilisateur choisisse l'emplacement de sauvegarde
        QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer le fichier PDF", "", "*.pdf");
        if (filePath.isEmpty()) {
            return; // Annule si aucun fichier n'a été sélectionné
        }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filePath);
        document->print(&printer);

        QMessageBox::information(this, "PDF Créé", "Le fichier PDF a été créé avec succès !");
}


void MainWindow::on_pushButton_8_clicked()
{
    // Créer une requête SQL pour obtenir les noms et quantités des médicaments
    QSqlQuery query;
    query.prepare("SELECT nom_med, quantite_med FROM medicament");

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des statistiques :" << query.lastError().text();
        return;
    }

    // Créer une QPieSeries pour contenir les données
    QPieSeries *series = new QPieSeries();

    // Remplir la série avec les résultats de la requête
    while (query.next()) {
        QString nom = query.value(0).toString(); // Nom du médicament
        int quantite = query.value(1).toInt();  // Quantité

        // Ajouter le nom et la quantité comme étiquette
        QString label = QString("%1 (%2)").arg(nom).arg(quantite);
        series->append(label, quantite);
    }

    // Personnaliser les étiquettes (facultatif)
    for (auto slice : series->slices()) {
        slice->setLabelVisible();
        slice->setLabel(QString("%1 : %2").arg(slice->label()).arg(slice->percentage() * 100, 0, 'f', 1) + "%");
    }

    // Créer le graphique et ajouter la série
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des Médicaments par Quantité");
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Afficher le graphique dans un QChartView
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Afficher le graphique dans la troisième page du stackedWidget
    QWidget *statPage = ui->stackedWidget->widget(2); // Page index 2
    QVBoxLayout *layout = new QVBoxLayout(statPage);
    layout->addWidget(chartView);

    // Afficher la troisième page avec les statistiques
    ui->stackedWidget->setCurrentIndex(2);
}



void MainWindow::on_cancel_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_2_clicked()
{
    QString inputText = ui->lineEdit_nom_med->text().trimmed();

    if (inputText.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le champ de texte est vide !");
        return;
    }

    // Vérifier si le médicament existe dans la base
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM medicament WHERE TRIM(LOWER(nom_med)) = TRIM(LOWER(:nom_med))");
    query.bindValue(":nom_med", inputText);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", "Erreur lors de l'exécution de la requête : " + query.lastError().text());
        return;
    }

    query.next();
    int count = query.value(0).toInt();

    if (count == 0) {
        QMessageBox::warning(this, "Erreur", "Le médicament '" + inputText + "' n'existe pas dans la base de données !");
        return;
    }

    // Générer le QR Code si le médicament existe
    const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(inputText.toStdString().c_str(), qrcodegen::QrCode::Ecc::LOW);
    std::ofstream myfile;
    myfile.open("qrcode.svg");
    myfile << qr.toSvgString(1);
    myfile.close();

    QSvgRenderer svgRenderer(QString("qrcode.svg"));
    QPixmap pix(QSize(90, 90));
    QPainter pixPainter(&pix);
    svgRenderer.render(&pixPainter);
    ui->label_4->setPixmap(pix);

    QMessageBox::information(this, "Succès", "Le QR Code a été généré avec succès !");
}

void MainWindow::verifier_quantites_med() {
    QList<int> ids = medTmp.verifier_quantites();

    if (!ids.isEmpty()) {
        QString message = "Attention ! Les médicaments suivants ont une quantité inférieure à 10 :\n";
        for (int id : ids) {
            message += "- ID : " + QString::number(id) + "\n";
        }

        // Créer un QLabel pour afficher le message
        QLabel *notification = new QLabel(this);
        notification->setText(message);
        notification->setStyleSheet(
            "background-color: #f8d7da; color: #721c24; "
            "border: 1px solid #f5c6cb; border-radius: 5px; "
            "padding: 10px; font-size: 14px;"
        );
        notification->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
        notification->adjustSize();

        // Récupérer la géométrie de l'écran
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();

        // Placer la notification dans le coin inférieur droit
        int x = screenGeometry.width() - notification->width() - 50;
        int y = screenGeometry.height() - notification->height() - 50;
        notification->move(x, y);

        // Afficher la notification
        notification->show();

        // Supprimer automatiquement la notification après 10 secondes
        QTimer::singleShot(10000, notification, &QLabel::deleteLater);
    }
}

