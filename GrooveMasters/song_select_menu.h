#ifndef SONG_SELECT_MENU_H
#define SONG_SELECT_MENU_H

#include "song_list_widget.h"
#include "song_info_widget.h"
#include "difficult_list_widget.h"
#include "song_info.h"

#include <QPaintEvent>
#include <QPainter>
#include <QLinearGradient>
#include <QWidget>
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <fstream>
#include <QStringList>
#include <string>
#include <QLabel>
#include <QPushButton>


class Song_Select_Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Song_Select_Menu(QWidget *parent = nullptr);
    void loadSongInfoVector();
    Song_List_Widget *getSongListWidget();
    Song_Info_Widget *getSongInfoWidget();
    Difficult_List_Widget *getDifficultListWidget();
    int getSelectedSong() const;
    void setSongInfoWidget(Song_Info_Widget *newSongInfoWidget);
    void setMusicVolume(int);

private:
    QMediaPlayer previewPlayer;
    std::vector <Song_Info> songInfoVector;
    int selectedSong = 0;
    Song_List_Widget *songListWidget;
    Song_Info_Widget *songInfoWidget;
    Difficult_List_Widget *difficultListWidget;
    void hideEvent(QHideEvent *event);
    void paintEvent(QPaintEvent *event) override;
signals:
    void levelSelected(Song_Info, QString);

public slots:
    void backToSongs();
    void changeSelectedSong(int);
    void emitLevelSelected(QString);
    void selectDifficulty();
};

#endif // SONG_SELECT_MENU_H
