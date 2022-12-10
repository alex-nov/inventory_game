#ifndef DATABASESTORAGE_H
#define DATABASESTORAGE_H

#include "item.h"
#include "constants.h"

#include <QSqlDatabase>
#include <QModelIndex>
#include <QtGlobal>

#include <memory>

class DatabaseStorage
{
public:
    /** Получение экземпляра хранилища */
    static DatabaseStorage* Instance();

    /** Очистка таблиц базы данных */
    void Clear();

    /** Добавление элемента из внешней фабрики в инвентарь */
    bool MoveItemToInventory( const QModelIndex& index, std::shared_ptr<Item> item );
    /** Удаление одного элемента из инвентаря */
    bool DeleteItemFromInventory( const QModelIndex& index );
    /** Перенос всех элементов из одной ячейки инвентаря в другую */
    bool MoveItemsIntoInventory( const QModelIndex& index_from, const QModelIndex& index_to );

    /** Получение кол-ва элементов в ячейке инвентаря */
    int  GetItemsCountByPosition( const QModelIndex& index );
    /** Получение изображения элемента в ячейке инвентаря */
    QString GetItemImagePath( const QModelIndex& index );
    item::item_type GetItemType( const QModelIndex& index );

    /** Сохранения нового предмета в базе при создании */
    bool CreateNewItem( std::shared_ptr<Item> item );

private:
    DatabaseStorage();
    Q_DISABLE_COPY( DatabaseStorage )
    DatabaseStorage( DatabaseStorage&& );
    DatabaseStorage& operator=( DatabaseStorage&& );

    /** Создание таблиц БД */
    bool InitTables();

    bool m_database_connected;
    QSqlDatabase m_database;
};

#endif // DATABASESTORAGE_H
