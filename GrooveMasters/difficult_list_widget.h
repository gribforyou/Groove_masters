#ifndef DIFFICULT_LIST_WIDGET_H
#define DIFFICULT_LIST_WIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QShowEvent>
#include <QKeyEvent>

class Difficult_List_Widget : public QListWidget
{
    Q_OBJECT
public:
    explicit Difficult_List_Widget(QWidget *parent = nullptr);
private:
    void keyPressEvent(QKeyEvent* event);

signals:
    void difficultySelected(QString);
    void difficultSettingsSignal();
    void difficultExitSignal();
    void backToSongs();

public slots:
    void selectDifficulty();
    void emitDifficultySelected();
};

#endif // DIFFICULT_LIST_WIDGET_H
