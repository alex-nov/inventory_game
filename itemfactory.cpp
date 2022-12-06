#include "itemfactory.h"
#include "databasestorage.h"

ItemFactory::ItemFactory()
    : m_next_item_id( 0 )
    , m_last_created_item_id( 0 )
{
}


std::shared_ptr<Item> ItemFactory::CreateItem( item_type type )
{
    QString image_path;
    switch( type )
    {
        case item_type::apple:
            image_path = config::APPLE_IMAGE_PATH;
            break;
    }

    m_last_created_item_id = m_next_item_id;
    auto item = std::make_shared< Item >( m_next_item_id++, type, image_path );
    DatabaseStorage::Instance()->CreateNewItem( item );

    return item;
}

ItemFactory* ItemFactory::Instance()
{
    static ItemFactory m_instance;
    return &m_instance;
}
