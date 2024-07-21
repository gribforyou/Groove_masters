#ifndef SCORES_WIDGET_H
#define SCORES_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <fstream>
#include <string>
#include <QDebug>

class Scores_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Scores_Widget(QWidget *parent = nullptr);
    void loadSongScores(QString);

signals:

};

#endif // SCORES_WIDGET_H
