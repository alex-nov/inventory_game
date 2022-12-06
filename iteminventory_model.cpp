#include "iteminventory_model.h"
#include "itemfactory.h"
#include "constants.h"

#include <QDebug>


ItemInventoryModel::ItemInventoryModel()
{
}

int ItemInventoryModel::rowCount( const QModelIndex &parent ) const
{
    Q_UNUSED(parent);

    return config::INVENTORY_ROWS_COUNT;
}

int ItemInventoryModel::columnCount( const QModelIndex &parent ) const
{
    Q_UNUSED(parent);

    return config::INVENTORY_COLUMNS_COUNT;
}

QVariant ItemInventoryModel::data( const QModelIndex &index, int role ) const
{
     Q_UNUSED(role);
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
    if(!index.isValid()) {
        return t_bool_success;
    }

    switch ( role )
    {
        case inventory_role::count_role:
        {
            if( value.canConvert( QMetaType::Int ) )
            {
                if( value.toInt() > 0 )
                {
                    DatabaseStorage::Instance()->MoveItemToInventory(
                                index.row(), index.column(),
                                ItemFactory::Instance()->CreateItem( item_type::apple ) );

                    qDebug() << "ItemInventoryModel::setData add at row" << index.row()
                             << " column" << index.column();
                }
                else
                {
                    DatabaseStorage::Instance()->DeleteItemFromInventory( index.row(), index.column() );

                    qDebug() << "ItemInventoryModel::setData delete from row" << index.row()
                             << " column" << index.column();
                }
            }
        }
        break;
    }

    return t_bool_success;
}
