#ifndef ITEMINVENTORY_VIEW_H
#define ITEMINVENTORY_VIEW_H

#include "constants.h"

#include <QTableView>
#include <QtMultimedia/QSound>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDrag>

class ItemInventoryView : public QTableView
{
    Q_OBJECT

protected:
    /* Переопределение обработчиков действия мыши для drag & drop */
    void dragEnterEvent( QDragEnterEvent* event ) Q_DECL_OVERRIDE;
    void dragLeaveEvent( QDragLeaveEvent *event ) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent( QDropEvent* event ) Q_DECL_OVERRIDE;
    void mouseMoveEvent( QMouseEvent* event ) Q_DECL_OVERRIDE;
    void mousePressEvent( QMouseEvent *event ) Q_DECL_OVERRIDE;

public:
    ItemInventoryView( const quint32 rows = config::INVENTORY_ROWS_COUNT,
                       const quint32 columns = config::INVENTORY_COLUMNS_COUNT,
                       QWidget *parent = nullptr );

private:
    quint32 m_rows;
    quint32 m_columns;
    QPoint m_drag_point;
    QModelIndex m_current_drag_index;
};

#endif // ITEMINVENTORY_VIEW_H
