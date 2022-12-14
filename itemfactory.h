#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "item.h"
#include "constants.h"

#include <memory>

class ItemFactory
{
public:
    /** Создания нового предмета с уникальным id */
    std::shared_ptr< Item > CreateItem( item::item_type m_type );

    /** Получение экземпляра фабрики */
    static ItemFactory* Instance();

private:
    ItemFactory();
    Q_DISABLE_COPY(ItemFactory)
    ItemFactory(ItemFactory&&);
    ItemFactory& operator=(ItemFactory&&);

    quint32 m_next_item_id;
};

#endif // ITEMFACTORY_H
