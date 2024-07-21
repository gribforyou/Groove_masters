#include "song_info.h"

Song_Info::Song_Info()
{

}

Song_Info::Song_Info(QString id, QString title, QString author)
{
    this->id = id;
    this->title = title;
    this->author = author;
}

void Song_Info::setId(QString id)
{
    this->id = id;
}

QString Song_Info::getId() const
{
    return id;
}

void Song_Info::setTitle(QString title)
{
    this->title = title;
}

QString Song_Info::getTitle() const
{
    return title;
}

void Song_Info::setAuthor(QString author)
{
    this->author = author;
}

QString Song_Info::getAuthor() const
{
    return author;
}
