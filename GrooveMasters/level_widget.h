#ifndef LEVEL_WIDGET_H
#define LEVEL_WIDGET_H

#include <QWidget>
#include "song_info.h"
#include <vector>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioProbe>

class Level_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Level_Widget(QWidget *parent = 0);
    bool loadLevel(Song_Info, QString);
    void startLevel();
    double getSongTime() const;
    double getSongLength() const;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void setMusicVolume(int);
    void setFxVolume(int);

private:
    int score, combo;
    bool isPaused;
    void pause();
    void resume();
    QTimer timer;
    int interval = 25, secondSize = 300, noteSize = 10, bpm, offset;
    QAudioProbe audioProbe;
    unsigned short *visualizerData;
    int visualizerDataSize = 64;
    double spb;
    QMediaPlayer songPlayer;
    std::vector <QMediaPlayer*> tapSoundPlayers;
    void showEvent(QShowEvent *event);
    std::vector <bool> isActive;
    std::vector <std::vector <std::pair <int, int>>> notesVector;
    void hideEvent(QHideEvent *event);
    void addPointsToScore(int);
    void paintEvent(QPaintEvent*);

private slots:
    void updateNotes();
    void updateVisualizerData(QAudioBuffer);

signals:

public slots:
};

#endif // LEVEL_WIDGET_H
