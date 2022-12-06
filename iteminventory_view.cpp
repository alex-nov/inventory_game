#include "constants.h"
#include "iteminventory_view.h"
#include "iteminventory_delegate.h"
#include "itemmimedata.h"
#include "itemfactory.h"

#include <QHeaderView>
#include <QMouseEvent>
#include <QDebug>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDrag>
#include <QApplication>
#include <QPainter>


ItemInventoryView::ItemInventoryView( QWidget *parent )
    : QTableView( parent )
{
    // Настройки внешнего вида инвентаря
    setFixedSize( config::INVENTORY_COLUMNS_COUNT * config::ITEM_WIDTH,
                  config::INVENTORY_ROWS_COUNT * config::ITEM_HEIGHT );

    horizontalHeader()->setDefaultSectionSize( config::ITEM_WIDTH );
    verticalHeader()->setDefaultSectionSize( config::ITEM_HEIGHT );
    horizontalHeader()->hide();
    verticalHeader()->hide();

    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    setItemDelegate( new InventoryDelegate( this ) );

    setFrameShape( QFrame::NoFrame );

    // Настройки drag and drop
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);

    m_drag_point = QPoint();
}


void ItemInventoryView::dragEnterEvent( QDragEnterEvent *event )
{
    if( event->mimeData()->hasFormat( ItemMimeData::MimeType() ) )
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void ItemInventoryView::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void ItemInventoryView::dragMoveEvent(QDragMoveEvent *event)
{
    if ( event->mimeData()->hasFormat( ItemMimeData::MimeType() ) )
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void ItemInventoryView::dropEvent( QDropEvent *event )
{
    qDebug() << "ItemInventoryView::dropEvent " << event->pos();

    QModelIndex model_index = indexAt( event->pos() );
    if( !model_index.isValid() )
    {
        event->ignore();
        return;
    }

    const ItemMimeData* mime_data = dynamic_cast< const ItemMimeData* >( event->mimeData() );
    QAbstractItemModel * item_model = qobject_cast< QAbstractItemModel* >( model() );
    if( mime_data && item_model )
    {
        // Кладём новый объект из фабрики
        if( mime_data->GetMovedItem() )
        {
            if( mime_data->GetMovedItem()->GetItemType() == item_type::apple )
            item_model->setData( model_index,
                                 mime_data->GetMovedItem()->GetItemId(),
                                 inventory_role::add_apple );
        }
        // Передвигаем элементы внутри инвентаря
        else
        {
            // Проверка, что не кладём, откуда взяли
            if( indexAt( event->pos() ) == indexAt( m_drag_point ) )
            {
                event->ignore();
                return;
            }

            QModelIndex from_index = indexAt( mime_data->GetDragPoint() );
            item_model->setData( model_index,
                                 QPoint( from_index.row(), from_index.column() ),
                                 inventory_role::add_many_items );
            update( from_index );
        }
        event->setDropAction( Qt::MoveAction );
        event->accept();
    }
    update( model_index );
}

void ItemInventoryView::mouseMoveEvent( QMouseEvent *event )
{
    if( !event->buttons() & Qt::LeftButton )
    {
        QWidget::mouseMoveEvent( event );
        return;
    }

    int distance = ( event->pos() - m_drag_point ).manhattanLength();
    QModelIndex model_index = indexAt( m_drag_point );
    auto items_count = model_index.data( inventory_role::count_role );

    // Начинаем перетаскивать есть сдвинули на определенное расстояние
    // и стартовая ячейка не пустая
    if( distance > QApplication::startDragDistance() &&
        items_count.canConvert( QMetaType::Int )     &&
        items_count.toInt() > 0 )
    {
        auto hot_spot = event->pos() - QPoint( config::ITEM_WIDTH * model_index.column(),
                                               config::ITEM_HEIGHT * model_index.row() );

        auto mime_data = new ItemMimeData;
        mime_data->SetDragPoint( m_drag_point );

        auto drag = new QDrag( this );
        drag->setPixmap( QPixmap( config::APPLE_IMAGE_PATH ) );
        drag->setHotSpot( hot_spot );
        drag->setMimeData( mime_data );
        drag->exec( Qt::MoveAction );
    }

    QWidget::mouseMoveEvent( event );
}

void ItemInventoryView::mousePressEvent( QMouseEvent *event )
{
    QModelIndex model_index = indexAt( event->pos() );
    QAbstractItemModel * item_model = qobject_cast< QAbstractItemModel* >( model() );

    // Фиксируем стартовое положение переноса объектов
    if( event->button() == Qt::LeftButton )
    {
        m_drag_point = event->pos();
    }
    else if( event->button() == Qt::RightButton )
    {
        qDebug() << "right button click row "  << model_index.row() << " column " << model_index.column();
        if( item_model )
        {
            if( item_model->setData( model_index, QVariant(), inventory_role::delete_item ) )
            {
                 QSound::play( config::APPLE_DELETE_SOUND_PATH );
            }
        }
    }

    QTableView::mousePressEvent(event);
}
