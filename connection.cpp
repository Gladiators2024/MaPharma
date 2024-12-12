#include "connection.h"
connection::connection(){}
bool connection::createconnection()
{
  db=QSqlDatabase::addDatabase("QODBC") ;
  bool test=false;
  db.setDatabaseName("Mapharma");
  db.setUserName("mayssa");
  db.setPassword("mayssa24");
  if(db.open()) test=true;//Comme db est de type QSqlDatabase, il hérite automatiquement de toutes les méthodes publiques de QSqlDatabase, y compris open().
  return test;
}

void connection ::closeConnection()
{db.close();}//Qt ferme la connexion active à la base de données associée.
