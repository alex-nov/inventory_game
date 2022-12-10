#include "constants.h"
#include "inventory_utils.h"
#include "iteminventory_view.h"
#include "iteminventory_delegate.h"
#include "databasestorage.h"
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


ItemInventoryView::ItemInventoryView( const quint32 rows, const quint32 columns, QWidget *parent )
    : QTableView( parent )
    , m_rows( rows )
    , m_columns( columns )
{
    // Настройки внешнего вида инвентаря
    setFixedSize( config::INVENTORY_COLUMNS_COUNT * item::draw::ITEM_WIDTH,
                  config::INVENTORY_ROWS_COUNT * item::draw::ITEM_HEIGHT );

    horizontalHeader()->setDefaultSectionSize( item::draw::ITEM_WIDTH );
    verticalHeader()->setDefaultSectionSize( item::draw::ITEM_HEIGHT );
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
    m_current_drag_index = QModelIndex();

    // на старте инвентарь неактивен
    setEnabled( false );
}


void ItemInventoryView::dragEnterEvent( QDragEnterEvent *event )
{
    if( event->mimeData()->hasFormat( ItemMimeData::MimeType() ) )
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

void ItemInventoryView::dragLeaveEvent( QDragLeaveEvent *event )
{
    m_current_drag_index = QModelIndex();
    event->accept();
}

void ItemInventoryView::dragMoveEvent( QDragMoveEvent *event )
{
    if( m_current_drag_index.isValid() &&
        m_current_drag_index == indexAt( event->pos() ) )
    {
        return;
    }

    if ( event->mimeData()->hasFormat( ItemMimeData::MimeType() ) )
    {
        const ItemMimeData* mime_data = dynamic_cast< const ItemMimeData* >( event->mimeData() );

        m_current_drag_index = indexAt( event->pos() );

        auto item_type_placed = DatabaseStorage::Instance()->GetItemType( m_current_drag_index );
        item::item_type item_type_taken;
        if( mime_data->GetMovedItem() )
        {
            item_type_taken = mime_data->GetMovedItem()->GetItemType();
        }
        else
        {
            auto taken_index = indexAt( mime_data->GetDragPoint() );
            item_type_taken = DatabaseStorage::Instance()->GetItemType( taken_index );
        }

        if( item_type_placed == item::item_type::none ||
            item_type_placed == item_type_taken )
        {
            event->setDropAction( Qt::MoveAction );
            event->accept();
            return;
        }
    }

    event->ignore();
}

void ItemInventoryView::dropEvent( QDropEvent *event )
{
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
        // Кладём новый объект из фабрики в инвентарь
        auto moved_item = mime_data->GetMovedItem();
        if( moved_item )
        {
            item_model->setData( model_index,
                                 utils::ConvertItemToHashTable( moved_item ),
                                 inventory_role::add_item );
        }
        // Передвигаем элементы внутри инвентаря
        else
        {
            // Проверка, что не кладём, откуда взяли
            if( indexAt( event->pos() ) == indexAt( mime_data->GetDragPoint() ) ||
                mime_data->GetDragPoint().x() < 0 ||
                mime_data->GetDragPoint().y() < 0 )
            {
                event->ignore();
                return;
            }

            QModelIndex from_index = indexAt( mime_data->GetDragPoint() );
            item_model->setData( model_index,
                                 from_index,
                                 inventory_role::add_many_items );
            update( from_index );
        }

        event->setDropAction( Qt::MoveAction );
        event->accept();
    }
    update( model_index );

    m_current_drag_index = QModelIndex();
}

void ItemInventoryView::mouseMoveEvent( QMouseEvent *event )
{
    if( ~event->buttons() & Qt::LeftButton )
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
        auto hot_spot = event->pos() - QPoint( item::draw::ITEM_WIDTH * model_index.column(),
                                               item::draw::ITEM_HEIGHT * model_index.row() );

        auto mime_data = new ItemMimeData;
        mime_data->SetDragPoint( m_drag_point );

        QRect draw_rect( 0, 0, item::draw::ITEM_WIDTH, item::draw::ITEM_HEIGHT );
        int item_count = model_index.data( inventory_role::count_role).toInt();

        auto drag = new QDrag( this );
        drag->setPixmap( utils::DrawItemForWidget(
                             draw_rect,
                             DatabaseStorage::Instance()->GetItemType( model_index ),
                             item_count,
                             true ) );
        drag->setHotSpot( hot_spot );
        drag->setMimeData( mime_data );
        drag->exec( Qt::MoveAction );

        m_current_drag_index = indexAt( event->pos() );
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
