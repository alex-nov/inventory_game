#ifndef ITEMINVENTORY_VIEW_H
#define ITEMINVENTORY_VIEW_H

#include <QTableView>
#include <QtMultimedia/QSound>

class ItemInventoryView : public QTableView
{
    Q_OBJECT
public:
    ItemInventoryView( QWidget *parent = nullptr );

    virtual void mousePressEvent( QMouseEvent *event ) Q_DECL_OVERRIDE;
};

#endif // ITEMINVENTORY_VIEW_H
