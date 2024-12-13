#include "medicament.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>
#include <string>
#include <iostream>
#include <QDebug>
#include <QSqlError>
#include <QRegularExpression>
#include <QList>

using namespace std;

Medicament::Medicament() {
    id_medicament = 0;
    nom_med = " ";
    dosage_med = 0;
    date_expiration_med = " " ;
    quantite_med = 0;
    prix_med = 0;
}

Medicament::Medicament(int id_medicament, QString nom_med, int dosage_med, QString date_expiration_med, int quantite_med, double prix_med) {
    this->id_medicament = id_medicament;
    this->nom_med = nom_med;
    this->dosage_med = dosage_med;
    this->date_expiration_med = date_expiration_med;
    this->quantite_med = quantite_med;
    this->prix_med = prix_med;
}

bool Medicament::ajouter_med() {
    QSqlQuery query;

    query.prepare("INSERT INTO medicament (id_medicament, nom_med, dosage_med, date_expiration_med, quantite_med, prix_med) "
                  "VALUES (:id_medicament, :nom_med, :dosage_med, :date_expiration_med, :quantite_med, :prix_med)");
    query.bindValue(":id_medicament", id_medicament);
    query.bindValue(":nom_med", nom_med);
    query.bindValue(":dosage_med", dosage_med);
    query.bindValue(":date_expiration_med", date_expiration_med);
    query.bindValue(":quantite_med", quantite_med);
    query.bindValue(":prix_med", prix_med);

    qDebug() << "Préparation de la requête d'insertion : "
             << query.executedQuery();

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout du médicament : "
                 << query.lastError().text();
        return false;
    }
    return true;
}

bool Medicament::supprimer_med(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM medicament WHERE id_medicament = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression du médicament : "
                 << query.lastError().text();
        return false;
    }
    return true;
}
QSqlQueryModel* Medicament::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM medicament");
    return model;
}
bool Medicament::modifier_med(int id_medicament, QString nom_med,  int dosage_med,
                         QString date_expiration_med, int quantite_med, double prix_med) {
    QSqlQuery query;

    query.prepare("UPDATE medicament SET nom_med = :nom_med, dosage_med = :dosage_med, "
                  "date_expiration_med = :date_expiration_med, quantite_med = :quantite_med, "
                  "prix_med = :prix_med WHERE id_medicament = :id_medicament");

    // Liaison des valeurs aux paramètres
    query.bindValue(":id_medicament", id_medicament);
    query.bindValue(":nom_med", nom_med);
    query.bindValue(":dosage_med", dosage_med);
    query.bindValue(":date_expiration_med", date_expiration_med);
    query.bindValue(":quantite_med", quantite_med);
    query.bindValue(":prix_med", prix_med);
    if (!query.exec()) {
        qDebug() << "Erreur lors de la modification:" << query.lastError().text();
        return false;
    }
    return true;
}
QSqlQueryModel* Medicament::chercher_med(int id_medicament) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM medicament WHERE id_medicament = :id");
    query.bindValue(":id", id_medicament);

    if (!query.exec()) {
        qDebug() << "Erreur dans la requête SQL:" << query.lastError().text();
    }

    model->setQuery(query); /*aloras*/
    return model;
}
QSqlQueryModel* Medicament::trier_par_id() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM medicament ORDER BY id_medicament ASC");
    return model;
}
QSqlQueryModel* Medicament::trier_par_quantite() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM medicament ORDER BY quantite_med ASC");
    return model;
}
QList<int> Medicament::verifier_quantites() {
    QSqlQuery query;
    QList<int> ids_alerte;

    query.prepare("SELECT id_medicament FROM medicament WHERE quantite_med < 10");
    if (query.exec()) {
        while (query.next()) {
            ids_alerte.append(query.value(0).toInt());
        }
    } else {
        qDebug() << "Erreur lors de la vérification des quantités :" << query.lastError().text();
    }

    return ids_alerte;
}

