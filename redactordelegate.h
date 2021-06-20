#ifndef REDACTORDELEGATE_H
#define REDACTORDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QApplication>
#include <QLineEdit>


class RedactorDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit RedactorDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:
    void commit_data(QWidget *editor) const;
};

#endif // REDACTORDELEGATE_H
