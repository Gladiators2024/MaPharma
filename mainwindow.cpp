#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>
#include <QDebug>
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QSqlError>
#include <QDialog>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Ajout du QCalendarWidget à l'interface
        QCalendarWidget *calendar = new QCalendarWidget(this);
        calendar->setGridVisible(true);
        calendar->setGeometry(760, 60, 400, 250); // Position et taille
        calendar->setStyleSheet("background-color: #b0b5b1; border-radius: 10px;");

        // Connecter le signal clicked au slot
        connect(calendar, &QCalendarWidget::clicked, this, &MainWindow::on_onDate_clicked);

        // Exemple : Ajouter quelques événements
        events[QDate(2024, 12, 25)] = {"Noël", "Echange de cadeaux"};
        events[QDate(2024, 12, 31)] = {"Réveillon du Nouvel An"};

        events[QDate(2025, 1, 1)] = {"Jour de l'An", "Réunion de famille"};
        events[QDate(2025, 1, 14)] = {"Fête de la Révolution et de la Jeunesse"};

    // Initialiser l'affichage de la liste des fournisseurs dès le démarrage de l'application
    ui->affichage->setModel(fr.afficher());

    connect(ui->afficher, &QPushButton::clicked, this, &MainWindow::on_afficher_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
   if (ui->id->text().isEmpty() || ui->nom->text().isEmpty() || ui->adresse->text().isEmpty()|| ui->date->text().isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Veuillez remplir tous les champs obligatoires avec des valeurs valides."), QMessageBox::Ok);
        return;
    }

    int id_fournisseur = ui->id->text().toInt();
    QString nom_fr = ui->nom->text();
    QString adresse_fr = ui->adresse->text();
    int numero_fr = ui->numero->text().toInt();
    QString email_fr = ui->email->text();
    QString produit_fr = ui->produit->text();
    QString date_livraison_fr = ui->date->text();
    QString con_pai_fr = ui->conditions->text();
    QString ev_qu_fr = ui->evaluations->text();

    // Vérification des valeurs numériques
    if (id_fournisseur <= 0 || numero_fr <= 0 ) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Les valeurs numériques doivent être supérieures à zéro."), QMessageBox::Ok);
        return;
    }

    Fournisseur fournisseur(id_fournisseur, nom_fr, adresse_fr, numero_fr, email_fr, produit_fr, date_livraison_fr, con_pai_fr, ev_qu_fr);

    bool test = fournisseur.ajouter_fr();
    if (test) {
        ui->affichage->setModel(fr.afficher());  // Rafraîchit l'affichage
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    int id_fournisseur = ui->lineEdit_supp->text().toInt(); // Récupération de l'ID depuis l'interface
    bool test = fr.supprimer_fr(id_fournisseur); // Appel de la fonction supprimer_fr

    if (test) {
        ui->affichage->setModel(fr.afficher());  // Rafraîchit l'affichage
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_modif_clicked()
{
    int id_fournisseur = ui->id->text().toInt();

    // Chercher le fournisseur dans la base de données
    QSqlQuery query;
    query.prepare("SELECT nom_fr, adresse_fr, numero_fr, email_fr, produit_fr, date_livraison_fr, con_pai_fr, ev_qu_fr FROM FOURNISSEURS WHERE id_fournisseur = :id_fournisseur");
    query.bindValue(":id_fournisseur", id_fournisseur);

    if (query.exec()) {
        if (query.next()) {
            // Récupérer les informations et les afficher dans les champs appropriés
            ui->nom->setText(query.value("nom_fr").toString());
            ui->adresse->setText(query.value("adresse_fr").toString());
            ui->numero->setText(query.value("numero_fr").toString());
            ui->email->setText(query.value("email_fr").toString());
            ui->produit->setText(query.value("produit_fr").toString());
            ui->date->setText(query.value("date_livraison_fr").toString());
            ui->conditions->setText(query.value("con_pai_fr").toString());
            ui->evaluations->setText(query.value("ev_qu_fr").toString());
        } else {
            QMessageBox::warning(this, "Erreur", "Fournisseur introuvable.");
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de l'exécution de la requête.");
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    int id_fournisseur = ui->id->text().toInt();
    QString nom = ui->nom->text();
    QString adresse = ui->adresse->text();
    int numero = ui->numero->text().toInt();  // Conversion en entier
    QString email = ui->email->text();
    QString produit = ui->produit->text();
    QString date_livraison = ui->date->text();
    QString conditions = ui->conditions->text();
    QString evaluations = ui->evaluations->text();

    QSqlQuery query;
    query.prepare("UPDATE FOURNISSEURS SET nom_fr = :nom, adresse_fr = :adresse, numero_fr = :numero, email_fr = :email, produit_fr = :produit, date_livraison_fr = :date_livraison, con_pai_fr = :conditions, ev_qu_fr = :evaluations WHERE id_fournisseur = :id_fournisseur");
    query.bindValue(":id_fournisseur", id_fournisseur);
    query.bindValue(":nom", nom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":numero", numero);  // Utilisation du numéro converti
    query.bindValue(":email", email);
    query.bindValue(":produit", produit);
    query.bindValue(":date_livraison", date_livraison);
    query.bindValue(":conditions", conditions);
    query.bindValue(":evaluations", evaluations);

    if (query.exec()) {
        ui->affichage->setModel(fr.afficher());
        QMessageBox::information(this, "Succès", "Les informations du fournisseur ont été mises à jour.");
    } else {
        QMessageBox::warning(this, "Erreur", "La mise à jour a échoué.");
    }
}


void MainWindow::on_afficher_clicked()
{
    ui->affichage->setModel(fr.afficher());
}


void MainWindow::on_rechercher_clicked()
{    Fournisseur f;
     int id_fournisseur = ui->lineEditrecherche->text().toInt();
     qDebug() << "ID saisi pour la recherche :" << id_fournisseur;

     QSqlQueryModel* model = f.chercher_FOURNI(id_fournisseur);

     if (model->rowCount() == 0) {

         QMessageBox::information(this, "Recherche", "Aucun fournisseur trouvé avec cet ID.");
     } else {

         ui->tableViewrecherche->setModel(model);
         qDebug() << " trouvées :" << model->rowCount(); // Affichez le nombre de lignes
     }


}


void MainWindow::on_pushButton_trier_clicked()
{
    ui->affichage->setModel(fr.trier_par_id());

}


void MainWindow::on_pushButton_3_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->affichage->model()->rowCount();
    const int columnCount = ui->affichage->model()->columnCount();

    out << "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        << QString("<title>%1</title>\n").arg("Liste des Fournisseurs")
        << "</head>\n"
           "<body bgcolor=#CFC4E1 link=#5000A0>\n"
           "<h1>Liste des Fournisseurs</h1>"
           "<table border=1 cellspacing=0 cellpadding=2>\n";

    // En-têtes
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++) {
        out << QString("<th>%1</th>")
                   .arg(ui->affichage->model()->headerData(column, Qt::Horizontal).toString());
    }
    out << "</tr></thead>\n";

    // Données de la table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            QString data = ui->affichage->model()
                               ->data(ui->affichage->model()->index(row, column))
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


void MainWindow::on_pushButton_stat_clicked()
{
    QSqlQuery query;
            query.prepare("SELECT adresse_fr, COUNT(*) as count FROM FOURNISSEURS GROUP BY adresse_fr");

            if (!query.exec()) {
                qDebug() << "Error fetching statistics:" << query.lastError().text();
                return;
            }

            // Create a QPieSeries to hold the data
            QPieSeries *series = new QPieSeries();

            // Populate the series with the results of the query
            while (query.next()) {
                QString address = query.value(0).toString();
                int count = query.value(1).toInt();
                series->append(address, count);
            }

            // Customize the chart (optional)
            for (auto slice : series->slices()) {
                slice->setLabel(QString("%1 (%2)").arg(slice->label()).arg(slice->value()));
            }

            // Create the chart and set the series
            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Statistics of Suppliers by Address");
            chart->legend()->setAlignment(Qt::AlignBottom);

            // Display the chart in a QChartView
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            // Show the chart in a new window or widget
                    chartView->setParent(this);
                    chartView->resize(500, 220);
                    chartView->move(250, 60);

                    chartView->show();

}


void MainWindow::on_pushButton_4_clicked()
{
    // Create a custom dialog for chat display
        QDialog *chatDialog = new QDialog(this);
        chatDialog->setWindowTitle("Chatbot");
        chatDialog->setFixedSize(600, 400);

        QVBoxLayout *layout = new QVBoxLayout(chatDialog);

        // Add QTextEdit for displaying chat messages
        QTextEdit *chatTextEdit = new QTextEdit(chatDialog);
        chatTextEdit->setReadOnly(true);
        chatTextEdit->setStyleSheet("QTextEdit { color: white; background-color: #34495E; border-radius: 10px; padding: 15px; font-family: 'Montserrat', sans-serif; font-size: 12px; }");
        layout->addWidget(chatTextEdit);

        // Add QLineEdit for user input
        QLineEdit *inputLineEdit = new QLineEdit(chatDialog);
        inputLineEdit->setPlaceholderText("Type your question here...");
        inputLineEdit->setStyleSheet("QLineEdit { background-color: #ECF0F1; border-radius: 10px; padding: 10px; font-family: 'Montserrat', sans-serif; font-size: 12px; }");
        layout->addWidget(inputLineEdit);

        // Add QPushButton for sending the message
        QPushButton *sendButton = new QPushButton("Send", chatDialog);
        sendButton->setStyleSheet("QPushButton { color: white; background-color: #3498DB; border: none; padding: 5px 15px; font-family: 'Montserrat', sans-serif; font-size: 12px; }"
                                  "QPushButton:hover { background-color: #2980B9; }");
        layout->addWidget(sendButton);

        // Add a '?' button to display chatbot instructions
        QPushButton *helpButton = new QPushButton("HELP", chatDialog);
        helpButton->setToolTip("Click for topics");
        layout->addWidget(helpButton);

        // Connect the clicked signal of the helpButton to a slot
        connect(helpButton, &QPushButton::clicked, [=]() {
            // Display a message box with the list of topics
            QMessageBox::information(chatDialog, "Informations", "Vous pouvez poser des questions sur :\n"
            "- event \n"
            "- new \n");
        });

        chatDialog->setLayout(layout);

        // Connect sendButton clicked signal to process the question
        connect(sendButton, &QPushButton::clicked, [=]() {
            QString question = inputLineEdit->text().simplified().toLower(); // Normalize and convert to lowercase

            // Check if the user input is empty
            if (question.isEmpty()) {
                QMessageBox::warning(this, "Empty Question", "Please ask a question for the chatbot.");
                return;
            }

            // Process the user's question and provide an appropriate response
            QString response;
            if (question.indexOf("event", 0, Qt::CaseInsensitive) != -1) {
                response = "Our company hosts a variety of events, including talent shows, game nights, movie screenings, and live performances.";
            } else if (question.indexOf("new", 0, Qt::CaseInsensitive) != -1) {
                response = "We are excited to announce the launch of our new medication, HealthPro 24, designed to boost immunity and enhance overall well-being. For a limited time, enjoy a 20% discount at participating pharmacies. Contact us for more details!";
            } else {
                response = "Sorry, I don't have information on that topic. Please ask another question or contact our support team for assistance.";
            }
            chatTextEdit->append(QString("<b>User:</b> %1<br><b>Bot:</b> %2").arg(question).arg(response));
            inputLineEdit->clear();
        });



        // Display the chat dialog
        chatDialog->exec();
}





void MainWindow::on_onDate_clicked(const QDate &date)
{
    if (events.contains(date)) {
        QString eventList = events[date].join("\n"); // Combine les événements pour cette date
        QMessageBox::information(this, "Événements du jour", QString("Événements pour %1:\n%2").arg(date.toString("dd/MM/yyyy"), eventList));
    } else {
        QMessageBox::information(this, "Pas d'événements", QString("Aucun événement prévu pour %1").arg(date.toString("dd/MM/yyyy")));
    }
}

