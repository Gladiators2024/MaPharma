/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *compteAssocieLineEdit;
    QPushButton *ajouterButton_clicked;
    QLabel *label_15;
    QLabel *label_26;
    QLineEdit *descriptionLineEdit;
    QLabel *label_27;
    QLabel *id_lab;
    QComboBox *type_combox;
    QDoubleSpinBox *doubleSpinBox;
    QComboBox *paymentbox;
    QComboBox *categorie_box;
    QDateEdit *dateEdit_2;
    QPushButton *modifierButton_clicked;
    QPushButton *supprimerButton_clicked;
    QLabel *label_8;
    QComboBox *tri_combox;
    QTableView *tableView;
    QLabel *label_9;
    QLabel *label_28;
    QPushButton *pushButton_21;
    QComboBox *recherche_combox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QSpinBox *id_r;
    QDateEdit *date_r;
    QComboBox *type_r;
    QPushButton *pushButton_22;
    QWidget *framestat;
    QPushButton *pushButton_28;
    QWidget *widget_12;
    QLabel *label_39;
    QGraphicsView *graphicsView_6;
    QWidget *widget_13;
    QLabel *label_40;
    QDateEdit *dateEdit_17;
    QDateEdit *dateEdit_18;
    QDateEdit *dateEdit_19;
    QCheckBox *checkBox_16;
    QTimeEdit *timeEdit_16;
    QCheckBox *checkBox_17;
    QTimeEdit *timeEdit_17;
    QTimeEdit *timeEdit_18;
    QCheckBox *checkBox_18;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1440, 641);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(217, 255, 218);\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        frame2 = new QFrame(centralwidget);
        frame2->setObjectName("frame2");
        frame2->setGeometry(QRect(190, 80, 321, 471));
        frame2->setStyleSheet(QString::fromUtf8("background-color: rgb(58, 116, 82);\n"
"color: rgb(255, 255, 255);\n"
" font: 87 9pt \"Arial Black\"; \n"
"  border-radius: 10px ; /* Arrondi dans tous les coins */\n"
"  border: 0px solid rgb(151, 181, 163); /* Bordure de la QLabel en couleur RGB sp\303\251cifi\303\251e */   /*background-color: transparent;*/\n"
""));
        frame2->setFrameShape(QFrame::StyledPanel);
        frame2->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 81, 16));
        label->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI Variable Display\";"));
        label_2 = new QLabel(frame2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 140, 81, 21));
        label_2->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI Variable Display\";"));
        label_3 = new QLabel(frame2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 100, 91, 16));
        label_3->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI Variable Display\";\n"
""));
        label_4 = new QLabel(frame2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 220, 131, 16));
        label_4->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI Variable Display\";"));
        label_5 = new QLabel(frame2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 60, 111, 16));
        label_5->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI Variable Display\";"));
        label_6 = new QLabel(frame2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 260, 131, 16));
        label_6->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI Variable Display\";"));
        compteAssocieLineEdit = new QLineEdit(frame2);
        compteAssocieLineEdit->setObjectName("compteAssocieLineEdit");
        compteAssocieLineEdit->setGeometry(QRect(140, 60, 171, 20));
        compteAssocieLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color :rgb(0, 0, 0);"));
        ajouterButton_clicked = new QPushButton(frame2);
        ajouterButton_clicked->setObjectName("ajouterButton_clicked");
        ajouterButton_clicked->setGeometry(QRect(20, 380, 75, 24));
        ajouterButton_clicked->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 11pt \"Segoe UI Variable Display\";\n"
"background-color: rgb(224, 255, 230);\n"
" border-radius: 10px ; /* Arrondi dans tous les coins */\n"
"\n"
""));
        label_15 = new QLabel(frame2);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(0, 0, 251, 20));
        label_15->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 14pt \"Segoe UI Variable Display\";\n"
"background-color: rgb(174, 255, 123);"));
        label_26 = new QLabel(frame2);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(10, 180, 131, 21));
        label_26->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI Variable Display\";"));
        descriptionLineEdit = new QLineEdit(frame2);
        descriptionLineEdit->setObjectName("descriptionLineEdit");
        descriptionLineEdit->setGeometry(QRect(140, 310, 171, 20));
        descriptionLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color :rgb(0, 0, 0);\n"
"color :rgb(0, 0, 0);"));
        label_27 = new QLabel(frame2);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(10, 310, 131, 16));
        label_27->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI Variable Display\";"));
        id_lab = new QLabel(frame2);
        id_lab->setObjectName("id_lab");
        id_lab->setGeometry(QRect(140, 30, 171, 16));
        id_lab->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius: 10px ; /* Arrondi dans tous les coins */\n"
