#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include "repgen/repgen.h"
#include <QFileDialog>
#include "db.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Get the current working directory and create the full path to "report.pdf" and db
    QString reportFile = QDir::current().filePath("report.pdf");
    QString dbFile = QDir::current().filePath("analysis.sqlite");

    // Set the initial value of the QLineEdits
    ui->filenameLineEdit->setText(reportFile);
    ui->dbFilenameLineEdit->setText(dbFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generatePushButton_clicked()
{
    // Get name from line edit UI
    QString name = ui->nameLineEdit->text();
    std::string reportName = !name.isEmpty() ? name.toStdString() : "NoName";
    std::string dbFile = ui->dbFilenameLineEdit->text().toStdString();

    // Read Database, initialize storage with ORM mappings
    auto storage = initStorage(dbFile);

    // Fetch all entries from the marked_feature table
    auto marked_features = storage.get_all<MarkedFeature>();

    // Display the fetched data
    for (const auto &feature : marked_features)
    {
        qInfo() << "ID: " << feature.id
                << ", Dist0: " << feature.dist0 << ", Angle0: " << feature.angle0
                << ", Dist1: " << feature.dist1 << ", Angle1: " << feature.angle1
                << ", Feature Type: " << feature.feature_type
                << ", Note: " << QString::fromStdString(feature.note)
                << ", Is Cluster: " << feature.is_cluster;
    }

    // Generate latex as string
    std::string renderedLatex = repgen::generateAnomaliesSummary(reportName);

    // Get the final output PDF path from filenameLineEdit
    QString pdfFilePath = ui->filenameLineEdit->text();

    // Compile LaTeX to PDF using a generated .tex file
    if (!repgen::compileToPdf(renderedLatex, pdfFilePath.toStdString()))
    {
        ui->statusbar->showMessage(tr("Error writing to file!"), 5000);
        return;
    }

    ui->statusbar->showMessage(tr("PDF generated successfully!"), 5000);
}

void MainWindow::on_filenamePushButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(
        this, "Select PDF File to Save", "", "PDF Files (*.pdf);;All Files (*)");

    if (!filePath.isEmpty())
    {
        emit fileSelected(filePath); // Emit signal when file is selected
    }
}

void MainWindow::on_dbFilenamePushButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this, "Select sqlite File to Open", "", "SQLite3 Files (*.sqlite);;All Files (*)");

    if (!filePath.isEmpty())
    {
        emit dbFileSelected(filePath); // Emit signal when file is selected
    }
}
