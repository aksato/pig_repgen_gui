#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <inja/inja.hpp>
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
    nlohmann::json data;

    // Get name from line edit UI
    QString name = ui->nameLineEdit->text();
    data["name"] = !name.isEmpty() ? name.toStdString() : "NoName";

    // Get the final output PDF path from filenameLineEdit
    QString pdfFilePath = ui->filenameLineEdit->text();

    // Create the .tex file path using QDir::filePath() for better platform compatibility
    QFileInfo info(pdfFilePath);
    QString texFilePath = QDir(info.path()).filePath(info.baseName() + ".tex");

    // LaTeX template with placeholders
    std::string latexTemplate = R"(\documentclass{article}
    \begin{document}
    Hello {{ name }}
    \end{document})";

    std::string renderedLatex = inja::render(latexTemplate, data);

    // Write the output to a .tex file
    std::ofstream texFile(texFilePath.toStdString());
    if (!texFile) {
        ui->statusbar->showMessage(tr("Error writing to file!"), 5000);
        return;
    }
    texFile << renderedLatex;
    texFile.close();

    // Compile LaTeX to PDF using the generated .tex file
    QString command = "pdflatex " + texFilePath;
    system(command.toStdString().c_str());

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

