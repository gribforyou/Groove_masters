#ifndef MENU_WIDGET_H
#define MENU_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class Menu_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Menu_Widget(QWidget *parent = nullptr);
private slots:
    void back_slot();
    void settings_slot();
    void exit_slot();
signals:
    void back_signal();
    void settings_signal();
    void exit_signal();
};

#endif // MENU_WIDGET_H