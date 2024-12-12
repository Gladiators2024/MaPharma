#include "transaction.h"//"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
Transactions::Transactions() {}

Transactions::Transactions(QString compte_ass, QString type_tr, QDate date_tr,
                           QString categorie_tr, double montant_tr, QString mode_paiement,
                           QString description, QString id_emp)
    : compte_ass(compte_ass), type_tr(type_tr), date_tr(date_tr),
      categorie_tr(categorie_tr), montant_tr(montant_tr),
      mode_paiement(mode_paiement), description(description), id_emp(id_emp) {}

int Transactions::ajouter() {
    QSqlQuery query;

    // Exécuter l'insertion
    query.prepare("INSERT INTO TRANSACTIONS (COMPTE_ASS, TYPE_TR, DATE_TR, CATEGORIE_TR, "
                  "MONTANT_TR, MODE_PAIEMENT, DESCRIPTION, ID_EMP) "
                  "VALUES (:COMPTE_ASS, :TYPE_TR, :DATE_TR, :CATEGORIE_TR, :MONTANT_TR, "
                  ":MODE_PAIEMENT, :DESCRIPTION, :ID_EMP)");

    query.bindValue(":COMPTE_ASS", compte_ass);
    query.bindValue(":TYPE_TR", type_tr);
    query.bindValue(":DATE_TR", date_tr);
    query.bindValue(":CATEGORIE_TR", categorie_tr);
    query.bindValue(":MONTANT_TR", montant_tr);
    query.bindValue(":MODE_PAIEMENT", mode_paiement);
    query.bindValue(":DESCRIPTION", description);
    query.bindValue(":ID_EMP", id_emp);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête d'insertion : " << query.lastError();
        return -1; // Retourne -1 en cas d'erreur
    }

    // Récupérer l'ID généré
    if (query.exec("SELECT ID_TR FROM TRANSACTIONS ORDER BY ID_TR DESC")) {
        if (query.next()) {
            int id = query.value(0).toInt();
            qDebug() << "ID ajouté : " << id;
            return id;
        }
    } else {
        qDebug() << "Erreur lors de la récupération de l'ID : " << query.lastError();
    }

    return -1; // Retourne -1 si la récupération échoue
}



bool Transactions::modifier(int id_tr) {
    QSqlQuery query;
    query.prepare("UPDATE TRANSACTIONS SET COMPTE_ASS = :COMPTE_ASS, TYPE_TR = :TYPE_TR, "
                  "DATE_TR = :DATE_TR, CATEGORIE_TR = :CATEGORIE_TR, MONTANT_TR = :MONTANT_TR, "
                  "MODE_PAIEMENT = :MODE_PAIEMENT, DESCRIPTION = :DESCRIPTION, ID_EMP = :ID_EMP "
                  "WHERE ID_TR = :ID_TR");
    query.bindValue(":ID_TR", id_tr);
    query.bindValue(":COMPTE_ASS", compte_ass);
    query.bindValue(":TYPE_TR", type_tr);
    query.bindValue(":DATE_TR", date_tr);
    query.bindValue(":CATEGORIE_TR", categorie_tr);
    query.bindValue(":MONTANT_TR", montant_tr);
    query.bindValue(":MODE_PAIEMENT", mode_paiement);
    query.bindValue(":DESCRIPTION", description);
    query.bindValue(":ID_EMP", id_emp);
    return query.exec();
}

bool Transactions::supprimer(int id_tr) {
    QSqlQuery query;
    query.prepare("DELETE FROM TRANSACTIONS WHERE ID_TR = :ID_TR");
    query.bindValue(":ID_TR", id_tr);
    return query.exec();
}

QSqlQueryModel* Transactions::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM TRANSACTIONS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_TR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Compte Associé"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type Transaction"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Transaction"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Catégorie Transaction"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Montant Transaction"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Mode Paiement"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Description"));
   // model->setHeaderData(8, Qt::Horizontal, QObject::tr("ID Employé"));
    return model;
}

