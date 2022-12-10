#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QtGlobal>
#include <QString>
#include <QPen>
#include <QBrush>

namespace config
{

    const quint8  INVENTORY_ROWS_COUNT = 4;
    const quint8  INVENTORY_COLUMNS_COUNT = 4;

    const QString APPLE_DELETE_SOUND_PATH = ":/res/delete_item.wav";

    const QString MIME_DATA_FORMAT = "application/item";
}

namespace item
{
    const QString APPLE_IMAGE_PATH = ":/res/apple.png";
    const QString ORANGE_IMAGE_PATH = ":/res/orange.png";
    const QString PLUM_IMAGE_PATH = ":/res/plum.png";
    const QString PEAR_IMAGE_PATH = ":/res/pear.png";
    const QString NOLOGO_IMAGE_PATH = ":/res/nologo.png";

    enum class item_type : quint8
    {
        apple = 0,
        orange,
        plum,
        pear,
        none = 99
    };

    namespace draw
    {
        const quint16 ITEM_HEIGHT = 100;
        const quint16 ITEM_WIDTH  = 100;
        const QPen SELECTION_PEN = QPen( Qt::blue, 1, Qt::SolidLine );
        const QBrush SELECTION_BRUSH = QBrush( QColor( 0, 0, 255, 125 ) );
    }
}

namespace inventory_role
{
    // Для setData(...)
    const int add_item  = Qt::UserRole + 1;
    const int add_many_items = add_item + 1;
    const int delete_item = add_many_items + 1;
    // Для data(...)
    const int count_role = delete_item + 1;
}



#endif // CONSTANTS_H
