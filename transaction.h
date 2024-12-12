#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Transactions
{
private:
    int id_r;
    QString compte_ass, type_tr, categorie_tr, mode_paiement, description, id_emp;
    double montant_tr;
    QDate date_tr;

public:
    Transactions();  // Constructeur par défaut
    Transactions(QString compte_ass, QString type_tr, QDate date_tr, QString categorie_tr,
                 double montant_tr, QString mode_paiement, QString description, QString id_emp);

    // Accesseurs (Getters)
    QString getCompteAss() const { return compte_ass; }
    QString getTypeTr() const { return type_tr; }
    QDate getDateTr() const { return date_tr; }
    QString getCategorieTr() const { return categorie_tr; }
    double getMontantTr() const { return montant_tr; }
    QString getModePaiement() const { return mode_paiement; }
    QString getDescription() const { return description; }
    QString getIdEmp() const { return id_emp; }
    int getId_r() const{return id_r;}

    // Mutateurs (Setters)
    void setCompteAss(const QString& c) { compte_ass = c; }
    void setTypeTr(const QString& t) { type_tr = t; }
    void setDateTr(const QDate& d) { date_tr = d; }
    void setCategorieTr(const QString& cat) { categorie_tr = cat; }
    void setMontantTr(double m) { montant_tr = m; }
    void setModePaiement(const QString& mode) { mode_paiement = mode; }
    void setDescription(const QString& desc) { description = desc; }
    void setIdEmp(const QString& emp) { id_emp = emp; }

    int ajouter();
    bool supprimer(int id_tr);
    bool modifier(int id_tr);
    QSqlQueryModel* afficher();
    void rechercherParId(int id_tr);
    QSqlQueryModel* rechercher(const QString& critere, const QString& valeur,  const QDate& valeur1);
    QSqlQueryModel* trier(const QString& condition, bool ascendant);
    QMap<QString, int> statistiquesParTypeEtCategorie();
    bool connexion(int id, QString motDePasse);
    bool crehistorique(int id_trans,QString type);
    QSqlQueryModel* gethistorique();
};

#endif // TRANSACTIONS_H
