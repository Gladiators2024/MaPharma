#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("SmartPharmacy");//inserer le nom de la source de données
db.setUserName("azer");//inserer nom de l'utilisateur
db.setPassword("azer");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}

void Connection::closeConnection(){db.close();}
