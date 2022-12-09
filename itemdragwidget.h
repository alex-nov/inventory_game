#ifndef ITEMDRAGWIDGET_H
#define ITEMDRAGWIDGET_H

#include "constants.h"

#include <QLabel>

class ItemDragWidget : public QLabel
{
    Q_OBJECT
public:
    ItemDragWidget( const item::item_type type, QWidget *parent = Q_NULLPTR );

protected:
    /* Переопределение обработчиков действия мыши для переноса */
    void mousePressEvent( QMouseEvent* event ) Q_DECL_OVERRIDE;
    void mouseMoveEvent( QMouseEvent* event ) Q_DECL_OVERRIDE;

private:
    item::item_type m_factory_type;
    QPoint m_drag_point;
};

#endif // ITEMDRAGWIDGET_H
