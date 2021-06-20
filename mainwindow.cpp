#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mymodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyModel *model = new MyModel(this);
    ui->tableView->setModel(model);
    connect(ui->pushButton, &QPushButton::clicked, [=](){model->insertRows(ui->spinBox->value(),ui->spinBox_2->value());});
    connect(ui->pushButton_2, &QPushButton::clicked, [=](){model->removeRows(ui->spinBox->value(),ui->spinBox_2->value());});
    connect(ui->pushButton_3, &QPushButton::clicked, [=](){model->insertColumns(ui->spinBox->value(),ui->spinBox_2->value());});
    connect(ui->pushButton_4, &QPushButton::clicked, [=](){model->removeColumns(ui->spinBox->value(),ui->spinBox_2->value());});
    connect(ui->pushButton_5, &QPushButton::clicked, [=](){model->setHeaderData(ui->spinBox->value(),Qt::Horizontal,ui->lineEdit->text());});
}

MainWindow::~MainWindow()
{
    delete ui;
}
