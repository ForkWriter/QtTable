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
    connect(ui->pushButton, &QPushButton::clicked, [=](){model->insertRows(0,2);});
    connect(ui->pushButton_2, &QPushButton::clicked, [=](){model->removeRows(0,2);});
    connect(ui->pushButton_3, &QPushButton::clicked, [=](){model->insertColumns(0,2);});
    connect(ui->pushButton_4, &QPushButton::clicked, [=](){model->removeColumns(0,2);});
}

MainWindow::~MainWindow()
{
    delete ui;
}
