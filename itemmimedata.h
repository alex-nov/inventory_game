#ifndef ITEMMIMEDATA_H
#define ITEMMIMEDATA_H

#include "item.h"

#include <QMimeData>
#include <QPoint>

#include <memory>

class ItemMimeData : public QMimeData
{

public:
    ItemMimeData();
    virtual ~ItemMimeData(){}

    static QString MimeType();

    /** Данные нового элемента из фабрики */
    void SetMovedItem( std::shared_ptr< Item > item );
    /** Получение перенесенного предмета из фабрики */
    std::shared_ptr< Item > GetMovedItem() const;

    /** Данные для переноса между ячейками инвентаря*/
    void SetDragPoint( const QPoint& drag_point );
    /** Получение данных ячейки инвентаря, откуда прозводится перенос*/
    QPoint GetDragPoint() const;

    /* Переопределение методов для корретного опознания MimeData */
    virtual QStringList	formats() const Q_DECL_OVERRIDE;
    virtual bool hasFormat(const QString & mimeType) const Q_DECL_OVERRIDE;

private:
    std::shared_ptr< Item > m_moved_item;
    QPoint m_drag_point;
};

#endif // ITEMMIMEDATA_H
