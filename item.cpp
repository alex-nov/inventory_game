#include "item.h"

Item::Item( const quint32 id, const item::item_type type,  const QString& image )
    : m_item_id( id )
    , m_type( type )
    , m_image_path( image )
{
}

quint32 Item::GetItemId() const
{
    return m_item_id;
}

item::item_type Item::GetItemType() const
{
    return m_type;
}

QString Item::GetImagePath() const
{
    return m_image_path;
}
