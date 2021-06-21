#include "mainwindow.h"
#include "ui_mainwindow.h"

QStack<IMemento*> MementoCollector::m_back;
QStack<IMemento*> MementoCollector::m_ahead;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new MyModel(this))
{
    ui->setupUi(this);
    setWindowTitle("Таблица");
    ui->tableView->setModel(model);
    RedactorDelegate *cell_editor = new RedactorDelegate(this);
    ui->tableView->setItemDelegate(cell_editor);;
    connect(cell_editor, SIGNAL(commit_data(QWidget*)), this, SLOT(save_editor()));
    ui->spinBox_2->setMinimum(1);
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
        buffer_model = ui->tableView->selectionModel()->selection().indexes();
    }
    if (event->key() == Qt::Key_V && event->modifiers() == Qt::ControlModifier)
    {
        if (!buffer_model.isEmpty())
        {
            if (!ui->tableView->selectionModel()->selection().indexes().isEmpty())
            {
                save_back();
                QModelIndexList past_model = ui->tableView->selectionModel()->selection().indexes();
                int j = 0;
                for (int i=0; i<past_model.size(); i++, j++)
                {
                    if (j == buffer_model.size())
                        j = 0;
                    model->setData(past_model[i],buffer_model[j].data());
                }
                model->dataChanged(past_model.first(), past_model.last());
            }
        }
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

void MainWindow::on_action_triggered()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Инструкция");
    msgBox.setText("Для редактирования размеров таблицы необходимо использовать кнопки, "
                   "расположенные в правой части окна. \nТам находятся кнопки для вставки/удаления "
                   "строк и столбцов таблицы, а также поля для ввода индекса строки/столбца для вставки"
                   "и количества строк/столбцов, которые будут вставлены. \nПри указании индекса, который "
                   "не существует в таблицу вставка будет произведена в конец таблицы. При попытке удаления "
                   "не сушествующих столбцов появится сообщение об ошибке, а операция не будет произведена. "
                   "\nВ той же части находятся кнопка для смены имени заголовка и поле для ввода нового имени. "
                   "Также там находится кнопка для сброса таблицы."
                   "\nТаблица поддерживает несколько горячих клавиш:"
                   "\n- Ctrl+C - копирование выделенных элементов"
                   "\n- Ctrl+V - вставка скопированных элементов"
                   "\n- Ctrl+Z - откат действия (стек действий не ограничен)"
                   "\n- Ctrl+Y - восстановление отмененного действия (стек также не ограничен)");
    msgBox.exec();
}
