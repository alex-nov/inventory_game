#include "databasestorage.h"
#include "constants.h"

#include <QFileInfo>
#include <QString>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

#include <iostream>

DatabaseStorage* DatabaseStorage::Instance()
{
    static DatabaseStorage instance;
    return &instance;
}

DatabaseStorage::DatabaseStorage()
{
    m_database_connected = false;
    QString db_name = "database.db";

    m_database = QSqlDatabase::addDatabase( QString( "QSQLITE" ), db_name );
    m_database.setConnectOptions( "QSQLITE_OPEN_URI" );
    m_database.setDatabaseName( db_name );

    if ( m_database.open() )
    {
        qDebug() << "DB connected: " << db_name;
        m_database_connected = true;

       if( InitTables() )
       {
            qDebug() << db_name << ": tables inventory and items created";
            Clear();
       }
    }
    else
    {
       qDebug() << "Не удалось подключиться к базе данных данных: " << db_name;
    }
}



bool DatabaseStorage::InitTables()
{
    if( !m_database_connected )
    {
        return false;
    }

    bool tables_created = false;
    {
        QSqlQuery sql_query( m_database );
        sql_query.prepare( QString( "CREATE TABLE IF NOT EXISTS \"inventory\" ( "
                                    "\"item_id\" INTEGER NOT NULL UNIQUE, "
                                    "\"row\" INTEGER NOT NULL, "
                                    "\"column\" INTEGER NOT NULL, "
                                    "PRIMARY KEY(\"item_id\") );" ) );

        tables_created = sql_query.exec();
    }

    {
        QSqlQuery sql_query( m_database );
        sql_query.prepare( QString( "CREATE TABLE IF NOT EXISTS \"items\" ( "
                                    "\"id\" INTEGER NOT NULL UNIQUE, "
                                    "\"type\" INTEGER NOT NULL, "
                                    "\"image_path\" TEXT, "
                                    "PRIMARY KEY(\"id\") );" ) );

        tables_created &= sql_query.exec();
    }

    return tables_created;
}


void DatabaseStorage::Clear()
{
    if( !m_database_connected )
    {
        return;
    }

    {
        QSqlQuery sql_query( m_database );
        sql_query.prepare( QString( "DELETE from inventory;" ) );
        if( !sql_query.exec() )
        {
            // TODO sql log error msg
            return;
        }
    }

    {
        QSqlQuery sql_query( m_database );
        sql_query.prepare( QString( "DELETE from items;" ) );
        if( !sql_query.exec() )
        {
            // TODO sql log error msg
            return;
        }
    }
}

bool DatabaseStorage::MoveItemToInventory( const QModelIndex& index, std::shared_ptr<Item> item )
{
    if( !m_database_connected )
    {
        return false;
    }

    QSqlQuery sql_query( m_database );
    sql_query.prepare( QString( "INSERT INTO inventory (row, column, item_id)"
                                "VALUES (:row, :column, :item_id);" ) );
    sql_query.bindValue( 0, index.row() );
    sql_query.bindValue( 1, index.column() );
    sql_query.bindValue( 2, item->GetItemId() );

    return sql_query.exec();
}

bool DatabaseStorage::DeleteItemFromInventory( const QModelIndex& index )
{
    if( !m_database_connected )
    {
        return false;
    }

    bool successed_delete_item = false;
    if( GetItemsCountByPosition( index ) > 0 )
    {
        // Производим полное удаление предмета из игры:
        // Удаляем предмет из таблицы предметов
        {
            QSqlQuery sql_query( m_database );
            sql_query.prepare( QString( "DELETE FROM items WHERE items.id IN "
                                        "(SELECT inventory.item_id from inventory "
                                        "WHERE inventory.row=:row AND inventory.column=:column "
                                        "ORDER BY inventory.item_id LIMIT 1);" ) );
            sql_query.bindValue( 0, index.row() );
            sql_query.bindValue( 1, index.column() );
            successed_delete_item = sql_query.exec();
        }
        // Удаляем предмет из инвентаря
        {
            QSqlQuery sql_query( m_database );
            sql_query.prepare( QString( "DELETE FROM inventory WHERE item_id IN "
                                        "(SELECT item_id from inventory "
                                        "WHERE row=:row AND column=:column "
                                        "ORDER BY item_id LIMIT 1);" ) );
            sql_query.bindValue( 0, index.row() );
            sql_query.bindValue( 1, index.column() );
            successed_delete_item &= sql_query.exec();
        }
    }

    return successed_delete_item;
}

