#include "mainwindow.h"
#include "ui_mainwindow.h"

QStack<IMemento*> MementoCollector::m_back;
QStack<IMemento*> MementoCollector::m_ahead;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), model(new MyModel(this))
{
    ui->setupUi(this);
    ui->tableView->setModel(model);
    RedactorDelegate *cell_editor = new RedactorDelegate(this);
    ui->tableView->setItemDelegate(cell_editor);;
    connect(cell_editor, SIGNAL(commit_data(QWidget*)), this, SLOT(save_editor()));
    connect(ui->pushButton, &QPushButton::clicked, [=](){save_back();model->insertRows(ui->spinBox->value(),ui->spinBox_2->value());});
    connect(ui->pushButton_2, &QPushButton::clicked, [=](){save_back();model->removeRows(ui->spinBox->value(),ui->spinBox_2->value());});
    connect(ui->pushButton_3, &QPushButton::clicked, [=](){save_back();model->insertColumns(ui->spinBox->value(),ui->spinBox_2->value());});
    connect(ui->pushButton_4, &QPushButton::clicked, [=](){save_back();model->removeColumns(ui->spinBox->value(),ui->spinBox_2->value());});
    connect(ui->pushButton_5, &QPushButton::clicked, [=](){save_back();model->setHeaderData(ui->spinBox->value(),Qt::Horizontal,ui->lineEdit->text());});
    connect(ui->pushButton_6, &QPushButton::clicked, [=](){save_back();model->modelReset();});
}

MainWindow::~MainWindow()
{
    delete ui;
}

IMemento *MainWindow::save()
{
    MyModel *memory = new MyModel(this);
    memory->modelCopy(model);
    Memento *out = new Memento(memory,this);
    return out;
}

void MainWindow::save_back()
{
    MementoCollector::clearAhead();
    MementoCollector::addBack(save());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_C && event->modifiers() == Qt::ControlModifier)
    {

    }
    if (event->key() == Qt::Key_V && event->modifiers() == Qt::ControlModifier)
    {

    }
    if (event->key() == Qt::Key_Z && event->modifiers() == Qt::ControlModifier)
    {
        if (MementoCollector::getBackSize() > 0)
        {
            MementoCollector::addAhead(save());
            MementoCollector::restoreBack();
        }
    }
    if (event->key() == Qt::Key_Y && event->modifiers() == Qt::ControlModifier)
    {
        if (MementoCollector::getAheadSize() > 0)
        {
            MementoCollector::addBack(save());
            MementoCollector::restoreAhead();
        }
    }
}

void MainWindow::save_editor()
{
    save_back();
}

void MainWindow::Memento::restoreData()
{
    window->model->modelReset();
    window->model->modelCopy(model);
    window->ui->tableView->setModel(window->model);
}
