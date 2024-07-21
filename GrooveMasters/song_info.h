#ifndef SONG_INFO_H
#define SONG_INFO_H

#include <QString>

class Song_Info
{
public:Song_Info();
    Song_Info(QString, QString, QString);
    void setId(QString);
    QString getId() const;
    void setTitle(QString);
    QString getTitle() const;
    void setAuthor(QString);
    QString getAuthor() const;

private:
    QString id, title, author;
};

#endif // SONG_INFO_H
