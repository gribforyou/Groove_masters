#include "song_list_widget.h"

Song_List_Widget::Song_List_Widget(QWidget *parent): QListWidget(parent)
{
    this->setMaximumWidth(400);
    connect(this, &QListWidget::currentRowChanged, this, &Song_List_Widget::emitSelectedSongChanged);
    connect(this, &QListWidget::itemDoubleClicked, this, &Song_List_Widget::emitSongSelected);
}

void Song_List_Widget::showEvent(QShowEvent *event)
{
    setFocus();
}

void Song_List_Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == 16777220) {
        emit songSelected();
        return;
    }
    if(event->key() == Qt::Key_S || event->key() == 1067){
        emit settingsSignal();
        return;
    }
    if(event->key() == Qt::Key_E || event->key()==1059){
        emit exitSignal();
        return;
    }
    if(event->key() == Qt::Key_Escape){
        emit menuSignal();
        return;
    }
    QListWidget::keyPressEvent(event);
}

void Song_List_Widget::emitSelectedSongChanged(int selectedSong)
{
    emit selectedSongChanged(selectedSong);
}

void Song_List_Widget::emitSongSelected()
{
    emit songSelected();
}

void Song_List_Widget::updateSongListWidget(const std::vector <Song_Info> &songInfoVector)
{
    this ->clear();
    for (int i = 0; i < songInfoVector.size(); i++)
        this->addItem(songInfoVector[i].getTitle());
    this->setCurrentRow(0);
}
