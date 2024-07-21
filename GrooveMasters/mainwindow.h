#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "start_widget.h"
#include "settings_widget.h"
#include "song_select_menu.h"
#include "level_widget.h"
#include "menu_widget.h"

#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPalette>
#include <QGraphicsBlurEffect>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Start_Widget* start_widget;
    Settings_Widget* settings_widget;
    Song_Select_Menu *songSelectMenu;
    Level_Widget *levelWidget;
    Menu_Widget *menuWidget;

    int music_sound_level;
    int fx_sound_level;

    QTimer* timer;

public slots:
    void changeSoundLevel(int m, int f);
    void settingsCancel();
    void backSlot();
    void settingsSlot();
    void exitSlot();
    void menuSlot();
    void showGameplayWidget(Song_Info, QString);
};
#endif // MAINWINDOW_H
