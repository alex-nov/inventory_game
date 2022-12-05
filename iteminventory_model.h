#ifndef ITEMINVENTORYMODEL_H
#define ITEMINVENTORYMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QVector>

class ItemInventoryModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ItemInventoryModel();

    virtual int rowCount(
            const QModelIndex &parent) const Q_DECL_OVERRIDE;

    virtual int columnCount(
            const QModelIndex &parent) const Q_DECL_OVERRIDE;

    virtual QVariant data(
            const QModelIndex &index,
            int role) const Q_DECL_OVERRIDE;

    virtual bool setData(
            const QModelIndex &index,
            const QVariant &value,
            int role) Q_DECL_OVERRIDE;

private:
    std::vector<int> m_storage;
};

#endif // ITEMINVENTORYMODEL_H
