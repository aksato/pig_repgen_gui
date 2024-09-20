#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include "repgen/repgen.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Get the current working directory and create the full path to "report.pdf"
    QString reportFile = QDir::current().filePath("report.pdf");

    // Set the initial value of the QLineEdit
    ui->filenameLineEdit->setText(reportFile);
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

    // Generate latex as string
    std::string renderedLatex = repgen::generateAnomaliesSummary(reportName);

    // Get the final output PDF path from filenameLineEdit
    QString pdfFilePath = ui->filenameLineEdit->text();

    // Compile LaTeX to PDF using a generated .tex file
    if(!repgen::compileToPdf(renderedLatex, pdfFilePath.toStdString())){
        ui->statusbar->showMessage(tr("Error writing to file!"), 5000);
        return;
    }

    ui->statusbar->showMessage(tr("PDF generated successfully!"), 5000);
}


void MainWindow::on_filenamePushButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(
        this, "Select PDF File to Save", "", "PDF Files (*.pdf);;All Files (*)");

    if (!filePath.isEmpty()) {
        emit fileSelected(filePath);  // Emit signal when file is selected
    }
}

