#include "iteminventory_delegate.h"
#include "constants.h"

#include <QPainter>

InventoryDelegate::InventoryDelegate( QWidget *parent )
    : QStyledItemDelegate( parent )
{
}

void InventoryDelegate::paint( QPainter *painter
            , const QStyleOptionViewItem &option
            , const QModelIndex &index ) const
{
    if( option.state & QStyle::State_Selected )
    {
        painter->fillRect( option.rect, QBrush( Qt::white ) );
    }

    if( index.data( inventory_role::count_role ).canConvert(QMetaType::Int) &&
        index.data( Qt::DecorationRole ).canConvert( QMetaType::QString ) )
    {

        int item_count = index.data( inventory_role::count_role).toInt();

        if( item_count > 0)
        {
            //Отрисовка иконки
            QWidget * t_widget_parent = static_cast< QWidget * >( parent() );
            if( t_widget_parent && t_widget_parent->isEnabled() )
            {
                painter->drawPixmap( option.rect, QPixmap( index.data( Qt::DecorationRole ).toString() ) );
            }
            else
            {
                painter->drawPixmap(
                            option.rect,
                            QIcon( index.data( Qt::DecorationRole ).toString() ).pixmap(
                                option.rect.size(),
                                QIcon::Disabled,
                                QIcon::Off) );
            }

            //Отрисовка количества итемок
            QString string_result = QString("%1").arg( item_count );

            painter->drawText( option.rect, Qt::AlignBottom | Qt::AlignRight, string_result);
        }

    }
}
