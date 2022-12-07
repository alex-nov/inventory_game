#include "mainmenu.h"

#include <QBoxLayout>
#include <QPalette>

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    push_button_start( new QPushButton( QString( "Начать" ) )),
    push_button_exit( new QPushButton( QString( "Выход" ) ))
{
    // Размещаем элементы управления
    auto lay1 = new QHBoxLayout();
    lay1->addStretch(1);
    lay1->addWidget( push_button_start, 0, Qt::AlignCenter );
    lay1->addStretch(1);
    lay1->addWidget( push_button_exit, 0, Qt::AlignCenter );
    lay1->addStretch(1);
    lay1->setGeometry( QRect( 0, 0, 768, 100) );
    setLayout( lay1 );

    // Рисуем фон меню
    QPalette pal;
    pal.setColor( this->backgroundRole(), Qt::yellow );
    setPalette( pal );
    setAutoFillBackground (true );

    // Подключаем сигналы элементов управления
    connect( push_button_start, SIGNAL( clicked() ), SIGNAL( start_action() ) );
    connect( push_button_exit, SIGNAL( clicked() ), SIGNAL( quit_action() ) );
}
