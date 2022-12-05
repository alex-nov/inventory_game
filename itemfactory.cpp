#include "itemfactory.h"

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
            image_path = config::APPLE_IMAGE_PATH;
            break;
    }

    return std::make_shared< Item >( m_next_item_id++, type, image_path );
}

ItemFactory* ItemFactory::Instance()
{
    static ItemFactory m_instance;
    return &m_instance;
}
