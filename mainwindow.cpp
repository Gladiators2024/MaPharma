#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employes.h"

#include <QMessageBox>
#include <QDebug>
#include <QSqlTableModel>
#include <QAbstractItemModel>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>

#include <QtCharts>
#include <QChartView>

#include <SmtpMime>
#include <smtpclient.h>
#include <mimemessage.h>
#include <mimetext.h>

#include <QVBoxLayout>
#include <QPixmap>
#include <QImage>
#include<QProcess>
#include<QStringList>

#include <QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
#include "arduino.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setTabText(0,"EMPLOYES");
    ui->tabWidget->setTabText(1,"CLIENTS");
    ui->tabWidget_2->setTabText(0,"Gestion Employes");
    ui->tabWidget_2->setTabText(1,"Mail");
    ui->tabWidget_2->setTabText(2,"Reconnaissance Facial");
    ui->tablevView->setModel(e.afficher_all_emp());
    ui->lineEdit->setPlaceholderText("rehercher..");
    ui->email_to->setPlaceholderText("To");
    ui->email_to_comboBox->setPlaceholderText("Start typing an email..");
    ui->subject->setPlaceholderText("Entrez un objet");
    ui->email_body->setPlaceholderText("Tapez votre message..");

    connect(ui->stats, &QPushButton::clicked, this, &MainWindow::on_stats_clicked);
    // Connect the send button to the email sending function
    connect(ui->send, &QPushButton::clicked, this, &MainWindow::on_send_clicked);

    connect(ui->email_to_comboBox, &QComboBox::currentTextChanged, this, [&](const QString &text) {
        ui->email_to->setText(text);  // Update the QLineEdit with the selected email in the combobox
    });

    emailList = {
        "qmayra1234@gmail.com",
        "MohamedMehdi.Zouagha@esprit.tn",
        "saoussen.lakhdhar@esprit.tn",
        "jasser.Missaoui@esprit.tn"
    };

    int ret=A.connect_arduino();
    switch(ret){
    case(0):qDebug()<<"arduino is available and connected to:"<<A.getarduino_port_name();
        break;
    case(1):qDebug()<<"arduino is available but not connected to:"<<A.getarduino_port_name();
        break;
    case(-1):qDebug()<<"arduino is not available:";
        break;
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));


}

void MainWindow::on_ajouter_clicked()
{
        int id_e=ui->id->text().toInt();
        QString nom_e=ui->nom->text();
        QString prenom_e=ui->id_2->text();
        QDate date_naissance_e = ui->date_naiss->date();
        QDate date_embauche_e = ui->date_embau->date();
        QString postes_e = ui->postes->text();
        int salaire_e=ui->salaire->text().toInt();
        qDebug() << "nom:" <<nom_e;
        qDebug() << "prenom:" << prenom_e;

        qDebug() << "id:" << id_e;
        qDebug() << "Date_D:" << date_naissance_e << "isValid:" << date_naissance_e.isValid();
        qDebug() << "Date_e:" << date_embauche_e << "isValid:" << date_embauche_e.isValid();
        qDebug() << "poste:" << postes_e;
        qDebug() << "salaire:" << salaire_e;

    if (nom_e.isEmpty() || prenom_e.isEmpty() ||!date_naissance_e.isValid() || !date_embauche_e.isValid() || postes_e.isEmpty() ) {
         QMessageBox::warning(this, "Error", "All fields must be filled correctly.");
         return;
     }

       employes e(id_e, nom_e, prenom_e, date_embauche_e, date_naissance_e, postes_e, salaire_e);
       if (e.ajouter()) {
           ui->tablevView->setModel(e.afficher_all_emp());//affichage d'employes
           QMessageBox::information(this, "Success", "Equipment added successfully.");
       } else {
           QMessageBox::warning(this, "Error", "Failed to add equipment.");
       }
   }

void MainWindow::on_supprimer_clicked()
{
    int id = ui->id->text().toInt();  // Convert input to int because in qt it is returned as a QString, regardless of what the content actually looks like.
    bool test = e.supprimer(id);
        if (test) {
            QMessageBox::information(this, "Success", "Employee deleted successfully.");
            ui->tablevView->setModel(e.afficher_all_emp());  // Refresh the display after deletion
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete employee.");
        }
}

