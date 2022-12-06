#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QtGlobal>
#include <QString>

namespace config
{
    const quint16 ITEM_HEIGHT = 150;
    const quint16 ITEM_WIDTH  = 150;
    const quint8  INVENTORY_ROWS_COUNT = 3;
    const quint8  INVENTORY_COLUMNS_COUNT = 3;

    const QString APPLE_IMAGE_PATH = ":/res/apple.png";
    const QString APPLE_DELETE_SOUND_PATH = ":/res/delete_item.wav";
}

namespace inventory_role
{
    const int type_role  = Qt::UserRole    + 1;
    const int count_role = type_role + 1;
}

enum class item_type
{
    apple = 0
};

#endif // CONSTANTS_H
