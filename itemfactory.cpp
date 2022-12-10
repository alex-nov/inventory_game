#include "itemfactory.h"
#include "databasestorage.h"
#include "inventory_utils.h"

ItemFactory::ItemFactory()
    : m_next_item_id( 0 )
{
}


std::shared_ptr<Item> ItemFactory::CreateItem( item::item_type type )
{
    // Создаем новый объект и сразу сохрянем его в БД
    auto item = std::make_shared< Item >( m_next_item_id++,
                                          type,
                                          utils::GetItemPathByItemType( type ) );
    DatabaseStorage::Instance()->CreateNewItem( item );

    return item;
}

ItemFactory* ItemFactory::Instance()
{
    static ItemFactory m_instance;
    return &m_instance;
}
