#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include "ReportService.h"
#include "PdfCompiler.h"
#include <QFileDialog>

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
    std::string dbFile = ui->dbFilenameLineEdit->text().toStdString();

    // Generate latex as string
    ReportService reportService(dbFile);
    ReportService::ServiceOptions options = {false};
    auto renderedLatex = reportService.request("features_identification", options);
    if (!renderedLatex)
    {
        ui->statusbar->showMessage(tr("Error generating tex content!"), 5000);
        return;
    }

    // Get the final output PDF path from filenameLineEdit
    QString pdfFilePath = ui->filenameLineEdit->text();

    // Compile LaTeX to PDF using a generated .tex file
    if (!PdfCompiler::compile(*renderedLatex, pdfFilePath.toStdString()))
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
