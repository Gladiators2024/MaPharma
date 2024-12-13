#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "client.h"
#include <QRegularExpression>
#include <QSqlQuery>
#include <QFileDialog>
#include <QPainter>
#include <QPrinter>
#include <QtCharts>
#include <QChartView>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QFont>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

const QRegularExpression MainWindow::emailRegex("[\\w\\.-]+@[\\w\\.-]+\\.[a-z]{2,4}");
const QRegularExpression MainWindow::telRegex("^\\d{8}$");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->afficherListe->setModel(client.afficher());
    ui->tableView_5->setModel(client.afficher());

    connect(ui->boutonRetour, &QPushButton::clicked, this, &MainWindow::retourVersMain);
    connect(ui->exporter_pdf, &QPushButton::clicked, this, &MainWindow::exporterVersPDF);
    connect(ui->afficherListe, &QTableView::clicked, this, &MainWindow::remplirChamps);
    connect(ui->showstats, &QPushButton::clicked, this, &MainWindow::on_showstats_clicked);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_currentIndexChanged(int)));
    connect(ui->pushButton_rechercher, &QPushButton::clicked, this, &MainWindow::on_pushButton_rechercher_clicked);
    connect(ui->lerechercher, &QLineEdit::textChanged, this, &MainWindow::on_lerechercher_textChanged);

    // Dans le constructeur de MainWindow ou la méthode d'initialisation
    connect(ui->passerAppelButton, &QPushButton::clicked, this, &MainWindow::appelerClientSlot);
    connect(ui->envoyerSMSButton, &QPushButton::clicked, this, &MainWindow::envoyerSMSSlot);

}

