#ifndef GENERATEURPDF_H
#define GENERATEURPDF_H
#include <QPdfWriter>
#include <QPainter>
#include <QSqlQueryModel>

class GenerateurPDF {
public:
    GenerateurPDF();
    static void genererPDF(QSqlQueryModel* model, const QString& nomFichierPDF);
};

#endif // GENERATEURPDF_H
