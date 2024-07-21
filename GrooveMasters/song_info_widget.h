#ifndef SONG_INFO_WIDGET_H
#define SONG_INFO_WIDGET_H

#include "scores_widget.h"
#include "song_info.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QListWidget>
#include <QListView>
#include <QSizePolicy>

class Song_Info_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Song_Info_Widget(QWidget *parent = nullptr);
    void loadSongInfo(Song_Info);
private:
    Scores_Widget *scores;
};

#endif // SONG_INFO_WIDGET_H
