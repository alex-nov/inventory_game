#include "inventory_utils.h"

#include "QPainter"

namespace utils
{

QPixmap DrawSelectedItemForDrag( const QRect& area,
                                 const item_type type,
                                 const int item_count )
{
     ;
    switch( type )
    {
        case item_type::apple:
        {
            QPixmap pix( item::draw::APPLE_WIDTH, item::draw::APPLE_HEIGHT );
            QPainter painter( &pix );
            painter.drawPixmap( area, QPixmap( item::APPLE_IMAGE_PATH ) );
            painter.setPen( item::draw::SELECTION_PEN );
            painter.setBrush( item::draw::SELECTION_BRUSH );
            painter.drawRect( 1, 1, item::draw::APPLE_WIDTH - 2, item::draw::APPLE_HEIGHT - 2 );

            if( item_count > 0 )
            {
                QString string_result = QString( "%1" ).arg( item_count );
                painter.drawText( area, Qt::AlignBottom | Qt::AlignRight, string_result );
            }

            painter.end();
            return pix;
        }
        break;
    }

    return QPixmap();
}

}
