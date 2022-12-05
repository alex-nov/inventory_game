#include "mainwindow.h"
#include "mainmenu.h"

#include <QApplication>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QTableWidget>
#include <QHeaderView>
#include <QPixmap>

const int c_item_height = 150;
const int c_item_width  = 150;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Создаем элементы интерфейса
    auto inventory = new QTableWidget( 3, 3 );
    inventory->horizontalHeader()->setDefaultSectionSize( c_item_width );
    inventory->verticalHeader()->setDefaultSectionSize( c_item_height );
    inventory->horizontalHeader()->hide();
    inventory->verticalHeader()->hide();
    inventory->setFixedSize( 3 * c_item_width, 3 * c_item_height );
    inventory->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
    inventory->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    inventory->setFrameShape(QFrame::NoFrame);

    auto item_factory = new QLabel();
    auto item_image = new QPixmap();
    item_image->load(":/res/apple.png");
    item_factory->setPixmap( *item_image );

    auto main_menu_button = new QPushButton( "Главное меню" );

    auto main_menu = new MainMenu();

    // Размещаем элементы на центарльном виджете
    auto lay1 = new QVBoxLayout();
    lay1->addStretch(1);
    lay1->addWidget( item_factory, 0, Qt::AlignCenter );
    lay1->addStretch(2);
    lay1->addWidget( main_menu_button, 1, Qt::AlignCenter );

    auto lay2 = new QHBoxLayout();
    lay2->addWidget( inventory );
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

