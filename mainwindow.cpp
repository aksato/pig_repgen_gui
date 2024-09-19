#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <inja/inja.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    // LaTeX template with placeholders
    std::string latexTemplate = R"(\documentclass{article}
    \begin{document}
    Hello {{ name }}
    \end{document})";

    std::string renderedLatex = inja::render(latexTemplate, data);

    // Write the output to a .tex file
    std::ofstream texFile("mesonqtinja.tex");
    texFile << renderedLatex;
    texFile.close();

    // Compile LaTeX to PDF
    system("pdflatex mesonqtinja.tex");

    ui->statusbar->showMessage(tr("PDF generated successfully!"), 5000);
}