int DatabaseStorage::GetItemsCountByPosition( const QModelIndex& index )
{
    if( !m_database_connected )
    {
        return 0;
    }

    QSqlQuery sql_query( m_database );
    sql_query.prepare(
                QString( "SELECT COUNT(*) FROM inventory "
                         "WHERE row=:row AND column=:column;" ) );
    sql_query.bindValue( 0, index.row() );
    sql_query.bindValue( 1, index.column() );

    if( sql_query.exec() && sql_query.next() )
    {
        return sql_query.value(0).toInt();
    }

    return 0;
}

QString DatabaseStorage::GetItemImagePath( const QModelIndex& index )
{
    if( !m_database_connected )
    {
        return 0;
    }

    if( GetItemsCountByPosition( index ) > 0 )
    {
        QSqlQuery sql_query( m_database );
        sql_query.prepare(
                    QString( "SELECT items.image_path FROM items LEFT JOIN inventory "
                             "WHERE items.id IN "
                             "(SELECT inventory.item_id FROM inventory "
                             "WHERE row=:row AND column=:column LIMIT 1);" ) );
        sql_query.bindValue( 0, index.row() );
        sql_query.bindValue( 1, index.column() );

        if( sql_query.exec() && sql_query.next() )
        {
            return sql_query.value(0).toString();
        }
    }

    return QString();
}

item::item_type DatabaseStorage::GetItemType( const QModelIndex& index )
{
    if( !m_database_connected )
    {
        return item::item_type::none;
    }

    if( GetItemsCountByPosition( index ) > 0 )
    {
        QSqlQuery sql_query( m_database );
        sql_query.prepare(
                    QString( "SELECT items.type FROM items LEFT JOIN inventory "
                             "WHERE items.id IN "
                             "(SELECT inventory.item_id FROM inventory "
                             "WHERE row=:row AND column=:column LIMIT 1);" ) );
        sql_query.bindValue( 0, index.row() );
        sql_query.bindValue( 1, index.column() );

        if( sql_query.exec() && sql_query.next() )
        {
            return static_cast< item::item_type >( sql_query.value(0).toUInt() );
        }
    }

    return item::item_type::none;
}

bool DatabaseStorage::CreateNewItem( std::shared_ptr<Item> item )
{
    if( !m_database_connected )
    {
        return false;
    }

    QSqlQuery sql_query( m_database );
    sql_query.prepare( QString( "INSERT INTO items (id, type, image_path)"
                                "VALUES (:id, :type, :image_path);" ) );
    sql_query.bindValue( 0, item->GetItemId() );
    sql_query.bindValue( 1, static_cast< int >( item->GetItemType() ) );
    sql_query.bindValue( 2, item->GetImagePath() );

    return sql_query.exec();
}

bool DatabaseStorage::MoveItemsIntoInventory( const QModelIndex& index_from, const QModelIndex& index_to )
{
    if( !m_database_connected )
    {
        return false;
    }

    QSqlQuery sql_query( m_database );
    sql_query.prepare( QString( "UPDATE inventory SET row=:row_to, column=:column_to WHERE "
                                "item_id IN "
                                "(SELECT item_id from inventory WHERE "
                                "row=:row_from AND column=:column_from);" ) );
    sql_query.bindValue( 0, index_to.row() );
    sql_query.bindValue( 1, index_to.column() );
    sql_query.bindValue( 2, index_from.row() );
    sql_query.bindValue( 3, index_from.column() );

    return sql_query.exec();
}

QVariant DatabaseStorage::RunSQLQuery( const QString &query_text )
{
    if( !m_database_connected )
    {
        return false;
    }

    QSqlQuery sql_query;
    bool success = sql_query.exec( query_text );
    if( !sql_query.isActive() )
    {
        qDebug() << "Не удалось выполнить запрос к базе данных: "
                 << m_database.databaseName()
                 << QChar('\n')
                 << "Query: "
                 << sql_query.lastQuery()
                 << QChar('\n')
                 << "Сообщение драйвера базы данных: "
                 << sql_query.lastError();
    }

    if( success && sql_query.next() )
    {
        return sql_query.value( 0 );
    }
    return QVariant();
}
