#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <string>
#include <iostream>
using namespace std;

class Fournisseur
{
private:
    int id_fournisseur;
    QString nom_fr;
    QString adresse_fr;
    int numero_fr;
    QString email_fr;
    QString produit_fr;
    QString date_livraison_fr;
    QString con_pai_fr;
    QString ev_qu_fr;

public:
    Fournisseur();



    // Constructor
    Fournisseur(int id_fournisseur,QString nom_fr,QString adresse_fr,int numero_fr,QString email_fr,QString produit_fr,QString date_livraison_fr,QString con_pai_fr,QString ev_qu_fr);

    // Getters
    int getid_fournisseur(){ return id_fournisseur; }
    QString getnom_fr(){ return nom_fr; }
    QString getadresse_fr(){ return adresse_fr; }
    int getnumero_fr(){ return numero_fr; }
    QString getemail_fr() { return email_fr; }
    QString getproduit_fr() { return produit_fr; }
    QString getdate_livraison_fr() { return date_livraison_fr; }
    QString getcon_pai_fr() { return con_pai_fr; }
    QString getev_qu_fr() { return ev_qu_fr; }

    // Setters
    void setid_fournisseur(int id_fournisseur){ this->id_fournisseur = id_fournisseur; }
    void setnom_fr(QString nom_fr){ this->nom_fr = nom_fr; }
    void setadresse_fr(QString adresse_fr){ this->adresse_fr = adresse_fr; }
    void setnumero_fr(int numero_fr){ this->numero_fr = numero_fr; }
    void setemail_fr(QString email_fr){ this->email_fr = email_fr; }
    void setproduit_fr(QString produit_fr){ this->produit_fr = produit_fr; }
    void setdate_livraison_fr(QString date_livraison_fr){ this->date_livraison_fr = date_livraison_fr; }
    void setcon_pai_fr(QString con_pai_fr){ this->con_pai_fr = con_pai_fr; }
    void setev_qu_fr(QString ev_qu_fr){ this->ev_qu_fr = ev_qu_fr; }

    bool ajouter_fr();
    bool supprimer_fr(int id_fournisseur);
    QSqlQueryModel * afficher();
    bool modifier_fr(int ,QString ,QString ,int ,QString ,QString ,QString ,QString ,QString );
    QSqlQueryModel* chercher_FOURNI(int id_fournisseur);
    QSqlQueryModel* trier_par_id();


};

#endif //FOURNISSEUR_H
