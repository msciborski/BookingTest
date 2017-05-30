#include "editedtextfield.h"

EditedTextField::EditedTextField(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant EditedTextField::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex EditedTextField::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex EditedTextField::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int EditedTextField::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int EditedTextField::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant EditedTextField::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
