#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QSize>
#include <QFont>

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MyModel(QObject *parent);

    int rowCount(const QModelIndex &parent) const;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    int columnCount(const QModelIndex &parent) const;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex());
    //void columnAdd(const QVariant &value, QString header);
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    QList<QVector<QString>> content;
    QList<QString> headers;
};

#endif // MYMODEL_H
