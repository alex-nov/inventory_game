#include "mainwindow.h"
#include "mainmenu.h"
#include "iteminventory_view.h"
#include "iteminventory_model.h"
#include "constants.h"

#include <QApplication>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Создаем элементы интерфейса
    auto inventory_view = new ItemInventoryView();
    auto inventory_model = new ItemInventoryModel;
    inventory_view->setModel( inventory_model );
    auto item_label = new QLabel();
    auto item_pixmap = new QPixmap();
    item_pixmap->load( config::APPLE_IMAGE_PATH );
    item_label->setPixmap( *item_pixmap );

    auto main_menu_button = new QPushButton( "Главное меню" );

    auto main_menu = new MainMenu();

    // Размещаем элементы на центарльном виджете
    auto lay1 = new QVBoxLayout();
    lay1->addStretch(1);
    lay1->addWidget( item_label, 0, Qt::AlignCenter );
    lay1->addStretch(2);
    lay1->addWidget( main_menu_button, 1, Qt::AlignCenter );

    auto lay2 = new QHBoxLayout();
    lay2->addWidget( inventory_view );
    lay1->addStretch(1);
    lay2->addItem( lay1 );

    auto lay3 = new QVBoxLayout();
    lay3->addWidget( main_menu );
    lay3->addItem( lay2 );

    QWidget* central_widget = new QWidget();
    central_widget->setLayout( lay3 );

    // Настройка главного окна
    setCentralWidget( central_widget );
    setWindowTitle(tr("InventoryGame"));

    connect( main_menu, SIGNAL( quit_action() ), SLOT( quit_application() ) );
}

void MainWindow::quit_application()
{
    QApplication::quit();
}

MainWindow::~MainWindow()
{
}

