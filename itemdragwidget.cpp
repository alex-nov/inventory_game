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

ItemDragWidget::ItemDragWidget(  const item::item_type type, QWidget *parent )
    : QLabel( parent )
    , m_factory_type( type )
{
    setFixedSize( item::draw::ITEM_WIDTH, item::draw::ITEM_HEIGHT );
    setPixmap( utils::DrawItemForWidget( rect(), m_factory_type, 0 ) );
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
            auto new_item = ItemFactory::Instance()->CreateItem( m_factory_type );
            mime_data->SetMovedItem( new_item );

            auto drag = new QDrag( this );
            drag->setPixmap( utils::DrawItemForWidget( rect(), m_factory_type, 0, true ) );
            drag->setHotSpot( event->pos() );
            drag->setMimeData( mime_data );
            drag->exec( Qt::CopyAction );
        }
    }
    QWidget::mouseMoveEvent( event );
}
