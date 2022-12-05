#include "iteminventory_model.h"
#include "constants.h"

#include <QDebug>


int getIndexFromRowColumn( int row, int column )
{
    return row * config::INVENTORY_COLUMNS_COUNT + column;
}

ItemInventoryModel::ItemInventoryModel()
{
    m_storage.reserve( config::INVENTORY_COLUMNS_COUNT * config::INVENTORY_ROWS_COUNT );
   for( size_t i = 0; i <config::INVENTORY_COLUMNS_COUNT * config::INVENTORY_ROWS_COUNT; ++i )
       m_storage.push_back( 0 );
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
            if( m_storage.at( getIndexFromRowColumn( index.row(), index.column() ) ) > 0 )
            {
                variant_result = config::APPLE_IMAGE_PATH;
            }
        }
        break;

        case inventory_role::count_role:
        {
            variant_result = m_storage.at( getIndexFromRowColumn( index.row(), index.column() ) );
            qDebug()    << "ItemInventoryModel::Data " << getIndexFromRowColumn( index.row(), index.column() ) << " "
                        << m_storage[ getIndexFromRowColumn( index.row(), index.column() ) ];
        }
        break;

        case inventory_role::type_role:
        {
            variant_result = static_cast<int>( item_type::apple );
        }
        break;
    }

    return variant_result;
}

bool ItemInventoryModel::setData( const QModelIndex &index, const QVariant &value, int role)
{
     Q_UNUSED(role);
     Q_UNUSED(value);
    bool t_bool_success = false;
    if(!index.isValid()) {
        return t_bool_success;
    }

    switch ( role )
    {
        case inventory_role::count_role:
        {
            if(value.canConvert(QMetaType::Int))
            {
                qDebug() << "ItemInventoryModel::setData "<< getIndexFromRowColumn( index.row(), index.column() ) << " "
                         << m_storage[ getIndexFromRowColumn( index.row(), index.column() ) ] << " + " << value.toInt();
                m_storage[ getIndexFromRowColumn( index.row(), index.column() ) ] += value.toInt();
            }
        }
        break;

        case inventory_role::type_role:
        {
            //return item_type::apple;
        }
        break;
    }

    return t_bool_success;
}
