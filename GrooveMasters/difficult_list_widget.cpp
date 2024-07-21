#include "difficult_list_widget.h"

Difficult_List_Widget::Difficult_List_Widget(QWidget *parent) : QListWidget(parent)
{
    this->setMaximumWidth(400);
    this->setFlow(QListWidget::LeftToRight);

    this->addItem(new QListWidgetItem("easy"));
    this->addItem(new QListWidgetItem("normal"));
    this->addItem(new QListWidgetItem("hard"));

    setCurrentRow(0);

    this->setFixedHeight(35);
}

void Difficult_List_Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==16777220){
        emitDifficultySelected();
    }
    if(event->key() == Qt::Key_S || event->key() == 1067){
        emit difficultSettingsSignal();
    }
    if(event->key() == Qt::Key_E || event->key() == 1059){
        emit difficultExitSignal();
    }
    if(event->key() == Qt::Key_Backspace){
        emit backToSongs();
    }
    QListWidget::keyPressEvent(event);
}

void Difficult_List_Widget::selectDifficulty()
{
    setFocus();
}

void Difficult_List_Widget::emitDifficultySelected()
{
    QString difficulty;
    int row = this->currentRow();
    switch (row) {
     case 0: difficulty = "easy"; break;
     case 1: difficulty = "normal"; break;
     case 2: difficulty = "hard"; break;
    }
    emit difficultySelected(difficulty);
}