"  border: 0px solid rgb(151, 181, 163);\n"
"color :rgb(0, 0, 0);\n"
""));
        type_combox = new QComboBox(frame2);
        type_combox->addItem(QString());
        type_combox->addItem(QString());
        type_combox->setObjectName("type_combox");
        type_combox->setGeometry(QRect(140, 100, 171, 22));
        type_combox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color :rgb(0, 0, 0);"));
        doubleSpinBox = new QDoubleSpinBox(frame2);
        doubleSpinBox->setObjectName("doubleSpinBox");
        doubleSpinBox->setGeometry(QRect(140, 220, 171, 22));
        doubleSpinBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color :rgb(0, 0, 0);"));
        doubleSpinBox->setMaximum(99999.990000000005239);
        paymentbox = new QComboBox(frame2);
        paymentbox->addItem(QString());
        paymentbox->addItem(QString());
        paymentbox->addItem(QString());
        paymentbox->setObjectName("paymentbox");
        paymentbox->setGeometry(QRect(140, 260, 171, 22));
        paymentbox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color :rgb(0, 0, 0);"));
        categorie_box = new QComboBox(frame2);
        categorie_box->addItem(QString());
        categorie_box->addItem(QString());
        categorie_box->setObjectName("categorie_box");
        categorie_box->setGeometry(QRect(140, 180, 171, 22));
        categorie_box->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color :rgb(0, 0, 0);"));
        dateEdit_2 = new QDateEdit(frame2);
        dateEdit_2->setObjectName("dateEdit_2");
        dateEdit_2->setGeometry(QRect(140, 140, 171, 22));
        dateEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color :rgb(0, 0, 0);"));
        modifierButton_clicked = new QPushButton(frame2);
        modifierButton_clicked->setObjectName("modifierButton_clicked");
        modifierButton_clicked->setGeometry(QRect(130, 380, 75, 24));
        modifierButton_clicked->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 11pt \"Segoe UI Variable Display\";\n"
"background-color: rgb(224, 255, 230);\n"
" border-radius: 10px ; /* Arrondi dans tous les coins */\n"
"\n"
""));
        supprimerButton_clicked = new QPushButton(frame2);
        supprimerButton_clicked->setObjectName("supprimerButton_clicked");
        supprimerButton_clicked->setGeometry(QRect(230, 380, 75, 24));
        supprimerButton_clicked->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 11pt \"Segoe UI Variable Display\";\n"
"background-color: rgb(224, 255, 230);\n"
" border-radius: 10px ; /* Arrondi dans tous les coins */\n"
"\n"
""));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(1180, 140, 71, 20));
        label_8->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"font: 600 11pt \"Yu Gothic UI Semibold\";"));
        tri_combox = new QComboBox(centralwidget);
        tri_combox->addItem(QString());
        tri_combox->addItem(QString());
        tri_combox->addItem(QString());
        tri_combox->setObjectName("tri_combox");
        tri_combox->setGeometry(QRect(1170, 170, 81, 16));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(540, 140, 621, 411));
        tableView->setStyleSheet(QString::fromUtf8("background-color: rgb(87, 174, 129);"));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(480, -10, 351, 61));
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 600 20pt \"Yu Gothic UI Semibold\";\n"
" border-radius: 10px ; /* Arrondi dans tous les coins */\n"
"  border: 0px solid rgb(151, 181, 163); /* Bordure de la QLabel en couleur RGB sp\303\251cifi\303\251e */   /*background-color: transparent;*/\n"
"background-color: rgb(134, 180, 153);\n"
""));
        label_28 = new QLabel(centralwidget);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(540, 109, 241, 31));
        label_28->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 14pt \"Segoe UI Variable Display\";\n"
"background-color: rgb(174, 255, 123);\n"
"  border-radius: 10px ; /* Arrondi dans tous les coins */\n"
"  border: 0px solid rgb(151, 181, 163); /* Bordure de la QLabel en couleur RGB sp\303\251cifi\303\251e */   /*background-color: transparent;*/"));
        pushButton_21 = new QPushButton(centralwidget);
        pushButton_21->setObjectName("pushButton_21");
        pushButton_21->setGeometry(QRect(1150, 110, 75, 24));
        pushButton_21->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 11pt \"Segoe UI Variable Display\";\n"
