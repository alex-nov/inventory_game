#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "itemdragwidget.h"
#include "iteminventory_view.h"
#include "mainmenu.h"

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void quit_application();
    void start_game();
    void end_game();

private:
    QPushButton* m_main_menu_button;
    ItemDragWidget* m_item_factory;
    ItemInventoryView* m_inventory;
    MainMenu* m_main_menu;
};
#endif // MAINWINDOW_H