void MainWindow::on_modifier_clicked()
{

    int id_e=ui->id->text().toInt();
    QString nom_e=ui->nom->text();
    QString prenom_e=ui->id_2->text();
    QDate date_naissance_e = ui->date_naiss->date();
    QDate date_embauche_e = ui->date_embau->date();
    QString postes_e = ui->postes->text();
    int salaire_e=ui->salaire->text().toInt();

    employes e(id_e, nom_e, prenom_e, date_embauche_e, date_naissance_e, postes_e, salaire_e);
    if (e.modifier(id_e)) {
        QMessageBox::information(this, "Success", "Employee modified successfully.");
        ui->tablevView->setModel(e.afficher_all_emp());  // Refresh display after modification
    } else {
        QMessageBox::warning(this, "Error", "Failed to modify employee.");
    }
}

void MainWindow::on_lineEdit_textChanged()
{
    QString partialSearch = ui->lineEdit->text();

    bool searchById = false;

    // Check if the input is a number (search by ID)
    if (partialSearch.toInt() != 0 || partialSearch == "0") {
        searchById = true;
    }

    QSqlQueryModel* model = e.rechercher(partialSearch, searchById);

    if (model) {
        ui->tablevView->setModel(model);
    } else {
        QMessageBox::warning(this, "Error", "Search failed.");
    }

}

void MainWindow::on_comboBox_currentIndexChanged()
{
    QString selectedText = ui->comboBox->currentText();

    QString methode;
    QString ordre;

    if (selectedText.contains("Nom")) {
        methode = "nom";
    } else if (selectedText.contains("Date")) {
        methode = "date";
    }else if (selectedText.contains("Salaire")) {
        methode = "salaire";
    }

    if (selectedText.contains("Ascendant")) {
        ordre = "ASC";
    } else if (selectedText.contains("Descendant")) {
        ordre = "DESC";
    }

    // Call the trier function with the parsed method and order
    QSqlQueryModel *sortedModel = e.trier(methode, ordre);

    // Check if the model was successfully returned
    if (sortedModel) {
        ui->tablevView->setModel(sortedModel);  // Display the sorted model
    } else {
        qDebug() << "Failed to sort.";
    }
}

void MainWindow::exportTableViewToPDF(QTableView *tablevView) {

    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save as PDF", "", "PDF Files (*.pdf);;All Files (*)");
    if (fileName.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageOrientation(QPageLayout::Portrait);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    painter.drawText(800, 10, "Liste d'Employes");

    QAbstractItemModel *model = tablevView->model();

    int x = 10;   // Starting x position
    int y = 100;   // Starting y position
    int rowHeight = 100;
    int columnWidth = 250;

    // Set up font for the PDF
    QFont font = painter.font();
    font.setPointSize(5);
    painter.setFont(font);

    // Draw column headers with a background color
    painter.setBrush(QColor(220, 198, 250)); // Set header background color
    for (int column = 0; column < model->columnCount(); ++column) {
        QRect rect(x + column * columnWidth, y, columnWidth, rowHeight);
        painter.drawRect(rect); // Draw rectangle with background color
        painter.drawText(rect, Qt::AlignCenter, model->headerData(column, Qt::Horizontal).toString());
    }

    // Draw rows with alternating colors (optional)
    for (int row = 0; row < model->rowCount(); ++row) {
        QColor rowColor = (row % 2 == 0) ? QColor(240, 240, 240) : QColor(255, 255, 255); // Alternating colors
        for (int column = 0; column < model->columnCount(); ++column) {
            QRect rect(x + column * columnWidth, y + (row + 1) * rowHeight, columnWidth, rowHeight);

            painter.setBrush(rowColor); // Set row background color
            painter.drawRect(rect);     // Draw the rectangle with the color
            painter.setBrush(Qt::NoBrush); // Reset brush for drawing text

            painter.drawText(rect, Qt::AlignCenter, model->data(model->index(row, column)).toString());
        }
    }

    painter.end();
    QMessageBox::information(nullptr, "Export Complete", "Data has been exported to PDF successfully.");
}

void MainWindow::on_exporter_clicked()
{
    exportTableViewToPDF(ui->tablevView);
}

void MainWindow::on_stats_clicked()
{
    QAbstractItemModel *model = ui->tablevView->model();
    if (!model) {
        QMessageBox::warning(this, "Error", "No data available.");
        return;
    }

    int rowCount = model->rowCount();
    if (rowCount == 0) {
        QMessageBox::warning(this, "Error", "No employee data to display.");
        return;
    }

    //Collect data for salaries
    QList<QPair<QString, double>> salaryData;
    for (int row = 0; row < rowCount; ++row) {
        QString name = model->data(model->index(row, 1)).toString(); // Name column
        double salary = model->data(model->index(row, 5)).toDouble(); // Salary column
        salaryData.append(qMakePair(name, salary));
    }

    //Sort the list by salary in descending order
    std::sort(salaryData.begin(), salaryData.end(), [](const QPair<QString, double> &a, const QPair<QString, double> &b) {
        return a.second > b.second;
    });

    //Create a pie chart for top 5 highest salary employees
    QPieSeries *series = new QPieSeries();

    // Add top 5 employees to the pie chart
    int topCount = qMin(5, rowCount);
    for (int i = 0; i < topCount; ++i) {
        // Add name and salary to pie chart
        series->append(salaryData[i].first, salaryData[i].second);
    }

    //Create the chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Top 5 Highest Paid Employees");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Step 7: Check if the chart already exists in the tab and remove it if so
    for (int i = 0; i < ui->tabWidget_2->count(); ++i) {
        if (ui->tabWidget_2->tabText(i) == "Statistiques") {
            ui->tabWidget_2->removeTab(i);
            break;
        }
    }

    // Step 8: Add the chart view to a new tab and display it
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);
    layout->addWidget(chartView);
    tab->setLayout(layout);

    // Set a fixed size for the tab widget
    tab->setMinimumSize(500, 400); // You can adjust this as needed

    // Add the new tab to the tab widget
    ui->tabWidget_2->addTab(tab, "Statistiques");
    ui->tabWidget_2->setCurrentWidget(tab);

    // Step 9: Optional - Ensure chart view resizes properly
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(500, 400); // Adjust size as needed
}


