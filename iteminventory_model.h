#ifndef ITEMINVENTORYMODEL_H
#define ITEMINVENTORYMODEL_H

#include <databasestorage.h>

#include <QObject>
#include <QAbstractTableModel>
#include <QVector>

class ItemInventoryModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ItemInventoryModel( const quint32 rows = config::INVENTORY_ROWS_COUNT,
                        const quint32 columns = config::INVENTORY_COLUMNS_COUNT );

    /* Переопределение методов модели */
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
    quint32 m_rows;
    quint32 m_columns;
};

#endif // ITEMINVENTORYMODEL_H
