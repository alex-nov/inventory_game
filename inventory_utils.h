#ifndef INVENTORY_UTILS_H
#define INVENTORY_UTILS_H

#include "constants.h"
#include "item.h"

#include <memory>

namespace utils
{

/** Модификация изображения предмета для drag & drop */
QPixmap DrawSelectedItemForDrag( const QRect& area,
                                 const item::item_type type,
                                 const int item_count );

QHash< QString, QVariant > ConvertItemToHashTable( const std::shared_ptr< Item > item  );
std::shared_ptr< Item > ConvertItemHashToItem( const QHash< QString, QVariant > item_hash );

}


#endif // INVENTORY_UTILS_H