void MainWindow::on_email_to_textChanged(const QString &text)
{
    QStringList filteredEmails;

    // Iterate over the email list and check if the email starts with the entered text
    for (const QString &email : emailList) {
        if (email.startsWith(text, Qt::CaseInsensitive)) {
            filteredEmails.append(email);
        }
    }

    // Update the ComboBox with the filtered emails
    ui->email_to_comboBox->clear();  // Clear previous results
    ui->email_to_comboBox->addItems(filteredEmails);
}

void MainWindow::on_send_clicked(){
    QString email_to = ui->email_to_comboBox->currentText(); // Get selected email from ComboBox
    QString subject = ui->subject->text();
    QString email_body = ui->email_body->text();

    // Create an SMTP client
    SmtpClient smtp("smtp.gmail.com", 587, SmtpClient::TlsConnection);

    // Set up authentication (app password)
    QString username = "qmayra1234@gmail.com";  // Replace with your Gmail address
    QString password = "xdek yenj qhma huqb";  // Replace with your App Password

    MimeMessage message;
    EmailAddress sender("qmayra1234@gmail.com", "Eya");
    message.setSender(sender);

    // Set the email content
    EmailAddress recipient(email_to);  // Recipient address from ComboBox
    message.addRecipient(recipient);

    message.setSubject(subject);

    MimeText text;
    text.setText(email_body);
    message.addPart(&text);

    // Connect to the SMTP server and send email
    smtp.connectToHost();  // Initiates the connection
    if (smtp.waitForReadyConnected()) {
        smtp.login(username, password, SmtpClient::AuthLogin);  // Login (void function, no check for return value)

        if (smtp.waitForAuthenticated()) {
            smtp.sendMail(message);  // Send the email (no return value)
            QMessageBox::information(this, "Success", "Email sent successfully.");
        } else {
            QMessageBox::warning(this, "Authentication Error", "Failed to authenticate.");
        }
    } else {
        QMessageBox::warning(this, "Connection Error", "Failed to connect to the SMTP server.");
    }

    smtp.quit();

}


//////////faceid/////////////
void MainWindow::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus == QProcess::NormalExit && exitCode == 0) {
        // Success
        QMessageBox::information(this, "Process Completed","succeded to run");
    } else {
        // Failure
        QMessageBox::warning(this, "Process Failed", "failed to run.");
    }
}

