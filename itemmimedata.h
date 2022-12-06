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

    // данные для нового элемента из фабрики
    void SetMovedItem( std::shared_ptr< Item > item );
    std::shared_ptr< Item > GetMovedItem() const;

    // данные для переноса между ячейками таблицы
    void SetDragPoint( const QPoint& drag_point );
    QPoint GetDragPoint() const;

    virtual QStringList	formats() const Q_DECL_OVERRIDE;
    virtual bool hasFormat(const QString & mimeType) const Q_DECL_OVERRIDE;

private:
    std::shared_ptr< Item > m_moved_item;
    QPoint m_drag_point;
};

#endif // ITEMMIMEDATA_H
