#ifndef EMPLOYES_H
#define EMPLOYES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlQueryModel>
#include<QDate>


class employes
{
    int id_e;
    QString nom_e;
    QString prenom_e;
    QDate date_embauche_e;
    QDate date_naissance_e;
    QString postes_e;
    int salaire_e;
    QString uid_card;
public:
    employes();
    employes(int id_e,QString nom_e,QString prenom_e,QDate date_embauche_e,QDate date_naissance_e,QString postes_e,int salaire_e);

    int getId() const { return id_e; }
    QString getNom() const { return nom_e; }
    QString getPrenom() const { return prenom_e; }
    QDate getDateEmbauche() const { return date_embauche_e; }
    QDate getDateNaissance() const { return date_naissance_e; }
    QString getPostes() const { return postes_e; }
    int getSalaire() const { return salaire_e; }

    void setId(int id) { id_e = id; }
    void setNom(const QString &nom) { nom_e = nom; }
    void setPrenom(const QString &prenom) { prenom_e = prenom; }
    void setDateEmbauche(const QDate &date) { date_embauche_e = date; }
    void setDateNaissance(const QDate &date) { date_naissance_e = date; }
    void setPostes(const QString &poste) { postes_e = poste; }
    void setSalaire(int salaire) { salaire_e = salaire; }

    bool ajouter();
    QSqlQueryModel* afficher_all_emp(); //method to fetch all employees(retrieve or get data from the database)
    bool supprimer(int id);
    bool modifier(int id);
    QSqlQueryModel* rechercher(const QString &partialSearch, bool searchById);
    QSqlQueryModel* trier(const QString& methode, const QString& ordre);


};

#endif // EMPLOYES_H
