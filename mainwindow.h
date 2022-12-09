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
    /** Выход из приложения */
    void quit_application();
    /** Начало игры, скрытие меню */
    void start_game();
    /** Возврат к начальному состаянию приложения */
    void end_game();

protected:
    /** Переопределение события таймера для анимации меню */
    virtual void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

private:
    QPushButton* m_main_menu_button;
    QVector< ItemDragWidget* > m_item_factories;
    ItemInventoryView* m_inventory;
    MainMenu* m_main_menu;

    int m_main_menu_h;
    int m_main_menu_step;
};
#endif // MAINWINDOW_H
