#ifndef ITEMDRAGWIDGET_H
#define ITEMDRAGWIDGET_H

#include <QLabel>

class ItemDragWidget : public QLabel
{
    Q_OBJECT
public:
    ItemDragWidget( QWidget *parent = Q_NULLPTR );

protected:
    /* Переопределение обработчиков действия мыши для переноса */
    void mousePressEvent( QMouseEvent* event ) Q_DECL_OVERRIDE;
    void mouseMoveEvent( QMouseEvent* event ) Q_DECL_OVERRIDE;

private:
    QPoint m_drag_point;
};

#endif // ITEMDRAGWIDGET_H
