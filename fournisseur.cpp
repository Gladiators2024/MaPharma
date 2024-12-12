#include "fournisseur.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>
#include <string>
#include <iostream>
#include <QDebug>
#include <QSqlError>

using namespace std;

Fournisseur::Fournisseur() {
    id_fournisseur = 0 ;
    nom_fr = " ";
    adresse_fr = " ";
    numero_fr = 0;
    email_fr = " ";
    produit_fr = " ";
    date_livraison_fr = " ";
    con_pai_fr = " ";
    ev_qu_fr = " ";
}

Fournisseur::Fournisseur(int id_fournisseur,QString nom_fr,QString adresse_fr,int numero_fr,QString email_fr,QString produit_fr,QString date_livraison_fr,QString con_pai_fr,QString ev_qu_fr) {
    this->id_fournisseur = id_fournisseur;
    this->nom_fr = nom_fr;
    this->adresse_fr = adresse_fr;
    this->numero_fr = numero_fr;
    this->email_fr = email_fr;
    this->produit_fr = produit_fr;
    this->date_livraison_fr = date_livraison_fr;
    this->con_pai_fr = con_pai_fr;
    this->ev_qu_fr = ev_qu_fr;
}

bool Fournisseur::ajouter_fr()
{
    QSqlQuery query;
    query.prepare("INSERT INTO FOURNISSEURS (id_fournisseur, nom_fr, adresse_fr, numero_fr, email_fr, produit_fr, date_livraison_fr, con_pai_fr, ev_qu_fr) "
                  "VALUES (:id_fournisseur, :nom_fr, :adresse_fr, :numero_fr, :email_fr, :produit_fr, :date_livraison_fr, :con_pai_fr, :ev_qu_fr)");
    query.bindValue(":id_fournisseur", id_fournisseur);
    query.bindValue(":nom_fr", nom_fr);
    query.bindValue(":adresse_fr", adresse_fr);
    query.bindValue(":numero_fr", numero_fr);
    query.bindValue(":email_fr", email_fr);
    query.bindValue(":produit_fr", produit_fr);
    query.bindValue(":date_livraison_fr", date_livraison_fr);
    query.bindValue(":con_pai_fr", con_pai_fr);
    query.bindValue(":ev_qu_fr", ev_qu_fr);

    return query.exec();
}


bool Fournisseur::supprimer_fr(int id_fournisseur)
{
    QSqlQuery query;
    query.prepare("DELETE FROM FOURNISSEURS WHERE id_fournisseur = :id_fournisseur");
    query.bindValue(":id_fournisseur", id_fournisseur);
    return query.exec();
}

QSqlQueryModel* Fournisseur::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FOURNISSEURS");
    return model;
}

bool Fournisseur::modifier_fr(int id_fournisseur,QString nom_fr,QString adresse_fr,int numero_fr,QString email_fr,
                              QString produit_fr,QString date_livraison_fr,QString con_pai_fr,QString ev_qu_fr)
{    QSqlQuery query;

    // Liaison des valeurs aux paramètres
     query.prepare("UPDATE  FOUNISSEURS set id_fournisseur= :id_fournisseur, nom_fr = :nom_fr, adresse_fr = :adresse_fr,"
                   "numero_f = :rnumero_fr, email_fr = :email_fr, produit_fr = :produit_fr, date_livraison_fr = :date_livraison_fr,"
                   "con_pai_fr = :con_pai_fr, ev_qu_fr = :ev_qu_fr");

     query.bindValue(":id_fournisseur", id_fournisseur);
     query.bindValue(":nom_fr", nom_fr);
     query.bindValue(":adresse_fr", adresse_fr);
     query.bindValue(":numero_fr", numero_fr);
     query.bindValue(":email_fr", email_fr);
     query.bindValue(":produit_fr", produit_fr);
     query.bindValue(":date_livraison_fr", date_livraison_fr);
     query.bindValue(":con_pai_fr", con_pai_fr);
     query.bindValue(":ev_qu_fr", ev_qu_fr);

    // Exécution de la requête
    if (!query.exec()) {
        // Affichage de l'erreur pour le débogage
        qDebug() << "Erreur lors de la modification:" << query.lastError().text();
        return false;
    }
    return true;
}
QSqlQueryModel* Fournisseur::chercher_FOURNI(int id_fournisseur) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM FOURNISSEURS WHERE id_fournisseur = :id_fournisseur");
    query.bindValue(":id_fournisseur", id_fournisseur);

    if (!query.exec()) {
        qDebug() << "Erreur dans la requête SQL:" << query.lastError().text();
    }

    model->setQuery(query);
    return model;
}
QSqlQueryModel* Fournisseur::trier_par_id() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FOURNISSEURS ORDER BY id_fournisseur ASC");
    return model;
}


