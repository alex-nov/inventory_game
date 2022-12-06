#include "iteminventory_model.h"
#include "itemfactory.h"
#include "constants.h"

#include <QDebug>
#include <QPoint>


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
        case inventory_role::add_apple:
        {
            if( value.canConvert( QMetaType::Int ) )
            {

                t_bool_success = DatabaseStorage::Instance()->MoveItemToInventory(
                     index.row()
                    ,index.column()
                    ,std::make_shared< Item >( value.toInt(), item_type::apple, config::APPLE_IMAGE_PATH )
                );

                qDebug() << "ItemInventoryModel::setData add at row" << index.row()
                         << " column" << index.column();
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

                qDebug() << "ItemInventoryModel::setData add some from" << value.toPoint()
                         << " to row" << index.row() << " column" << index.column();
            }
        }
        break;

        case inventory_role::delete_item:
        {
            t_bool_success = DatabaseStorage::Instance()->DeleteItemFromInventory( index.row(), index.column() );

            qDebug() << "ItemInventoryModel::setData delete from row" << index.row()
                     << " column" << index.column();
        }
        break;
    }

    return t_bool_success;
}