"background-color: rgb(224, 255, 230);\n"
" border-radius: 10px ; /* Arrondi dans tous les coins */\n"
"\n"
"background-color: rgb(58, 116, 82);"));
        recherche_combox = new QComboBox(centralwidget);
        recherche_combox->addItem(QString());
        recherche_combox->addItem(QString());
        recherche_combox->addItem(QString());
        recherche_combox->setObjectName("recherche_combox");
        recherche_combox->setGeometry(QRect(990, 110, 141, 22));
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(1170, 220, 83, 18));
        radioButton_2 = new QRadioButton(centralwidget);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(1170, 240, 83, 18));
        id_r = new QSpinBox(centralwidget);
        id_r->setObjectName("id_r");
        id_r->setGeometry(QRect(800, 110, 181, 22));
        date_r = new QDateEdit(centralwidget);
        date_r->setObjectName("date_r");
        date_r->setGeometry(QRect(800, 110, 181, 22));
        type_r = new QComboBox(centralwidget);
        type_r->addItem(QString());
        type_r->addItem(QString());
        type_r->setObjectName("type_r");
        type_r->setGeometry(QRect(800, 110, 181, 22));
        pushButton_22 = new QPushButton(centralwidget);
        pushButton_22->setObjectName("pushButton_22");
        pushButton_22->setGeometry(QRect(990, 560, 171, 24));
        pushButton_22->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 11pt \"Segoe UI Variable Display\";\n"
"background-color: rgb(224, 255, 230);\n"
" border-radius: 10px ; /* Arrondi dans tous les coins */\n"
"\n"
"background-color: rgb(58, 116, 82);"));
        framestat = new QWidget(centralwidget);
        framestat->setObjectName("framestat");
        framestat->setGeometry(QRect(190, 80, 1201, 541));
        framestat->setStyleSheet(QString::fromUtf8("background-color: rgb(217, 255, 218);\n"
""));
        pushButton_28 = new QPushButton(framestat);
        pushButton_28->setObjectName("pushButton_28");
        pushButton_28->setGeometry(QRect(880, 30, 171, 24));
        pushButton_28->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 11pt \"Segoe UI Variable Display\";\n"