void Transactions::rechercherParId(int id_tr) {
    QSqlQuery query;
    query.prepare("SELECT * FROM TRANSACTIONS WHERE ID_TR = :ID_TR");
    query.bindValue(":ID_TR", id_tr);

    if (query.exec() && query.next()) {
        this->id_r=query.value("ID_TR").toInt();
        this->compte_ass = query.value("COMPTE_ASS").toString();
        this->type_tr = query.value("TYPE_TR").toString();
        this->date_tr = query.value("DATE_TR").toDate();
        this->categorie_tr = query.value("CATEGORIE_TR").toString();
        this->montant_tr = query.value("MONTANT_TR").toDouble();
        this->mode_paiement = query.value("MODE_PAIEMENT").toString();
        this->description = query.value("DESCRIPTION").toString();
        this->id_emp = query.value("ID_EMP").toString();
    }
   }
QSqlQueryModel* Transactions::rechercher(const QString& critere, const QString& valeur, const QDate& valeur1) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    if (critere == "Date") {
        query.prepare("SELECT * FROM TRANSACTIONS WHERE DATE_TR LIKE :valeur");
        query.bindValue(":valeur",  valeur1 );
    } else if (critere == "Categorie") {
        query.prepare("SELECT * FROM TRANSACTIONS WHERE CATEGORIE_TR LIKE :valeur");
        query.bindValue(":valeur", "%" + valeur + "%");
    }
    if (!query.exec()) {
        qDebug() << "Erreur lors de la recherche :" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Transaction"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Compte Associé"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Transaction"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Catégorie"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Mode Paiement"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Description"));
   // model->setHeaderData(8, Qt::Horizontal, QObject::tr("ID Employé"));

    return model;
}
QSqlQueryModel* Transactions::trier(const QString& condition, bool ascendant) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString order = ascendant ? "ASC" : "DESC";

    if (condition == "Montant") {
        model->setQuery("SELECT * FROM TRANSACTIONS ORDER BY MONTANT_TR " + order);
    } else if (condition == "Date") {
        model->setQuery("SELECT * FROM TRANSACTIONS ORDER BY DATE_TR " + order);
    } else if (condition == "Compte associe") {
        model->setQuery("SELECT * FROM TRANSACTIONS ORDER BY COMPTE_ASS " + order);}

    // Définition des en-têtes des colonnes pour le modèle
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Transaction"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Compte Associé"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Transaction"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Catégorie"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Mode Paiement"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ID Employé"));

    return model;
}

QMap<QString, int> Transactions::statistiquesParTypeEtCategorie() {
    QMap<QString, int> stats;
    QSqlQuery query("SELECT TYPE_TR, CATEGORIE_TR, COUNT(*) FROM TRANSACTIONS GROUP BY TYPE_TR, CATEGORIE_TR");

    while (query.next()) {
        QString key = query.value(0).toString() + " - " + query.value(1).toString();
        qDebug ()<< "stats",key ;
        int count = query.value(2).toInt();
        stats[key] = count;
    }

    return stats;
}

bool Transactions::connexion(int id, QString motDePasse) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE ID_EMP = :id AND PASSWORD = :mdp");
    query.bindValue(":id", id);
    query.bindValue(":mdp", motDePasse);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la connexion :" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }
}
bool Transactions::crehistorique(int id_trans,QString type){
    QSqlQuery query;
    query.prepare("INSERT INTO HISTORIQUE (ID_TRANS, TYPE, TIME_TRANS) "
                  "VALUES (:id_trans, :type, CURRENT_TIMESTAMP)");
    query.bindValue(":id_trans", id_trans);
    query.bindValue(":type", type);


    if (!query.exec()) {
        qDebug() << "Erreur lors de l'envoi du message:" << query.lastError().text();
        return false;
    }
    return true;

}
QSqlQueryModel* Transactions::gethistorique(){
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM HISTORIQUE ORDER BY TIME_TRANS DESC ");
    return model;
}
