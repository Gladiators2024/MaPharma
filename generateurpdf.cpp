#include "generateurpdf.h"
#include <QMessageBox>
void GenerateurPDF::genererPDF(QSqlQueryModel* model, const QString& nomFichierPDF) {
    QPdfWriter writer(nomFichierPDF);
    QPainter painter(&writer);


    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);


    int rowCount = model->rowCount();
    int columnCount = model->columnCount();
    int cellWidth = 998;
    int cellHeight = 400;
    int margin = 10;


    for (int i = 0; i < columnCount; ++i) {

        painter.drawRect(margin + i * cellWidth, margin, cellWidth, cellHeight);

        painter.drawText(margin + i * cellWidth, margin, cellWidth, cellHeight, Qt::AlignCenter, model->headerData(i, Qt::Horizontal).toString().toUtf8());
    }


    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < columnCount; ++col) {

            painter.drawRect(margin + col * cellWidth, margin + (row + 1) * cellHeight, cellWidth, cellHeight);

            painter.drawText(margin + col * cellWidth, margin + (row + 1) * cellHeight, cellWidth, cellHeight, Qt::AlignCenter, model->data(model->index(row, col)).toString().toUtf8());
        }
    }


    painter.drawRect(margin, margin + (rowCount + 1) * cellHeight, columnCount * cellWidth, cellHeight);
    painter.drawText(margin, margin + (rowCount + 1) * cellHeight, columnCount * cellWidth, cellHeight, Qt::AlignCenter, "Fin du document");

    QMessageBox::information(nullptr, "PDF créé", "Le fichier PDF a été créé avec succès !");
}
