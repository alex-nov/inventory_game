#include "item.h"

Item::Item( const quint32 id, const item_type type,  const QString& image )
    : m_item_id( id )
    , m_type( type )
    , m_pixmap_path( image )
{
}
