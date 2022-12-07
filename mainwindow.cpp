#include "mainwindow.h"
#include "mainmenu.h"
#include "iteminventory_view.h"
#include "iteminventory_model.h"
#include "itemdragwidget.h"
#include "databasestorage.h"
#include "constants.h"

#include <QApplication>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QPixmap>
#include <QTimer>

#include <QDebug>


MainWindow::MainWindow( QWidget *parent )
    : QMainWindow(parent)
{
    // Создаем элементы интерфейса
    // Model-view структура инвентаря
    m_inventory = new ItemInventoryView();
    auto inventory_model = new ItemInventoryModel();
    m_inventory->setModel( inventory_model );

    // Объект порождающий новые предметы
    m_item_factory = new ItemDragWidget();

    // Элементы управления
    m_main_menu_button = new QPushButton( "Главное меню" );
    m_main_menu_button->setEnabled( false );
    m_main_menu = new MainMenu();

    // Размещаем элементы на центральном виджете
    auto lay1 = new QVBoxLayout();
    lay1->addStretch(1);
    lay1->addWidget( m_item_factory, 0, Qt::AlignCenter );
    lay1->addStretch(2);
    lay1->addWidget( m_main_menu_button, 1, Qt::AlignCenter );

    auto lay2 = new QHBoxLayout();
    lay2->addWidget( m_inventory );
    lay1->addStretch(1);
    lay2->addItem( lay1 );

    auto lay3 = new QVBoxLayout();
    lay3->addWidget( m_main_menu );
    lay3->addItem( lay2 );

    QWidget* central_widget = new QWidget();
    central_widget->setLayout( lay3 );

    // Настройка главного окна
    setCentralWidget( central_widget );
    setWindowTitle(tr("InventoryGame"));

    // Подключаем слоты к сигналам
    connect( m_main_menu, SIGNAL( quit_action() ), SLOT( quit_application() ) );
    connect( m_main_menu, SIGNAL( start_action() ), SLOT( start_game() ) );
    connect( m_main_menu_button, SIGNAL( clicked() ), SLOT( end_game() ) );
}

void MainWindow::quit_application()
{
    QApplication::quit();
}

void MainWindow::start_game()
{
    // Очистка БД и активация игровых виджетов
    DatabaseStorage::Instance()->Clear();
    m_main_menu_button->setEnabled( true );
    m_inventory->setEnabled( true );
    m_inventory->update();
    m_item_factory->setEnabled( true );

    // Анимация скрытия меню
    m_main_menu_h = 39;
    m_main_menu_step = -2;
    startTimer( 15 );
}

void MainWindow::end_game()
{
    // Отключаем игровые виджеты
    m_main_menu_button->setEnabled( false );
    m_inventory->setEnabled( false );
    m_item_factory->setEnabled( false );

    // Анимация появления меню
    m_main_menu_h = 0;
    m_main_menu_step = 2;
    m_main_menu->resize( m_main_menu->width(), m_main_menu_h );
    startTimer( 15 );
}

void MainWindow::timerEvent( QTimerEvent *event )
{
    // Логика анимации главного муню
    m_main_menu_h += m_main_menu_step;
    m_main_menu->resize ( m_main_menu->width(), m_main_menu_h );
    if( m_main_menu->height() >= 40 || m_main_menu->height() <= 0 )
    {
        killTimer( event->timerId( ));
    }
}

MainWindow::~MainWindow()
{
}

