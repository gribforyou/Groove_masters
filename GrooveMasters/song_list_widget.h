#ifndef SONG_LIST_WIDGET_H
#define SONG_LIST_WIDGET_H

#include <song_info.h>

#include <QList>
#include <QListWidget>
#include <QHeaderView>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QKeyEvent>

class Song_List_Widget : public QListWidget
{
      Q_OBJECT
public:
    explicit Song_List_Widget(QWidget *parent = 0);
private:
    QList <std::pair <QString, QString>> songList;
    void showEvent(QShowEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void selectedSongChanged(int);
    void songSelected();
    void settingsSignal();
    void exitSignal();
    void menuSignal();

private slots:
    void emitSelectedSongChanged(int);
    void emitSongSelected();

public slots:
    void updateSongListWidget(const std::vector <Song_Info>&);
};

#endif // SONG_LIST_WIDGET_H
