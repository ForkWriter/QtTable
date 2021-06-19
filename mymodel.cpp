#include "mymodel.h"

MyModel::MyModel(QObject *parent) : QAbstractTableModel(parent)
{
    headers.append("qwerty");
    headers.append("ytrewq");
}

int MyModel::rowCount(const QModelIndex &parent) const
{
    return content.count();
    Q_UNUSED(parent);
}

bool MyModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row + count - 1);

    for (int pos=0; pos<count; ++pos)
    {
        QVector<QString> vect;
        for (int i=0; i<headers.count(); i++)
            vect.push_back("");
        if (row < content.count())
            content.insert(row, vect);
        else
            content.append(vect);
    }

    endInsertRows();
    return true;
    Q_UNUSED(parent);
}

bool MyModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), row, row + count - 1);

    if (row + count <= content.count())
        content.erase(content.begin()+row, content.begin()+row+count);

    endRemoveRows();
    return true;
    Q_UNUSED(parent);
}

int MyModel::columnCount(const QModelIndex &parent) const
{
    return headers.count();
    Q_UNUSED(parent);
}

bool MyModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(QModelIndex(), column, column + count - 1);

    for (int pos=0; pos<count; ++pos)
    {
        headers.insert(headers.begin()+column, "");
        for (int i=0; i<content.count(); i++)
            if (column < content[i].size())
                content[i].insert(content[i].begin()+column,"");
            else
                content[i].push_back("");
    }

    endInsertColumns();
    return true;
    Q_UNUSED(parent);
}

bool MyModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(QModelIndex(), column, column + count - 1);

    if (column + count <= headers.size())
    {
        headers.erase(headers.begin()+column, headers.begin()+column+count);
        for (int i=0; i<content.count(); i++)
            content[i].erase(content[i].begin()+column, content[i].begin()+column+count);
    }

    endRemoveColumns();
    return true;
    Q_UNUSED(parent);
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role)
    {
        case Qt::DisplayRole:
        //case Qt::EditRole:
          return content[index.row()][index.column()];
        case Qt::TextAlignmentRole:
          return Qt::AlignCenter;
        case Qt::SizeHintRole:
          return QSize(0,40);
        case Qt::FontRole:
          return QFont("Times New Roman", 14);
        default:
            return QVariant();
    }
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return headers.at(section);
    else if (role == Qt::DisplayRole)
        return section;
    return QVariant();
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
        content[index.row()][index.column()] = value.toString();
    return true;
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}
