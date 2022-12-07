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
    /** Получение экземпляра хранилища */
    static DatabaseStorage* Instance();

    /** Очистка таблиц базы данных */
    void Clear();

    /** Добавление элемента из внешней фабрики в инвентарь */
    bool MoveItemToInventory( const quint8 row, const quint8 column, std::shared_ptr<Item> item );
    /** Удаление одного элемента из инвентаря */
    bool DeleteItemFromInventory( const quint8 row, const quint8 column );
    /** Перенос всех элементов из одной ячейки инвентаря в другую */
    bool MoveItemsIntoInventory( const quint8 row_from, const quint8 column_from,
                                 const quint8 row_to, const quint8 column_to );

    /** Получение кол-ва элементов в ячейке инвентаря */
    int  GetItemsCountByPosition( const quint8 row, const quint8 column );
    /** Получение изображения элемента в ячейке инвентаря */
    QString GetItemImagePath( const quint8 row, const quint8 column );
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
