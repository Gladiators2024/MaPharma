#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class client
{
    QString nom_cl, prenom_cl, adresse_cl, email_cl;
    int id_Clients, tel_cl, date_naissance_cl;
public:
    client();
    client(int,QString,QString,QString,QString,int,int);

    QString getNom(){return nom_cl;}
    QString getPrenom(){return prenom_cl;}
    QString getAdresse(){return adresse_cl;}
    QString getEmail(){return email_cl;}
    int getID(){return id_Clients;}
    int getTel(){return tel_cl;}
    int getDate(){return date_naissance_cl;}

    void setNom(QString n){nom_cl=n;}
    void setPrenom(QString p){prenom_cl=p;}
    void setAdresse(QString a){adresse_cl=a;}
    void setEmail(QString e){email_cl=e;}
    void setID(int id){this->id_Clients=id;}
    void setTel(int tel){this->tel_cl=tel;}
    void setDate(int date){this->date_naissance_cl=date;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int id_Clients);
    bool existe(int id_Clients);
    QSqlQueryModel* chercherClient(const QString& critere);
    QSqlQueryModel* trierClients(const QString& colonne);
    bool modifier(int id_Clients,const QString &nom_cl,const QString &prenom_cl,const QString &adresse_cl, const QString &email_cl, const QString &date_naissance_cl, int tel_cl);

    bool appelerClient(int tel_cl);
    bool envoyerSMS(int tel_cl, const QString& message);
};

#endif // CLIENT_H
