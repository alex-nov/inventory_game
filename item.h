#ifndef ITEM_H
#define ITEM_H

#include "constants.h"

#include <QtGlobal>
#include <QString>

class Item
{
public:
    explicit Item( const quint32 id, const item_type type,  const QString& image );

    quint32     GetItemId() const;
    item_type   GetItemType() const;
    QString     GetImagePath() const;

private:
    quint32 m_item_id;
    item_type m_type;
    QString m_image_path;
};

#endif // ITEM_H
