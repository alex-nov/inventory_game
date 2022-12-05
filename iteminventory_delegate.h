#ifndef ITEMINVENTORY_DELEGATE_H
#define ITEMINVENTORY_DELEGATE_H

#include <QStyledItemDelegate>

class InventoryDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    InventoryDelegate( QWidget *parent = Q_NULLPTR );

    virtual void paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // ITEMINVENTORY_DELEGATE_H
