#ifndef DATABASESTORAGE_H
#define DATABASESTORAGE_H

#include "item.h"
#include "constants.h"

#include <QSqlDatabase>
#include <QtGlobal>

#include <memory>

class DatabaseStorage
{
public:
    static DatabaseStorage* Instance();

    void Clear();

    bool MoveItemToInventory( const quint8 row, const quint8 column, std::shared_ptr<Item> item );
    bool DeleteItemFromInventory( const quint8 row, const quint8 column );
    int  GetItemsCountByPosition( const quint8 row, const quint8 column );

    QString GetItemImagePath( const quint8 row, const quint8 column );
    bool CreateNewItem( std::shared_ptr<Item> item );

private:
    DatabaseStorage();
    Q_DISABLE_COPY( DatabaseStorage )
    DatabaseStorage( DatabaseStorage&& );
    DatabaseStorage& operator=( DatabaseStorage&& );

    bool InitTables();

    //TODO: create QVariant RunSqlQuery( QString );

    bool m_database_connected;
    QSqlDatabase m_database;
};

#endif // DATABASESTORAGE_H
