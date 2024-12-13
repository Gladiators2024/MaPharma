#include "connexion.h"
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
connexion::connexion()
{

}
bool connexion::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("SmartPharmacy");//inserer le nom de la source de données
db.setUserName("eya");//inserer nom de l'utilisateur
db.setPassword("eya");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
