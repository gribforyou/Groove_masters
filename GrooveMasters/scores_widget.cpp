#include "scores_widget.h"

Scores_Widget::Scores_Widget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QHBoxLayout* hlayout1 = new QHBoxLayout();
    QHBoxLayout* hlayout2 = new QHBoxLayout();

    QLabel *score = new QLabel("Top score:");
    QLabel *topScore = new QLabel("0");
    topScore->setObjectName("topScore");
    hlayout1->addWidget(score);
    hlayout1->addWidget(topScore);
    hlayout1->addStretch();

    QLabel *combo = new QLabel("Max combo:");
    QLabel *maxCombo = new QLabel("0");
    maxCombo->setObjectName("maxCombo");
    hlayout2->addWidget(combo);
    hlayout2->addWidget(maxCombo);
    hlayout2->addStretch();

    layout->addLayout(hlayout1);
    layout->addLayout(hlayout2);

    this->setLayout(layout);
}

void Scores_Widget::loadSongScores(QString id)
{
    std::ifstream fin("scores/" + id.toStdString() + ".dat");
    if (!fin) {
        qDebug() << "ERROR!!";
        return;
    }

    std::string str;

    try {
        getline(fin, str);
        findChild<QLabel*>("topScore")->setText(QString::fromStdString(str));
        getline(fin, str);
        findChild<QLabel*>("maxCombo")->setText(QString::fromStdString(str));
    } catch (...) {
        qDebug() << "File content error";
    }
}