void MainWindow::retourVersMain()
{
    ui->stackedWidget->setCurrentWidget(ui->main);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int QDateToInt(QDate date)
{
    return date.year() * 10000 + date.month() * 100 + date.day();
}

void MainWindow::on_ajouter_3_clicked()
{
    QString nom_cl = ui->NOM->text().trimmed();
    QString prenom_cl = ui->PRENOM->text().trimmed();
    QString adresse_cl = ui->Adresse->text().trimmed();
    QString email_cl = ui->EMAIL->text().trimmed();
    int id_cl = ui->ID->text().toInt();
    QString tel_cl_str = ui->TEL->text().trimmed();
    int date_naissance_cl = QDateToInt(ui->DATE->date());

    if (nom_cl.isEmpty() || prenom_cl.isEmpty() || adresse_cl.isEmpty() || email_cl.isEmpty()) {
        QMessageBox::warning(this, tr("Champs manquants"), tr("Veuillez remplir tous les champs requis."));
        return;
    }

    QRegularExpression nameRegex("^[a-zA-ZÀ-ÿ\\s-]+$");
    if (!nameRegex.match(nom_cl).hasMatch()) {
        QMessageBox::warning(this, tr("Nom invalide"), tr("Le nom ne doit contenir que des lettres."));
        return;
    }
    if (!nameRegex.match(prenom_cl).hasMatch()) {
        QMessageBox::warning(this, tr("Prénom invalide"), tr("Le prénom ne doit contenir que des lettres."));
        return;
    }

    if (!emailRegex.match(email_cl).hasMatch()) {
        QMessageBox::warning(this, tr("Email invalide"), tr("Veuillez entrer une adresse e-mail valide."));
        return;
    }

    if (!telRegex.match(tel_cl_str).hasMatch()) {
        QMessageBox::warning(this, tr("Numéro de téléphone invalide"), tr("Veuillez entrer un numéro de téléphone valide de 8 chiffres."));
        return;
    }

    if (id_cl <= 0 || ui->ID->text().contains(QRegularExpression("\\D"))) {
        QMessageBox::warning(this, tr("ID invalide"), tr("L'ID doit être un nombre positif."));
        return;
    }

    if (ui->DATE->date() > QDate::currentDate()) {
        QMessageBox::warning(this, tr("Date de naissance invalide"), tr("La date de naissance ne peut pas être dans le futur."));
        return;
    }

    int tel_cl = tel_cl_str.toInt();

    class client client(id_cl, nom_cl, prenom_cl, adresse_cl, email_cl, tel_cl, date_naissance_cl);
    bool test = client.ajouter();

    if (test) {
        ui->afficherListe->setModel(client.afficher());
        QMessageBox::information(this, QObject::tr("OK"), QObject::tr("Ajout effectué.\nCliquez sur Annuler pour quitter."));
    } else {
        ui->afficherListe->setModel(client.afficher());
        QMessageBox::critical(this, QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\nCliquez sur Annuler pour quitter."));
    }
}

void MainWindow::on_supprimer_clicked()
{
    int id_Clients = ui->lerechercher->text().toInt();

    if (!client.existe(id_Clients)) {
        QMessageBox::warning(this, QObject::tr("ID non trouvé"),
            QObject::tr("Cet ID n'existe pas. \n"
                        "Vérifiez l'ID et réessayez."), QMessageBox::Ok);
        return;
    }

    bool test = client.supprimer(id_Clients);

    if (test) {
        ui->afficherListe->setModel(client.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
            QObject::tr("Suppression effectuée \n"
                        "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Échec"),
            QObject::tr("La suppression n'a pas été effectuée \n"
                        "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
}

void MainWindow::on_comboBox_currentIndexChanged() {
    QString colonne = ui->comboBox->currentText(); // Récupère la colonne sélectionnée
    QSqlQueryModel* sortedModel = client.trierClients(colonne);

    if (sortedModel) {
        ui->afficherListe->setModel(nullptr); // Réinitialiser le modèle avant d'appliquer le nouveau
        ui->afficherListe->setModel(sortedModel);
        qDebug() << "Tri appliqué avec succès sur la colonne :" << colonne;
    } else {
        qDebug() << "Erreur : Impossible d'appliquer le tri pour la colonne :" << colonne;
    }
}

void MainWindow::on_afficher_clicked()
{
    QSqlQueryModel* model = client.afficher();

    if (!model) {
        qDebug() << "Erreur lors de la mise à jour du modèle de vue.";
        return;
    }

    ui->afficherListe->setModel(model);
}

void MainWindow::exporterVersPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer PDF"), "", tr("Fichiers PDF (*.pdf)"));
    if (fileName.isEmpty()) {
        return;
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QPainter painter(&printer);

    // Définir les polices et styles
    QFont titleFont("Arial", 18, QFont::Bold);
    QFont headerFont("Arial", 12, QFont::Bold);
    QFont rowFont("Arial", 10);

    // Dessiner un titre ou un logo
    painter.setFont(titleFont);
    painter.setPen(Qt::black);
    painter.drawText(4000, 100, "Liste des Clients");

    // Récupération des données
    QSqlQueryModel* model = client.afficher();
    if (!model) {
        QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors de la récupération des données des clients."));
        return;
    }

    int x = 200;  // Coordonnée de départ en x
    int y = 250;  // Coordonnée de départ en y
    int lineHeight = 300;  // Hauteur des lignes
    int spaceBetweenLines = 50;  // Espace entre les lignes
    int columnWidths[] = {500, 1200, 1200, 1200, 1800, 1200, 2100};

    QStringList headers = {"ID", "Nom", "Prénom", "Adresse", "Email", "Téléphone", "Date de Naissance"};

    // Dessiner l'en-tête du tableau
    painter.setFont(headerFont);
    painter.setBrush(QColor(200, 200, 255)); // Couleur d'arrière-plan
    int currentX = x;
    for (int i = 0; i < headers.size(); ++i) {
        painter.drawRect(currentX, y, columnWidths[i], lineHeight);
        painter.drawText(currentX + 10, y + 200, headers[i]);
        currentX += columnWidths[i];
    }
    y += lineHeight + spaceBetweenLines;

    // Dessiner les lignes du tableau
    painter.setFont(rowFont);
    for (int i = 0; i < model->rowCount(); ++i) {
        currentX = x;

        // Alternance des couleurs
        if (i % 2 == 0) {
            painter.setBrush(QColor(240, 240, 240)); // Ligne claire
        } else {
            painter.setBrush(QColor(255, 255, 255)); // Ligne blanche
        }

        for (int j = 0; j < headers.size(); ++j) {
            painter.drawRect(currentX, y, columnWidths[j], lineHeight);
            painter.drawText(currentX + 10, y + 200, model->data(model->index(i, j)).toString());
            currentX += columnWidths[j];
        }

        y += lineHeight + spaceBetweenLines;

        // Gestion de nouvelle page
        if (y + lineHeight + spaceBetweenLines > printer.height() - 50) {
            painter.end();
            printer.newPage();
            painter.begin(&printer);
            y = 150;

            // Ré-afficher l'en-tête sur une nouvelle page
            currentX = x;
            for (int k = 0; k < headers.size(); ++k) {
                painter.setBrush(QColor(200, 200, 255));
                painter.drawRect(currentX, y, columnWidths[k], lineHeight);
                painter.drawText(currentX + 10, y + 200, headers[k]);
                currentX += columnWidths[k];
            }
            y += lineHeight + spaceBetweenLines;
        }
    }

    painter.end();

    QMessageBox::information(this, tr("PDF Exporté"), tr("Les informations des clients ont été exportées avec succès dans le fichier PDF."));
}


void MainWindow::on_exporter_pdf_clicked()
{
        connect(ui->exporter_pdf, &QPushButton::clicked, this, &MainWindow::exporterVersPDF);
}

void MainWindow::on_pushButton_rechercher_3_clicked()
{
    int id_Clients = ui->lerechercher->text().toInt();

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT nom_cl, prenom_cl, adresse_cl, email_cl, tel_cl, date_naissance_cl FROM CLIENTS WHERE id_Clients = :id_Clients");
    checkQuery.bindValue(":id_Clients", id_Clients);

    if (!checkQuery.exec()) {
        QMessageBox::critical(nullptr, "Erreur", "Échec de la recherche du client dans la base de données !");
        return;
    }

    if (checkQuery.next()) {
        QString nom_cl = checkQuery.value(0).toString();
        QString prenom_cl = checkQuery.value(1).toString();
        QString adresse_cl = checkQuery.value(2).toString();
        QString email_cl = checkQuery.value(3).toString();
        QString tel_cl = checkQuery.value(4).toString();
        QString date_naissance_cl = checkQuery.value(5).toString();

        QDate dateDeNaissanceDate = QDate::fromString(date_naissance_cl, "yyyy-MM-dd");

        ui->NN->setText(nom_cl);
        ui->NP->setText(prenom_cl);
        ui->NA->setText(adresse_cl);
        ui->ND->setDate(dateDeNaissanceDate);
        ui->NE->setText(email_cl);
        ui->NT->setText(tel_cl);

        ui->lerechercher->setReadOnly(true);

        ui->stackedWidget->setCurrentWidget(ui->modifier);
    } else {
        QMessageBox::warning(nullptr, "Erreur", "ID de client non trouvé dans la base de données !");
    }
}

void MainWindow::on_modifier_2_clicked()
{
    int id_Clients = ui->lerechercher->text().toInt();

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM CLIENTS WHERE id_Clients = :id_Clients");
    checkQuery.bindValue(":id_Clients", id_Clients);

    if (!checkQuery.exec()) {
        QMessageBox::critical(nullptr, "Erreur", "Échec de la vérification de l'existence du client dans la base de données !");
        return;
    }

    if (!checkQuery.next()) {
        QMessageBox::warning(nullptr, "Erreur", "ID de client non trouvé dans la base de données !");
        return;
    }

    QString nom_cl = ui->NOM->text();
    QString prenom_cl = ui->PRENOM->text();
    QString adresse_cl = ui->Adresse->text();
    int tel_cl = ui->TEL->text().toInt();
    QString email_cl = ui->EMAIL->text();
    QString date_naissance_cl = ui->DATE->text();

    QString nouvnom = ui->NN->text();
    QString nouvprenom = ui->NP->text();
    QString nouvadresse = ui->NA->text();
    int nouvtelephone = ui->NT->text().toInt();
    QString nouvemail = ui->NE->text();
    QString nouvdateDeNaissanceDate = ui->ND->date().toString("yyyy-MM-dd");

    if (nom_cl != nouvnom || prenom_cl != nouvprenom || email_cl != nouvemail ||
        adresse_cl != nouvadresse || tel_cl != nouvtelephone ||
        date_naissance_cl != nouvdateDeNaissanceDate)
    {

        bool modificationReussie = client.modifier(id_Clients, nouvnom, nouvprenom, nouvadresse, nouvemail, nouvdateDeNaissanceDate, nouvtelephone);

        if (modificationReussie) {

            ui->tableView_5->setModel(client.afficher());

            QMessageBox::information(this, "Succès", "Client modifié avec succès !");

            ui->stackedWidget->setCurrentWidget(ui->modifier);
        } else {
            QMessageBox::warning(this, "Erreur", "Erreur lors de la modification du client !");
        }
    } else {
        QMessageBox::information(this, "Information", "Aucune modification n'a été apportée.");
    }

    qDebug() << "Nouvelles valeurs:" << nouvnom << nouvprenom << nouvadresse << nouvemail << nouvdateDeNaissanceDate << nouvtelephone;

}

void MainWindow::on_boutonRetour_clicked()
{
        connect(ui->boutonRetour, &QPushButton::clicked, this, &MainWindow::retourVersMain);
}

void MainWindow::remplirChamps(const QModelIndex &index)
{
    QAbstractItemModel *model = ui->afficherListe->model();

    QString id_Clients = model->data(model->index(index.row(), 0)).toString();
    QString nom_cl = model->data(model->index(index.row(), 1)).toString();
    QString prenom_cl = model->data(model->index(index.row(), 2)).toString();
    QString adresse_cl = model->data(model->index(index.row(), 3)).toString();
    QString tel_cl = model->data(model->index(index.row(), 4)).toString();
    QString email_cl = model->data(model->index(index.row(), 5)).toString();

    QString date_naissance_cl = model->data(model->index(index.row(), 6)).toString();
    QDate date_naissance_str = QDate::fromString(date_naissance_cl, "yyyy-MM-dd");

    ui->ID->setText(id_Clients);
    ui->NOM->setText(nom_cl);
    ui->PRENOM->setText(prenom_cl);
    ui->Adresse->setText(adresse_cl);
    ui->EMAIL->setText(tel_cl);
    ui->TEL->setText(email_cl);
    ui->DATE->setDate(date_naissance_str);
}

void MainWindow::on_showstats_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stats);

    QSqlQuery query;
    query.exec("SELECT adresse_cl, COUNT(*) FROM Clients GROUP BY adresse_cl ORDER BY adresse_cl");

    QPieSeries *series = new QPieSeries();

    QColor colors[] = {Qt::blue, Qt::green, Qt::red, Qt::yellow, Qt::cyan, Qt::magenta, Qt::gray, Qt::darkBlue, Qt::darkGreen, Qt::darkRed};

    int colorIndex = 0;

    while (query.next()) {
        QString adresse = query.value(0).toString();
        int count = query.value(1).toInt();

        QPieSlice *slice = series->append(adresse, count);
        slice->setLabelVisible();
        slice->setLabel(QString("%1: %2").arg(adresse).arg(count));

        slice->setColor(colors[colorIndex % (sizeof(colors) / sizeof(QColor))]);

        slice->setPen(QPen(QColor(50, 50, 50)));

        colorIndex++;
    }

    QChart *chart = new QChart();
    chart->setTitle("Statistiques des clients par adresse");
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chart->setBackgroundRoundness(10);
    chart->setBackgroundBrush(QBrush(QColor(227, 252, 242)));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setRenderHint(QPainter::TextAntialiasing);

    chartView->setStyleSheet("border-radius: 15px; border: 3px solid #285c47;");

    ui->stackedWidget->addWidget(chartView);
    ui->stackedWidget->setCurrentWidget(chartView);
}

void MainWindow::on_pushButton_clicked()
{
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::retourVersMain);
}



void MainWindow::on_lerechercher_textChanged(const QString &critere)
{
    class client c;
        QSqlQueryModel* model = c.chercherClient(critere);

        if (model) {
            // Si des résultats sont trouvés, on les affiche dans le QTableView
            ui->afficherListe->setModel(model);
        } else {
            // Sinon, on vide le QTableView
            ui->afficherListe->setModel(nullptr);
            qDebug() << "Aucun client trouvé avec ce critère.";
        }
}

void MainWindow::on_pushButton_rechercher_clicked()
{
    QString critere = ui->lerechercher->text();  // Récupérer le critère de recherche depuis un QLineEdit

    class client c;  // Créer un objet de type client
    QSqlQueryModel* model = c.chercherClient(critere);  // Appeler la méthode de recherche

    if (model) {
        ui->afficherListe->setModel(model);  // Mettre à jour le QTableView avec le modèle
    } else {
        // Si aucun client n'est trouvé
        ui->afficherListe->setModel(nullptr);
        qDebug() << "Aucun client trouvé avec ce critère.";
    }
}

