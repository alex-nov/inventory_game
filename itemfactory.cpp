#include "itemfactory.h"
#include "databasestorage.h"

ItemFactory::ItemFactory()
    : m_next_item_id( 0 )
{
}


std::shared_ptr<Item> ItemFactory::CreateItem( item_type type )
{
    QString image_path;
    switch( type )
    {
        case item_type::apple:
            image_path = item::APPLE_IMAGE_PATH;
            break;
    }

    // Создаем новый объект и сразу сохрянем его в БД
    auto item = std::make_shared< Item >( m_next_item_id++, type, image_path );
    DatabaseStorage::Instance()->CreateNewItem( item );

    return item;
}

ItemFactory* ItemFactory::Instance()
{
    static ItemFactory m_instance;
    return &m_instance;
}
