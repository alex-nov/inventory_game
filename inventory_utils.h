#ifndef INVENTORY_UTILS_H
#define INVENTORY_UTILS_H

#include "constants.h"

namespace utils
{

/** Модификация изображения предмета для drag & drop */
QPixmap DrawSelectedItemForDrag( const QRect& area,
                                 const item_type type,
                                 const int item_count );

}


#endif // INVENTORY_UTILS_H
