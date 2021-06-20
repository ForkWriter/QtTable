#include "redactordelegate.h"

RedactorDelegate::RedactorDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *RedactorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    emit commit_data(editor);
    return editor;
    Q_UNUSED(option);
    Q_UNUSED(index);
}

void RedactorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *redactor = static_cast<QLineEdit*>(editor);
    redactor->setText(index.data().toString());
}

void RedactorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *redactor = static_cast<QLineEdit*>(editor);
    model->setData(index, redactor->text());
}

void RedactorDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
    Q_UNUSED(index);
}

void RedactorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}
