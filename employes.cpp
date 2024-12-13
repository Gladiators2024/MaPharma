#include "employes.h"
#include<QSqlQuery>
#include <QSqlTableModel>
#include<QRegularExpression>
#include "SmtpMime"
#include <QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>

employes::employes()
{
    /*id_e=0;
    nom_e="";
    prenom_e="";
    date_embauche_e=QDate();
    postes_e="";
    salaire_e=0;
    date_naissance_e=QDate();*/
}
employes::employes(int id_e,QString nom_e,QString prenom_e,QDate date_embauche_e,QDate date_naissance_e,QString postes_e,int salaire_e)//constructeur parametré
{
    this->id_e=id_e;
    this->nom_e=nom_e;
    this->prenom_e=prenom_e;
    this->date_embauche_e=date_embauche_e;
    this->postes_e=postes_e;
    this->salaire_e=salaire_e;
    this->date_naissance_e=date_naissance_e;
}

bool employes::ajouter() {
    QRegularExpression regex("^[A-Za-z ]+$");

    // Validate the 'nom_e' and 'prenom_e' fields
    if (!regex.match(nom_e).hasMatch() || !regex.match(prenom_e).hasMatch() || !regex.match(postes_e).hasMatch()) {
        qDebug() << "Invalid input: Name and surname should only contain letters.";
        return false; // Invalid input, so return false or handle it as needed
    }
    QSqlQuery query;
    query.prepare("INSERT INTO EYA.EMPLOYES (ID_EMPLOYES, NOM_EMP, PRENOM_EMP, DATE_EMBAUCHE_EMP, POSTE_EMP, SALAIRE_EMP, DATE_NAISS_EMP) "
                  "VALUES (:id, :nom, :prenom, :date_embauche, :postes, :salaire, :date_naissance)");
    query.bindValue(":id", id_e);
    query.bindValue(":nom", nom_e);
    query.bindValue(":prenom", prenom_e);
    query.bindValue(":date_embauche", date_embauche_e);
    query.bindValue(":postes", postes_e);
    query.bindValue(":salaire", salaire_e);
    query.bindValue(":date_naissance", date_naissance_e);
    return query.exec();
}

QSqlQueryModel* employes::afficher_all_emp() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EYA.EMPLOYES ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));

    return model;
}


bool employes::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EYA.EMPLOYES WHERE ID_EMPLOYES = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
            qDebug() << "Delete failed:" << query.lastError().text();
            return false;
        }
        return true;
    //return query.exec();

}

bool employes::modifier(int id)
{
   QRegularExpression regex("^[A-Za-z ]+$");


   /* if ( || !regex.match(prenom_e).hasMatch() || !regex.match(postes_e).hasMatch()) {
        qDebug() << "Invalid input: Name and surname should only contain letters.";
        return false;
    }*/
     QSqlQuery query;

        QString querystring="UPDATE EYA.EMPLOYES SET ";
        bool firstfield=true;
        if(!nom_e.isEmpty() )
        {
            if(regex.match(nom_e).hasMatch()){
            if(!firstfield)
            {
                querystring+=",";//deja une valeur ajoutée
            }
           querystring+="NOM_EMP = :nom";//first value to add
            }
           firstfield = false;
        }

        if(!prenom_e.isEmpty())
        {
            if(regex.match(prenom_e).hasMatch()){
            if(!firstfield)
            {
                querystring+=",";//deja une valeur ajoutée
            }
           querystring+="PRENOM_EMP = :prenom";//first value to add
            }
           firstfield = false;
        }

        if(date_naissance_e.isValid())
        {
            if(!firstfield)
            {
                querystring+=",";//deja une valeur ajoutée
            }
           querystring+="DATE_NAISS_EMP = :date_naissance";//first value to add
           firstfield = false;
        }

        if(date_embauche_e.isValid())
        {
            if(!firstfield)
            {
                querystring+=",";//deja une valeur ajoutée
            }
           querystring+="DATE_EMBAUCHE_EMP = :date_embauche";//first value to add
           firstfield = false;
        }

        if(!postes_e.isEmpty())
        {
            if(regex.match(postes_e).hasMatch()){
            if(!firstfield)
            {
                querystring+=",";//deja une valeur ajoutée
            }
           querystring+="POSTE_EMP = :poste";//first value to add
            }
           firstfield = false;
        }

        if(salaire_e!=0)
        {
            if(!firstfield)
            {
                querystring+=",";//deja une valeur ajoutée
            }
           querystring+="SALAIRE_EMP = :salaire";//first value to add
           firstfield = false;
        }
        if(firstfield)
        {
            return false;
        }

        querystring += " WHERE ID_EMPLOYES = :id";
        query.prepare(querystring);

        //bind the values that were included in the query

        if(!nom_e.isEmpty())
            query.bindValue(":nom",nom_e);

        if(!prenom_e.isEmpty())
            query.bindValue(":prenom",prenom_e);

        if(date_naissance_e.isValid())
            query.bindValue(":date_naissance",date_naissance_e);

        if(date_embauche_e.isValid())
            query.bindValue(":date_embauche",date_embauche_e);

        if(!postes_e.isEmpty())
            query.bindValue(":poste",postes_e);

        if(salaire_e!=0)
            query.bindValue(":salaire",salaire_e);

        query.bindValue(":id", id);

        return query.exec();
}

QSqlQueryModel* employes::rechercher(const QString &partialSearch, bool searchById) {

    QSqlQuery query;
    QString queryString = "SELECT * FROM EYA.EMPLOYES WHERE ";

    if (searchById) {
        queryString += "TO_CHAR(ID_EMPLOYES) LIKE :partialSearch";  // Search by ID
    } else {
        queryString += "NOM_EMP LIKE :partialSearch";  // Search by Nom
    }

    query.prepare(queryString);
    query.bindValue(":partialSearch", partialSearch + "%");  // Use partial match

    if (!query.exec()) {
        qDebug() << "Search failed, SQL error:" << query.lastError().text();
        return nullptr;
    }

    // Fill model with results
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(std::move(query));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date d'Embauche"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date de Naissance"));

    return model;

}


QSqlQueryModel* employes::trier(const QString& methode, const QString& ordre)
{
        QSqlQuery query;
        QString queryString = "SELECT * FROM EYA.EMPLOYES";

        QString orderDirection = (ordre.toUpper() == "DESC") ? "DESC" : "ASC";

        // Construire la requête en fonction de la méthode de tri
        if (methode == "nom") {
            queryString += " ORDER BY NOM_EMP " + orderDirection;
        } else if (methode == "date") {
            queryString += " ORDER BY DATE_NAISS_EMP " + orderDirection;
        }else if (methode == "salaire") {
            queryString += " ORDER BY SALAIRE_EMP " + orderDirection;
        }

        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(queryString);

        if (model->lastError().isValid()) {
            qDebug() << "Sorting query failed:" << model->lastError().text();
            delete model;
            return nullptr;
        }

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date d'Embauche"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Poste"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Salaire"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date de Naissance"));

        return model;
}

