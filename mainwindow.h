#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
//#include <QItemSelectionModel>
#include "mymodel.h"
#include "imemento.h"
#include "redactordelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MyModel *model;
    QModelIndexList buffer_model;

    class Memento:public IMemento
    {
    public:
        Memento(MyModel *model, MainWindow *window):model(model), window(window){};
        void restoreData() override;
        virtual ~Memento()
        {
            model = nullptr;
            window = nullptr;
        }
    private:
        MyModel *model;
        MainWindow *window;
    };
    friend Memento;
    IMemento* save();
    void save_back();
    void keyPressEvent(QKeyEvent *event);

private slots:
    void save_editor();
    void on_action_triggered();
};
#endif // MAINWINDOW_H
