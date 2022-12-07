#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QtGlobal>
#include <QString>
#include <QPen>
#include <QBrush>

namespace config
{

    const quint8  INVENTORY_ROWS_COUNT = 3;
    const quint8  INVENTORY_COLUMNS_COUNT = 3;

    const QString APPLE_DELETE_SOUND_PATH = ":/res/delete_item.wav";

    const QString MIME_DATA_FORMAT = "application/item";
}

namespace item
{
    const QString APPLE_IMAGE_PATH = ":/res/apple.png";

    namespace draw
    {
        const quint16 APPLE_HEIGHT = 150;
        const quint16 APPLE_WIDTH  = 150;
        const QPen SELECTION_PEN = QPen( Qt::blue, 1, Qt::SolidLine );
        const QBrush SELECTION_BRUSH = QBrush( QColor( 0, 0, 255, 125 ) );
    }
}

namespace inventory_role
{
    // Для setData(...)
    const int add_apple  = Qt::UserRole + 1;
    const int add_many_items = add_apple + 1;
    const int delete_item = add_many_items + 1;
    // Для data(...)
    const int count_role = delete_item + 1;
}

enum class item_type
{
    apple = 0
};

#endif // CONSTANTS_H
