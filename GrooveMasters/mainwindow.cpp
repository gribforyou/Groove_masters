#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setObjectName("mainwindow");
    this->setWindowTitle("Groove Master");
    this->setFixedSize(1200, 750);

    music_sound_level = 5;
    fx_sound_level = 5;

    start_widget = new Start_Widget;
    start_widget->setObjectName("startWidget");
    setStyleSheet("QWidget#mainwindow { background-image: url(./bg2.png); } QWidget { font-size: 16px; } QLabel#gameTitle { font-size: 60px; }");
    setCentralWidget(start_widget);

    settings_widget = new Settings_Widget;
    settings_widget->setFixedSize(260, 170);
    settings_widget->setWindowTitle("Settings");
    connect(settings_widget, SIGNAL(level_changed(int ,int )), this, SLOT(changeSoundLevel(int ,int )));

    levelWidget = new Level_Widget();

    menuWidget = new Menu_Widget();
    menuWidget->setParent(this);
    menuWidget->setFixedSize(260, 170);
    menuWidget->move(width()/2-130, height()/2-85);
    menuWidget->close();
    connect(menuWidget, SIGNAL(back_signal()), this, SLOT(backSlot()));
    connect(menuWidget, SIGNAL(settings_signal()), this, SLOT(settingsSlot()));
    connect(menuWidget, SIGNAL(exit_signal()), this, SLOT(exitSlot()));

    songSelectMenu = new Song_Select_Menu();
    songSelectMenu->resize(size());
    connect(songSelectMenu, &Song_Select_Menu::levelSelected, this, &MainWindow::showGameplayWidget);
    connect(songSelectMenu->getSongListWidget(), SIGNAL(settingsSignal()), this, SLOT(settingsSlot()));
    connect(songSelectMenu->getSongListWidget(), SIGNAL(exitSignal()), this, SLOT(exitSlot()));
    connect(songSelectMenu->getDifficultListWidget(), SIGNAL(difficultSettingsSignal()), this, SLOT(settingsSlot()));
    connect(songSelectMenu->getDifficultListWidget(), SIGNAL(difficultExitSignal()), this, SLOT(exitSlot()));
    connect(songSelectMenu->getSongListWidget(), SIGNAL(menuSignal()), this, SLOT(menuSlot()));

    timer = new QTimer();
    timer->start(200);
    connect(timer, &QTimer::timeout, this, [=]{repaint();});

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(dynamic_cast<Start_Widget*>(this->centralWidget())){
        setCentralWidget(songSelectMenu);
        songSelectMenu->changeSelectedSong(0);
    };

    if (event->key() == Qt::Key_Escape) {
        if (dynamic_cast<Level_Widget*>(this->centralWidget())) {
            levelWidget = dynamic_cast<Level_Widget*>(takeCentralWidget());
            setCentralWidget(songSelectMenu);
            songSelectMenu->changeSelectedSong(songSelectMenu->getSelectedSong());
            if(this->settings_widget->isVisible()) settings_widget->hide();
        }
        else{
            if(dynamic_cast<Song_Select_Menu*>(centralWidget())){
                menuSlot();
            }
        }

    }

    if(dynamic_cast<Level_Widget*>(this->centralWidget())){
        if (settings_widget->isVisible() == false){
            levelWidget->keyPressEvent(event);
        }
    }
    if (event->key() == Qt::Key_S && event->isAutoRepeat() == false) {
        if (dynamic_cast<Level_Widget*>(this->centralWidget()))
            //levelWidget->keyPressEvent(event);
        settingsSlot();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_D || event->key() == Qt::Key_F || event->key() == Qt::Key_J || event->key() == Qt::Key_K) && dynamic_cast<Level_Widget*>(this->centralWidget())){
        levelWidget->keyReleaseEvent(event);
    };
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::backSlot()
{
    menuWidget->hide();
    centralWidget()->setEnabled(true);
}

void MainWindow::settingsSlot()
{
    settings_widget->set_sliders(music_sound_level, fx_sound_level);
    settings_widget->exec();
}

void MainWindow::exitSlot()
{
    QCoreApplication::quit();
}

void MainWindow::menuSlot()
{
    menuWidget->show();
}

void MainWindow::showGameplayWidget(Song_Info songInfo, QString difficulty)
{
    if (levelWidget->loadLevel(songInfo, difficulty)) {
        if (dynamic_cast<Song_Select_Menu*>(this->centralWidget()))
            songSelectMenu = dynamic_cast<Song_Select_Menu*>(takeCentralWidget());
        setCentralWidget(levelWidget);
    }
    else
        QMessageBox::information(this, "Error", "Level file not found");
}

void MainWindow::changeSoundLevel(int m, int f)
{
    this->music_sound_level = m;
    this->fx_sound_level = f;
    levelWidget->setMusicVolume(m);
    levelWidget->setFxVolume(f);
    songSelectMenu->setMusicVolume(m);
}

void MainWindow::settingsCancel()
{
    settings_widget->hide();
}


