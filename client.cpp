#include "client.h"
#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QDesktopServices>
#include <QUrl>

client::client()
{
    id_Clients=0;
    nom_cl=" ";
    prenom_cl=" ";
    adresse_cl=" ";
    email_cl=" ";
    tel_cl=0;
    date_naissance_cl=0;
}

client::client(int id_Clients,QString nom_cl, QString prenom_cl, QString adresse_cl, QString email_cl, int tel_cl, int date_naissance_cl)
{
    this->id_Clients=id_Clients;
    this->nom_cl=nom_cl;
    this->prenom_cl=prenom_cl;
    this->adresse_cl=adresse_cl;
    this->email_cl=email_cl;
    this->tel_cl=tel_cl;
    this->date_naissance_cl=date_naissance_cl;
}

bool client::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO clients (id_Clients, nom_cl, prenom_cl, adresse_cl, email_cl, tel_cl, date_naissance_cl) "
                  "VALUES (:id_Clients, :nom_cl, :prenom_cl, :adresse_cl, :email_cl, :tel_cl, :date_naissance_cl)");

    query.bindValue(":id_Clients", id_Clients);
    query.bindValue(":nom_cl", nom_cl);
    query.bindValue(":prenom_cl", prenom_cl);
    query.bindValue(":adresse_cl", adresse_cl);
    query.bindValue(":email_cl", email_cl);
    query.bindValue(":tel_cl", tel_cl);
    query.bindValue(":date_naissance_cl", QDate::fromString(QString::number(date_naissance_cl), "yyyyMMdd"));

    return query.exec();
}

QSqlQueryModel* client::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT id_Clients, nom_cl, prenom_cl, adresse_cl, email_cl, tel_cl, date_naissance_cl FROM CLIENTS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date de naissance"));

    return model;
}

bool client::existe(int id_Clients)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CLIENTS WHERE id_Clients = :id");
    query.bindValue(":id", id_Clients);
    if (query.exec() && query.next())
    {
        return query.value(0).toInt() > 0;
    }
    return false;
}

bool client::supprimer(int id_Clients)
{
   QSqlQuery query;

    query.prepare("DELETE FROM CLIENTS WHERE id_Clients = :id_Clients");

   query.bindValue(":id_Clients", id_Clients);

return query.exec();

}

bool client::modifier(int id_Clients, const QString &nom_cl, const QString &prenom_cl, const QString &adresse_cl,
                      const QString &email_cl, const QString &date_naissance_cl, int tel_cl) {
    QSqlQuery query;
    query.prepare("UPDATE CLIENTS SET nom_cl = :nom_cl, prenom_cl = :prenom_cl, "
                  "adresse_cl = :adresse_cl, email_cl = :email_cl, "
                  "date_naissance_cl = TO_DATE(:date_naissance_cl, 'YYYY-MM-DD'), tel_cl = :tel_cl "
                  "WHERE id_Clients = :id_Clients");
    query.bindValue(":id_Clients", id_Clients);
    query.bindValue(":nom_cl", nom_cl);
    query.bindValue(":prenom_cl", prenom_cl);
    query.bindValue(":adresse_cl", adresse_cl);
    query.bindValue(":email_cl", email_cl);
    query.bindValue(":date_naissance_cl", date_naissance_cl);
    query.bindValue(":tel_cl", tel_cl);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la modification:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* client::chercherClient(const QString& critere) {
    QSqlQueryModel* model = new QSqlQueryModel();

    // Convertir le critère en minuscules
    QString lowerCritere = critere.toLower();

    QString queryString = "SELECT id_Clients, nom_cl, prenom_cl, adresse_cl, email_cl, tel_cl, date_naissance_cl "
                          "FROM CLIENTS";

    if (!lowerCritere.isEmpty()) {
        queryString += " WHERE LOWER(id_Clients) LIKE :critere OR "
                       "LOWER(nom_cl) LIKE :critere OR "
                       "LOWER(prenom_cl) LIKE :critere";
    }

    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":critere", "%" + lowerCritere + "%");  // Bind du critère converti en minuscules

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête de recherche :" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);

    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de la mise à jour du modèle de vue :" << model->lastError().text();
        delete model;
        return nullptr;
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date de naissance"));

    return model;
}

QSqlQueryModel* client::trierClients(const QString& colonne) {
    // Construire la requête SQL
    QString queryString = "SELECT id_Clients, nom_cl, prenom_cl, adresse_cl, email_cl, tel_cl, date_naissance_cl FROM CLIENTS";

    if (colonne == "Date De Naissance") {
        queryString += " ORDER BY date_naissance_cl ASC";
    } else if (colonne == "Nom") {
        queryString += " ORDER BY nom_cl ASC";
    } else if (colonne == "Prénom") {
        queryString += " ORDER BY prenom_cl ASC";
    }

    // Créer un modèle pour exécuter la requête
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(queryString);

    // Vérifier les erreurs après exécution
    if (model->lastError().isValid()) {
        qDebug() << "Erreur dans la requête SQL :" << model->lastError().text();
        delete model;
        return nullptr;
    }

    // Configurer les en-têtes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date de naissance"));

    return model;
}

// Méthode pour appeler un client
bool client::appelerClient(int tel_cl) {
    QString phoneNumber = QString("tel:%1").arg(tel_cl);
    if (QDesktopServices::openUrl(QUrl(phoneNumber))) {
        qDebug() << "Appel initié avec succès.";
        return true;
    } else {
        qDebug() << "Échec de l'initiation de l'appel.";
        return false;
    }
}

// Méthode pour envoyer un SMS
bool client::envoyerSMS(int tel_cl, const QString& message) {
    QString smsLink = QString("sms:%1?body=%2").arg(tel_cl).arg(message);
    if (QDesktopServices::openUrl(QUrl(smsLink))) {
        qDebug() << "SMS envoyé avec succès.";
        return true;
    } else {
        qDebug() << "Échec de l'envoi du SMS.";
        return false;
    }
}
