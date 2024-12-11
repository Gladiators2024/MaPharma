#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{ db=QSqlDatabase ::addDatabase("QODBC");
bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("STOCK");//inserer le nom de la source de données
db.setUserName("jaser");//inserer nom de l'utilisateur
db.setPassword("jaser22");//inserer mot de passe de cet utilisateur

if (db.open())test=true;
return test;}

