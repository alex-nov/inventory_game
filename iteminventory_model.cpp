#include "iteminventory_model.h"
#include "itemfactory.h"
#include "constants.h"
#include "inventory_utils.h"

#include <QDebug>
#include <QPoint>


ItemInventoryModel::ItemInventoryModel(  const quint32 rows, const quint32 columns )
    : m_rows( rows )
    , m_columns( columns )
{
}

int ItemInventoryModel::rowCount( const QModelIndex &parent ) const
{
    Q_UNUSED(parent);

    return m_rows;
}

int ItemInventoryModel::columnCount( const QModelIndex &parent ) const
{
    Q_UNUSED(parent);

    return m_columns;
}

QVariant ItemInventoryModel::data( const QModelIndex &index, int role ) const
{
    QVariant variant_result;
    if( !index.isValid() )
    {
        return variant_result;
    }

    switch ( role )
    {
        case Qt::DecorationRole:
        {
            variant_result = DatabaseStorage::Instance()->GetItemImagePath( index.row(), index.column() );
        }
        break;

        case inventory_role::count_role:
        {
            variant_result = DatabaseStorage::Instance()->GetItemsCountByPosition( index.row(), index.column() );
        }
        break;

    }

    return variant_result;
}

bool ItemInventoryModel::setData( const QModelIndex &index, const QVariant &value, int role)
{
    bool t_bool_success = false;

    if( !index.isValid() )
    {
        return t_bool_success;
    }

    switch ( role )
    {
        case inventory_role::add_item:
        {
            if( value.canConvert( QMetaType::QVariantHash ) )
            {
                t_bool_success = DatabaseStorage::Instance()->MoveItemToInventory(
                        index.row(),
                        index.column(),
                        utils::ConvertItemHashToItem( value.toHash() )
                );
            }
        }
        break;

        case inventory_role::add_many_items:
        {
            if( value.canConvert( QMetaType::QPoint ) )
            {
                t_bool_success = DatabaseStorage::Instance()->MoveItemsIntoInventory(
                     value.toPoint().x(),
                     value.toPoint().y(),
                     index.row(),
                     index.column()
                );
            }
        }
        break;

        case inventory_role::delete_item:
        {
            t_bool_success = DatabaseStorage::Instance()->DeleteItemFromInventory( index.row(), index.column() );
        }
        break;

    }

    return t_bool_success;
}