void MainWindow::on_save_f_clicked()
{

        QString program = "C:\\Users\\SBS\\anaconda3\\python.exe";
        QStringList arguments;

        // Ask the user for a User ID through Qt dialog
        bool ok;
        int userId = QInputDialog::getInt(this, tr("Enter User ID"), tr("User ID:"), 1, 1, 100, 1, &ok);

        if (ok) {
            arguments << "C:\\Users\\SBS\\Documents\\tryy\\script.py" << QString::number(userId);
        }

        // Create a new QProcess instance
        QProcess *process = new QProcess(this);

        // Set the working directory to where the Python script is located
        process->setWorkingDirectory("C:\\Users\\SBS\\Documents\\tryy");

        // Start the Python script with the provided arguments
        process->start(program, arguments);

        // Check if the process was successfully started
        if (!process->waitForStarted()) {
            qDebug() << "Failed to start the process.";
            QMessageBox::critical(this, "Error", "Failed to start the Python process.");
            return;
        }

        // Capture the standard output and error of the process
        connect(process, &QProcess::readyReadStandardOutput, this, [process]() {
            QByteArray output = process->readAllStandardOutput();
            qDebug() << "Python Output: " << output;
        });

        connect(process, &QProcess::readyReadStandardError, this, [process]() {
            QByteArray error = process->readAllStandardError();
            qDebug() << "Python Error: " << error;
        });

        // Connect to the process's finished signal to handle completion
        connect(process, &QProcess::finished, this, &MainWindow::onProcessFinished);




}

void MainWindow::on_recognise_f_clicked()
{
    // Path to the Python executable
       QString program = "C:\\Users\\SBS\\anaconda3\\python.exe";  // Modify if necessary

       // Path to your Python face recognition script
       QStringList arguments;
       // Ask the user for a User ID through Qt dialog
       bool ok;
       int userId = QInputDialog::getInt(this, tr("Enter User ID"), tr("User ID:"), 1, 1, 100, 1, &ok);

       if (ok) {
           arguments << "C:\\Users\\SBS\\Documents\\tryy\\script3.py" << QString::number(userId);
       }

       // Create a QProcess to run the Python script
       QProcess *process = new QProcess(this);

       // Connect the process to output for debugging (optional)
       connect(process, &QProcess::readyReadStandardOutput, [process]() {
           QByteArray output = process->readAllStandardOutput();
           qDebug() << "Python output:" << output;
       });

       // Start the Python script with the given arguments
       process->start(program, arguments);

       // Optionally, handle process errors
       connect(process, &QProcess::errorOccurred, [](QProcess::ProcessError error) {
           qDebug() << "Error occurred:" << error;
       });

}


void MainWindow::openDoor() {
    QByteArray command = "open\n";  // Command to send to Arduino
    command = command.toLower();   // Convert to lowercase
    qDebug() << "Sending command to Arduino:" << command;
    A.write_to_arduino(command);    // Send the command
}

QString buffer;  // Declare a buffer to accumulate fragments

void MainWindow::update_label() {
    QByteArray data = A.read_from_arduino();  // Read data from Arduino
    qDebug() << "Raw data received from Arduino:" << data;

    buffer.append(QString(data));  // Append the new fragment to the buffer

    // Check if the buffer contains the delimiter for the end of the UID
    if (buffer.contains("\r\n")) {
        QString UID = buffer.trimmed();  // Trim spaces or newlines
        buffer.clear();  // Clear the buffer after processing the UID
        qDebug() << "Complete UID received:" << UID;

        // Convert UID to uppercase to ensure case consistency
        UID = UID.toUpper();
        if (!UID.isEmpty()) {
            QSqlQuery query;
            query.prepare("SELECT NOM_EMP, PRENOM_EMP FROM EYA.EMPLOYES WHERE CARD_UID = :uid");
            query.bindValue(":uid", UID);

            if (query.exec() && query.next()) {
                QString name = query.value("NOM_EMP").toString();  // Fetch name
                QString last_name = query.value("PRENOM_EMP").toString();
                QString fullName = name + " " + last_name;
                qDebug() << "Access granted for:" << name;
                ui->label_14->setText("Access granted!");
                ui->label_17->setText("Employee: " + fullName);
                openDoor();
                QTimer::singleShot(4000, this, [this]() {
                        ui->label_14->clear();
                        ui->label_17->clear();
                });

            } else {
                qDebug() << "Access denied: UID not found in database.";
                QTimer::singleShot(3000, this, [this]() {
                        ui->label_16->setText("Access denied: Invalid UID!");

                });
                ui->label_16->clear();
            }
        } else {
            qDebug() << "Empty UID detected.";
            ui->label_16->setText("No UID detected!");
        }
    } else {
        qDebug() << "Waiting for more data to complete the UID.";
    }
}











MainWindow::~MainWindow()
{
    delete ui;
}


















