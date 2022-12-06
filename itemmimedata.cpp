#include "constants.h"
#include "itemmimedata.h"

ItemMimeData::ItemMimeData()
    : QMimeData()
{
}

QString ItemMimeData::MimeType()
{
    return config::MIME_DATA_FORMAT;
}

void ItemMimeData::SetMovedItem(std::shared_ptr<Item> item)
{
    m_moved_item = item;
    m_drag_point = QPoint();
}

std::shared_ptr<Item> ItemMimeData::GetMovedItem() const
{
    return m_moved_item;
}

void ItemMimeData::SetDragPoint(const QPoint &drag_point)
{
    m_moved_item = nullptr;
    m_drag_point = drag_point;
}

QPoint ItemMimeData::GetDragPoint() const
{
    return m_drag_point;
}

QStringList ItemMimeData::formats() const
{
    QStringList formats = QMimeData::formats();
    formats.append( config::MIME_DATA_FORMAT );

    return formats;
}

bool ItemMimeData::hasFormat(const QString &mime_type) const
{
    if( mime_type == config::MIME_DATA_FORMAT && m_moved_item )
    {
        return true;
    }

    return QMimeData::hasFormat( mime_type );
}
