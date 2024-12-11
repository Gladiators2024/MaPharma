#ifndef MEDICAMENT_H
#define MEDICAMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <string>
#include <iostream>
#include <QList>
using namespace std;

class Medicament
{
private:
    int id_medicament;
    QString nom_med;
    int dosage_med;
    QString date_expiration_med;
    int quantite_med;
    double prix_med;

public:
    Medicament();


    Medicament(int id_medicament, QString nom_med, int dosage_med, QString date_expiration_med, int quantite_med, double prix_med);

    int getIdMedicament(){ return id_medicament; }
    QString getNomMed(){ return nom_med; }
    int getDosageMed(){ return dosage_med; }
    QString getDateExpirationMed() { return date_expiration_med; }
    int getQuantiteMed() { return quantite_med; }
    double getPrixMed() { return prix_med; }

    void setIdMedicament(int id_medicament){ this->id_medicament = id_medicament; }
    void setNomMed(QString nom_med){ this->nom_med = nom_med; }
    void setDosageMed(int dosage_med){ this->dosage_med = dosage_med; }
    void setDateExpirationMed(QString date_expiration_med){ this->date_expiration_med = date_expiration_med; }
    void setQuantiteMed(int quantite_med){ this->quantite_med = quantite_med; }
    void setPrixMed(double prix_med){ this->prix_med = prix_med; }

    bool ajouter_med();
    bool supprimer_med(int);
    QSqlQueryModel * afficher();
    bool modifier_med(int , QString ,int ,QString, int, double );
     QSqlQueryModel* chercher_med(int id);
        QSqlQueryModel* trier_par_id();
        QSqlQueryModel* trier_par_quantite();
        QList<int> verifier_quantites();
};

#endif // MEDICAMENT_H
