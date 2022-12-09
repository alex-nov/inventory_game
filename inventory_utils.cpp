#include "inventory_utils.h"

#include <QPainter>
#include <QHash>
#include <QString>
#include <QVariant>

namespace utils
{

QPixmap DrawSelectedItemForDrag( const QRect& area,
                                 const item::item_type type,
                                 const int item_count )
{
    QPixmap pix( item::draw::ITEM_WIDTH, item::draw::ITEM_HEIGHT );
    QPainter painter( &pix );
    painter.setBrush( Qt::white );
    painter.setPen( Qt::NoPen );
    painter.drawRect( area );
    switch( type )
    {
        case item::item_type::apple:
        {
           painter.drawPixmap( area, QPixmap( item::APPLE_IMAGE_PATH ) );
        }
        break;

        case item::item_type::orange:
        {
           painter.drawPixmap( area, QPixmap( item::ORANGE_IMAGE_PATH ) );
        }
        break;
    }
    painter.setPen( item::draw::SELECTION_PEN );
    painter.setBrush( item::draw::SELECTION_BRUSH );
    painter.drawRect( 1, 1, item::draw::ITEM_WIDTH - 2, item::draw::ITEM_HEIGHT - 2 );

    if( item_count > 0 )
    {
        QString string_result = QString( "%1" ).arg( item_count );
        painter.drawText( area, Qt::AlignBottom | Qt::AlignRight, string_result );
    }

    painter.end();
    return pix;


    return QPixmap();
}

QHash< QString, QVariant > ConvertItemToHashTable( const std::shared_ptr< Item > item )
{
    QHash< QString, QVariant > result;
    result.insert( "id", item->GetItemId() );
    result.insert( "type", static_cast< quint8 >( item->GetItemType() ) );
    result.insert( "path", item->GetImagePath() );
    return result;
}

std::shared_ptr< Item > ConvertItemHashToItem( const QHash< QString, QVariant > item_hash )
{
    return std::make_shared< Item >( item_hash[ "id" ].toUInt(),
                 static_cast< item::item_type >( item_hash[ "type" ].toUInt() ),
                 item_hash[ "path" ].toString() );
}

}
