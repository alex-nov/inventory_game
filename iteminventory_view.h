#ifndef ITEMINVENTORY_VIEW_H
#define ITEMINVENTORY_VIEW_H

#include <QTableView>
#include <QtMultimedia/QSound>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDrag>

class ItemInventoryView : public QTableView
{
    Q_OBJECT

protected:
    void dragEnterEvent( QDragEnterEvent* event ) Q_DECL_OVERRIDE;
    void dragLeaveEvent( QDragLeaveEvent *event ) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent( QDropEvent* event ) Q_DECL_OVERRIDE;
    void mouseMoveEvent( QMouseEvent* event ) Q_DECL_OVERRIDE;
    void mousePressEvent( QMouseEvent *event ) Q_DECL_OVERRIDE;

public:
    ItemInventoryView( QWidget *parent = nullptr );

private:
    QPoint m_drag_point;
};

#endif // ITEMINVENTORY_VIEW_H
