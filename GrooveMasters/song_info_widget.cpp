#include "song_info_widget.h"

Song_Info_Widget::Song_Info_Widget(QWidget *parent) : QWidget(parent)
{
    scores = new Scores_Widget();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);

    QLabel *label = new QLabel();
    label->setObjectName("songTitle");
    label->setStyleSheet("#songTitle { font-size: 30px; margin-bottom: 0px; padding-bottom: 0px; }");
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    layout->addWidget(label);
    label = new QLabel();
    label->setObjectName("songAuthor");
    label->setStyleSheet("QLabel { font-size: 20px; margin-left: 20px; margin-top: 0px; padding-top: 0px; margin-bottom: 20px; }");
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    layout->addWidget(label);

    label = new QLabel();
    label->setMinimumWidth(700);
    label->setObjectName("cover");
    label->setText("Song cover");

    QPixmap pixmap;
    pixmap.load("covers/test.png");
    label->setMaximumWidth(500);
    layout->addWidget(label);
    label->setPixmap(pixmap.scaled(label->width(), label->height(), Qt::KeepAspectRatio));
    layout->addWidget(scores);

}

void Song_Info_Widget::loadSongInfo(Song_Info songInfo)
{
    findChild<QLabel*>("songTitle")->setText(songInfo.getTitle());
    findChild<QLabel*>("songAuthor")->setText("by " + songInfo.getAuthor());

    QPixmap pixmap;
    pixmap.load("covers/" + songInfo.getId() + ".png");

    QLabel *coverLabel = findChild<QLabel*>("cover");
    coverLabel->setPixmap(pixmap.scaled(coverLabel->width(), coverLabel->height(), Qt::KeepAspectRatio));

    scores->loadSongScores(songInfo.getId());
}


