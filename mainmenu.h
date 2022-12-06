#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);

signals:
    void quit_action();
    void start_action();

protected:
    QPushButton * push_button_start;
    QPushButton * push_button_exit;

};

#endif // MAINMENU_H
