#include "iteminventory_view.h"
#include "iteminventory_delegate.h"
#include "constants.h"
#include "itemfactory.h"

#include <QHeaderView>
#include <QMouseEvent>
#include <QDebug>


ItemInventoryView::ItemInventoryView( QWidget *parent )
    : QTableView( parent )
{
    setFixedSize( config::INVENTORY_COLUMNS_COUNT * config::ITEM_WIDTH,
                  config::INVENTORY_ROWS_COUNT * config::ITEM_HEIGHT );

    horizontalHeader()->setDefaultSectionSize( config::ITEM_WIDTH );
    verticalHeader()->setDefaultSectionSize( config::ITEM_HEIGHT );
    horizontalHeader()->hide();
    verticalHeader()->hide();

    setItemDelegate(new InventoryDelegate( this ) );
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setSelectionMode(QAbstractItemView::SingleSelection);

    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setFrameShape(QFrame::NoFrame);
}

void ItemInventoryView::mousePressEvent( QMouseEvent *event )
{
    QModelIndex t_model_index = indexAt( event->pos() );
    QAbstractItemModel * t_model = qobject_cast< QAbstractItemModel* >( model() );

    if( event->button() == Qt::LeftButton )
    {
        qDebug() << "left button click row "  << t_model_index.row() << " column " << t_model_index.column();
        if( t_model )
        {
            if( t_model->setData( t_model_index, 1, inventory_role::count_role ) )
            {

            }
        }
    } else if( event->button() == Qt::RightButton )
    {
        qDebug() << "right button click row "  << t_model_index.row() << " column " << t_model_index.column();
        if(t_model)
        {
            if( t_model->setData( t_model_index, -1, inventory_role::count_role ) )
            {
                 QSound::play( config::APPLE_DELETE_SOUND_PATH );
            }
        }
    }

    QTableView::mousePressEvent(event);
}
