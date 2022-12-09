#ifndef ITEM_H
#define ITEM_H

#include "constants.h"

#include <QtGlobal>
#include <QString>

class Item
{
public:
    explicit Item( const quint32 id, const item::item_type type,  const QString& image );

    /** Получение уникального id предмета */
    quint32     GetItemId() const;
    /** Получение типа предмета */
    item::item_type   GetItemType() const;
    /** Получение адреса изображения предмета */
    QString     GetImagePath() const;

private:
    quint32 m_item_id;
    item::item_type m_type;
    QString m_image_path;
};

#endif // ITEM_H
