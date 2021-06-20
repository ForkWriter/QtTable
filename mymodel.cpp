#include "mymodel.h"

MyModel::MyModel(QObject *parent) : QAbstractTableModel(parent)
{

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
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Error!");
        msgBox.setText("Some of the specified rows cannot be removed.");
        msgBox.exec();
    }

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
        QVariant val;
        if (column < headers.count())
        {
            val = column + pos;
            headers.insert(headers.begin()+val.toInt(), val.toString());
        }
        else
        {
            val = headers.count();
            headers.append(val.toString());
        }
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
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Error!");
        msgBox.setText("Some of the specified columns cannot be removed.");
        msgBox.exec();
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
          return content[index.row()][index.column()];
        case Qt::TextAlignmentRole:
          return Qt::AlignCenter;
        case Qt::SizeHintRole:
          return QSize(0,30);
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

bool MyModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (orientation == Qt::Horizontal && role == Qt::EditRole)
        headers[section] = value.toString();
    emit headerDataChanged(Qt::Horizontal,section,section);
    return true;
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
        content[index.row()][index.column()] = value.toString();
    return true;
}

void MyModel::modelReset()
{
    beginResetModel();

    removeRows(0, content.count());
    removeColumns(0, headers.count());

    endResetModel();
}

void MyModel::modelCopy(MyModel *copy)
{
    insertRows(0, copy->content.count());
    insertColumns(0, copy->headers.count());
    for (int i=0; i<copy->headers.count(); i++)
        setHeaderData(i, Qt::Horizontal, copy->headerData(i, Qt::Horizontal));
    for (int i=0; i<copy->content.count(); i++)
        for (int j=0; j<copy->headers.count(); j++)
            setData(index(i,j), copy->data(index(i,j),Qt::DisplayRole));
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}