"background-color: rgb(224, 255, 230);\n"
" border-radius: 10px ; /* Arrondi dans tous les coins */\n"
"\n"
"background-color: rgb(58, 116, 82);"));
        widget_12 = new QWidget(framestat);
        widget_12->setObjectName("widget_12");
        widget_12->setGeometry(QRect(530, 60, 541, 381));
        widget_12->setStyleSheet(QString::fromUtf8("background-color: rgb(174, 255, 123);\n"
"color: rgb(255, 255, 255);\n"
" font: 87 9pt \"Arial Black\"; \n"
"  border-radius: 10px ; /* Arrondi dans tous les coins */\n"
"  border: 0px solid rgb(151, 181, 163); /* Bordure de la QLabel en couleur RGB sp\303\251cifi\303\251e */   /*background-color: transparent;*/\n"
""));
        label_39 = new QLabel(widget_12);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(0, 0, 121, 20));
        label_39->setStyleSheet(QString::fromUtf8("background-color: rgb(206, 255, 199);\n"
"background-color: rgb(95, 170, 103);"));
        graphicsView_6 = new QGraphicsView(widget_12);
        graphicsView_6->setObjectName("graphicsView_6");
        graphicsView_6->setGeometry(QRect(20, 50, 501, 301));
        widget_13 = new QWidget(framestat);
        widget_13->setObjectName("widget_13");
        widget_13->setGeometry(QRect(40, 60, 451, 381));
        widget_13->setStyleSheet(QString::fromUtf8("background-color: rgb(174, 255, 123);\n"
"color: rgb(255, 255, 255);\n"
" font: 87 9pt \"Arial Black\"; \n"
"  border-radius: 10px ; /* Arrondi dans tous les coins */\n"
"  border: 0px solid rgb(151, 181, 163); /* Bordure de la QLabel en couleur RGB sp\303\251cifi\303\251e */   /*background-color: transparent;*/\n"
""));
        label_40 = new QLabel(widget_13);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(10, 10, 121, 20));
        label_40->setStyleSheet(QString::fromUtf8("background-color: rgb(206, 255, 199);\n"
"background-color: rgb(95, 170, 103);"));
        dateEdit_17 = new QDateEdit(widget_13);
        dateEdit_17->setObjectName("dateEdit_17");
        dateEdit_17->setGeometry(QRect(10, 40, 110, 22));
        dateEdit_18 = new QDateEdit(widget_13);
        dateEdit_18->setObjectName("dateEdit_18");
        dateEdit_18->setGeometry(QRect(10, 90, 110, 22));
        dateEdit_19 = new QDateEdit(widget_13);
        dateEdit_19->setObjectName("dateEdit_19");
        dateEdit_19->setGeometry(QRect(10, 150, 110, 22));
        checkBox_16 = new QCheckBox(widget_13);
        checkBox_16->setObjectName("checkBox_16");
        checkBox_16->setGeometry(QRect(20, 70, 111, 18));
        timeEdit_16 = new QTimeEdit(widget_13);
        timeEdit_16->setObjectName("timeEdit_16");
        timeEdit_16->setGeometry(QRect(140, 70, 61, 22));
        checkBox_17 = new QCheckBox(widget_13);
        checkBox_17->setObjectName("checkBox_17");
        checkBox_17->setGeometry(QRect(20, 120, 111, 18));
        timeEdit_17 = new QTimeEdit(widget_13);
        timeEdit_17->setObjectName("timeEdit_17");
        timeEdit_17->setGeometry(QRect(140, 120, 61, 22));
        timeEdit_18 = new QTimeEdit(widget_13);
        timeEdit_18->setObjectName("timeEdit_18");
        timeEdit_18->setGeometry(QRect(140, 170, 61, 22));
        checkBox_18 = new QCheckBox(widget_13);
        checkBox_18->setObjectName("checkBox_18");
        checkBox_18->setGeometry(QRect(20, 170, 111, 18));
        MainWindow->setCentralWidget(centralwidget);
        type_r->raise();
        frame2->raise();
        label_8->raise();
        tri_combox->raise();
        tableView->raise();
        label_9->raise();
        label_28->raise();
        pushButton_21->raise();
        recherche_combox->raise();
        radioButton->raise();
        radioButton_2->raise();
        id_r->raise();
        date_r->raise();
        pushButton_22->raise();
        framestat->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1440, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Montant", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Compte associe", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Mode de paiement", nullptr));
        compteAssocieLineEdit->setText(QString());
        ajouterButton_clicked->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "        Ajouter une transaction", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "Categorie", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        id_lab->setText(QString());
        type_combox->setItemText(0, QCoreApplication::translate("MainWindow", "credit", nullptr));
        type_combox->setItemText(1, QCoreApplication::translate("MainWindow", "debit", nullptr));

        paymentbox->setItemText(0, QCoreApplication::translate("MainWindow", "versemt", nullptr));
        paymentbox->setItemText(1, QCoreApplication::translate("MainWindow", "en ligne", nullptr));
        paymentbox->setItemText(2, QCoreApplication::translate("MainWindow", "cache", nullptr));

        categorie_box->setItemText(0, QCoreApplication::translate("MainWindow", "achat", nullptr));
        categorie_box->setItemText(1, QCoreApplication::translate("MainWindow", "vente", nullptr));

        modifierButton_clicked->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        supprimerButton_clicked->setText(QCoreApplication::translate("MainWindow", "Suprimer", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Trier par :", nullptr));
        tri_combox->setItemText(0, QCoreApplication::translate("MainWindow", "Date", nullptr));
        tri_combox->setItemText(1, QCoreApplication::translate("MainWindow", "Compte associe", nullptr));
        tri_combox->setItemText(2, QCoreApplication::translate("MainWindow", "Montant", nullptr));

        label_9->setText(QCoreApplication::translate("MainWindow", "         Gestion Financiere", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "     Liste des transactions", nullptr));
        pushButton_21->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        recherche_combox->setItemText(0, QCoreApplication::translate("MainWindow", "ID", nullptr));
        recherche_combox->setItemText(1, QCoreApplication::translate("MainWindow", "Date", nullptr));
        recherche_combox->setItemText(2, QCoreApplication::translate("MainWindow", "Categorie", nullptr));

        radioButton->setText(QCoreApplication::translate("MainWindow", "Croissant", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Decroisant", nullptr));
        type_r->setItemText(0, QCoreApplication::translate("MainWindow", "achat", nullptr));
        type_r->setItemText(1, QCoreApplication::translate("MainWindow", "vente", nullptr));

        pushButton_22->setText(QCoreApplication::translate("MainWindow", "Statestique et historique", nullptr));
        pushButton_28->setText(QCoreApplication::translate("MainWindow", "Quiter", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "    Statestique", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "       Historique", nullptr));
        checkBox_16->setText(QCoreApplication::translate("MainWindow", "Transaction 1", nullptr));
        checkBox_17->setText(QCoreApplication::translate("MainWindow", "Transaction 2", nullptr));
        checkBox_18->setText(QCoreApplication::translate("MainWindow", "Transaction 3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
