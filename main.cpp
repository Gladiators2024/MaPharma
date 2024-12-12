#include <QApplication>
#include <QMessageBox>
#include <QLocale>
#include <QTranslator>
#include "connection.h"
#include"dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connection c;
    bool test = c.createconnection();
    Dialog d;

    if (test) {

        QMessageBox::information(nullptr, QObject::tr("Database Connection"), QObject::tr("Connection successful.\nClick Cancel to exit."), QMessageBox::Cancel);
        d.show();
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Database Connection"), QObject::tr("Connection failed.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "transaction_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    return a.exec();
}
