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

void MainWindow::on_pushButton_clicked()
{
    nlohmann::json data;
    data["name"] = "world";

    qInfo() << QString::fromStdString(inja::render("Hello {{ name }}!", data)); // Returns std::string "Hello world!"
}
