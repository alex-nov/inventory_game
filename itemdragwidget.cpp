#include "constants.h"
#include "inventory_utils.h"
#include "itemdragwidget.h"
#include "itemmimedata.h"
#include "itemfactory.h"

#include <QMouseEvent>
#include <QApplication>
#include <QMimeData>
#include <QDrag>
#include <QPainter>
#include <QBrush>

ItemDragWidget::ItemDragWidget( QWidget *parent )
    : QLabel( parent )
{
    auto item_pixmap = new QPixmap();
    item_pixmap->load( item::APPLE_IMAGE_PATH );
    setPixmap( *item_pixmap );
    setEnabled( false );
}

void ItemDragWidget::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton )
    {
        m_drag_point = event->pos();
    }
    QWidget::mousePressEvent( event );
}

void ItemDragWidget::mouseMoveEvent(QMouseEvent *event)
{
    if( event->buttons() & Qt::LeftButton )
    {
        int distance = ( event->pos() - m_drag_point ).manhattanLength();
        if( distance > QApplication::startDragDistance() )
        {
            auto mime_data = new ItemMimeData;
            auto new_item = ItemFactory::Instance()->CreateItem( item_type::apple );
            mime_data->SetMovedItem( new_item );

            auto drag = new QDrag( this );
            drag->setPixmap( utils::DrawSelectedItemForDrag( rect(), item_type::apple, 0 ) );
            drag->setHotSpot( event->pos() );
            drag->setMimeData( mime_data );
            drag->exec( Qt::CopyAction );
        }
    }
    QWidget::mouseMoveEvent( event );
}
