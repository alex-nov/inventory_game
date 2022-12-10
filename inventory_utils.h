#ifndef INVENTORY_UTILS_H
#define INVENTORY_UTILS_H

#include "constants.h"
#include "item.h"

#include <memory>

namespace utils
{
/** Получение пути до изображения по типу файла */
QString GetItemPathByItemType( const item::item_type type );

/** Модификация изображения предмета для drag & drop */
QPixmap DrawItemForWidget( const QRect& area,
                           const item::item_type type,
                           const int item_count,
                           const bool is_selected = false );

/** Модификация изображения предмета для drag & drop */
QPixmap DrawItemForWidget( const QRect& area,
                           const QString& pixmap_path,
                           const int item_count,
                           const bool is_selected = false );

/** Конвертер для передачи Item в модель инвентаря */
QHash< QString, QVariant > ConvertItemToHashTable( const std::shared_ptr< Item > item  );
/** Обратный конвертер для получения Item из модели инвентаря */
std::shared_ptr< Item > ConvertItemHashToItem( const QHash< QString, QVariant > item_hash );

}


#endif // INVENTORY_UTILS_H
