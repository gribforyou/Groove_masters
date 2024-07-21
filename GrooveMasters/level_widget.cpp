#include "level_widget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QDebug>
#include <QKeyEvent>
#include <fstream>
#include <QPainter>
#include <QPen>
#include <math.h>

Level_Widget::Level_Widget(QWidget *parent) : QWidget(parent)
{
    visualizerData = new unsigned short[visualizerDataSize];
    for (int i = 0; i < visualizerDataSize; i++)
        visualizerData[i] = 0;
    isActive = std::vector <bool>(4, false);
    notesVector.resize(4);
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->addStretch();
    QVBoxLayout *infoLayout = new QVBoxLayout();
    QLabel *label = new QLabel(this);
    label->setObjectName("score");
    label->setStyleSheet("QLabel { font-size: 40px; }");
    label->setText("Score " + QString::number(score));
    infoLayout->addWidget(label);
    label = new QLabel(this);
    label->setObjectName("grade");
    label->setStyleSheet("QLabel { font-size: 40px; }");
    infoLayout->addWidget(label);
    label = new QLabel(this);
    label->setObjectName("combo");
    label->setStyleSheet("QLabel { font-size: 20px; }");
    infoLayout->addWidget(label);
    horizontalLayout->addLayout(infoLayout);
    verticalLayout->addLayout(horizontalLayout);
    verticalLayout->addStretch();
    horizontalLayout = new QHBoxLayout();
    label = new QLabel();
    label->setText("Press Enter to Pause");
    label->setAlignment(Qt::AlignHCenter);
    horizontalLayout->addWidget(label);
    label = new QLabel();
    label->setText("Press S to Show Settings");
    label->setAlignment(Qt::AlignHCenter);
    horizontalLayout->addWidget(label);
    label = new QLabel();
    label->setText("Press Escape to Exit to Menu");
    label->setAlignment(Qt::AlignHCenter);
    horizontalLayout->addWidget(label);
    verticalLayout->addLayout(horizontalLayout);
    connect(&timer, &QTimer::timeout, this, &Level_Widget::updateNotes);
    songPlayer.setVolume(10);
    audioProbe.setSource(&songPlayer);
    connect(&audioProbe, &QAudioProbe::audioBufferProbed, this, &Level_Widget::updateVisualizerData);
    for (int i = 0; i < 4; i++) {
        QMediaPlayer *tapSoundPlayer = new QMediaPlayer();
        tapSoundPlayer->setMedia(QUrl::fromLocalFile("tap.mp3"));
        tapSoundPlayer->setVolume(20);
        tapSoundPlayers.push_back( tapSoundPlayer);
    };
}

bool Level_Widget::loadLevel(Song_Info songInfo, QString difficulty)
{
    songPlayer.setMedia(QUrl::fromLocalFile("audio/levels/" + songInfo.getId() + ".mp3"));
    std::ifstream fin("charts/" + difficulty.toStdString() + "/" + songInfo.getId().toStdString() + ".chrt");
    if (!fin) {
        return false;
    };
    fin >> bpm >> offset;
    spb = 60. / bpm;
    fin.ignore();
    for (int i = 0; i < 4; i++) {
        std::string input;
        getline(fin, input);
        if (input != "") {
            QString notesDataLine = QString::fromStdString(input);
            QStringList notesDataList = notesDataLine.split(";");
            for (int j = 0; j < notesDataList.size(); j++)
                notesVector[i].push_back(std::make_pair(notesDataList[j].split(",")[0].toInt(), notesDataList[j].split(",")[1].toInt()));
        };
    };
    return true;
}

void Level_Widget::startLevel()
{
    score = 0, combo = 0;
    findChild<QLabel*>("score")->setText("Score: " + QString::number(score));
    findChild<QLabel*>("grade")->setText("");
    timer.start(interval);
    songPlayer.setPosition(0);
    songPlayer.play();
    audioProbe.setSource(&songPlayer);
    qDebug() << audioProbe.isActive();
    isPaused = false;
}

double Level_Widget::getSongLength() const
{
    return songPlayer.duration() / 1000.;
}

double Level_Widget::getSongTime() const
{
    return songPlayer.position() / 1000.;
}

void Level_Widget::showEvent(QShowEvent *event)
{
    startLevel();
}

void Level_Widget::hideEvent(QHideEvent *event)
{
    songPlayer.stop();
}

void Level_Widget::addPointsToScore(int note)
{
    int offset = abs((getSongTime() - note * spb) * 1000 - this->offset), points = 0;
    if (offset <= 50) {
        points = 1000;
        findChild<QLabel*>("grade")->setText("Perfect!");
    }
    else
        if (offset <= 100) {
            points = 500;
            findChild<QLabel*>("grade")->setText("Great!");
        }
        else
            if (offset <= 200) {
                points = 250;
                findChild<QLabel*>("grade")->setText("Good!");
            }
            else
                if (offset <= 300) {
                    points = 100;
                    findChild<QLabel*>("grade")->setText("Bad!");
                }
                else if (offset <= 500)
                    findChild<QLabel*>("grade")->setText("Missed!");
    if (points > 100) {
        combo++;
        findChild<QLabel*>("combo")->setText("Combo " + QString::number(combo));
    }
    else {
        combo = 0;
        findChild<QLabel*>("combo")->setText("");
    };
    score += points;
    findChild<QLabel*>("score")->setText(QString::number(score));
}

void Level_Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    QLinearGradient gradient;
    gradient.setColorAt(0, Qt::black);
    gradient.setColorAt(1, Qt::transparent);
    gradient.setStart(0, 0);
    gradient.setFinalStop(0, size().height());
    painter.setBrush(gradient);
    painter.drawRect(0, size().height() * 0.4, size().width(), size().height());
    gradient.setStart(0, size().height());
    gradient.setFinalStop(0, 0);
    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, size().width(), size().height() * 0.4);
    painter.setPen(Qt::black);
    painter.drawLine(0, size().height() * 0.4, size().width(), size().height() * 0.4);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::black));
    int spacing = (size().width() - 5 * visualizerDataSize) / (visualizerDataSize + 1);
    int maxHeight = 30;
    for(int i = 0; i < visualizerDataSize; i++){
        int height = rand() % maxHeight;
        painter.drawRect(spacing * (i + 1) + 5 * i, size().height() * 0.4 - height, 5, height);
    };
    QColor color(Qt::black); // progress bar
    color.setAlpha(200);
    painter.setBrush(color);
    painter.drawRect(0, 0, getSongTime(), 10);
    painter.setPen(Qt::black);
    int columnWidth = size().width() / 8, columnHeight = size().height() * 0.5;
    painter.translate(size().width() / 4, size().height() * 0.9);
    painter.scale(1, -1);
    gradient.setColorAt(0, Qt::white); // field
    gradient.setStart(0, -size().height() * 0.4);
    gradient.setFinalStop(0, columnHeight);
    painter.setBrush(gradient);
    QPolygon fieldPolygon;
    fieldPolygon << QPoint(0, 0) << QPoint(columnWidth * 4 * 0.3, columnHeight) << QPoint(columnWidth * 4 * 0.7, columnHeight) << QPoint(columnWidth * 4, 0);
    painter.drawPolygon(fieldPolygon);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::black);
    for (int i = 0; i < 5; i++)
        painter.drawLine(columnWidth * i, 0, columnWidth * 4 * 0.3 + columnWidth * i * 0.4, columnHeight);
    painter.drawLine(0, 0, columnWidth * 4, 0);
    painter.drawLine(columnWidth * 4 * 0.3 * noteSize / columnHeight, noteSize, columnWidth * 4 + (columnWidth * 4 * 0.3 + columnWidth * 4 * 0.4 - columnWidth * 4) * noteSize /columnHeight, noteSize);
    color.setAlpha(150);
    painter.setBrush(color); // notes
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < notesVector[i].size(); j++) {
            std::pair <int, int> note = notesVector[i][j];
            double noteStartPos = (note.first * spb + offset / 1000. - getSongTime()) * secondSize, noteLength = note.second * spb * secondSize, noteEndPos = noteStartPos + noteLength + noteSize;
            if (noteStartPos < columnHeight && noteEndPos > 0) {
                QPolygon notePolygon;
                notePolygon << QPoint(columnWidth * i + (columnWidth * 4 * 0.3 + columnWidth * i * 0.4 - columnWidth * i) * ((noteStartPos < 0) ? 0 : sin(noteStartPos / columnHeight * acos(-1) / 2) * columnHeight) / columnHeight, (noteStartPos < 0) ? 0 : sin(noteStartPos / columnHeight * acos(-1) / 2) * columnHeight);
                notePolygon << QPoint(columnWidth * i + (columnWidth * 4 * 0.3 + columnWidth * i * 0.4 - columnWidth * i) * ((noteEndPos > columnHeight) ? columnHeight : sin(noteEndPos / columnHeight * acos(-1) / 2) * columnHeight) / columnHeight, (noteEndPos > columnHeight) ? columnHeight : sin(noteEndPos / columnHeight * acos(-1) / 2) * columnHeight);
                notePolygon << QPoint(columnWidth * (i + 1) + (columnWidth * 4 * 0.3 + columnWidth * (i + 1) * 0.4 - columnWidth * (i + 1)) * ((noteEndPos > columnHeight) ? columnHeight : sin(noteEndPos / columnHeight * acos(-1) / 2) * columnHeight) / columnHeight, (noteEndPos > columnHeight) ? columnHeight : sin(noteEndPos / columnHeight * acos(-1) / 2) * columnHeight);
                notePolygon << QPoint(columnWidth * (i + 1) + (columnWidth * 4 * 0.3 + columnWidth * (i + 1) * 0.4 - columnWidth * (i + 1)) * ((noteStartPos < 0) ? 0 : sin(noteStartPos / columnHeight * acos(-1) / 2) * columnHeight) / columnHeight, (noteStartPos < 0) ? 0 : sin(noteStartPos / columnHeight * acos(-1) / 2) * columnHeight);
                painter.drawPolygon(notePolygon);
            };
        };
    };
    painter.setBrush(color);
    for (int i = 0; i < 4; i++)
        if (isActive[i]) {
            QPolygon keyPolygon;
            keyPolygon << QPoint(columnWidth * i, 0);
            keyPolygon << QPoint(columnWidth * i + (columnWidth * 4 * 0.3 + columnWidth * i * 0.4 - columnWidth * i) * noteSize / columnHeight, noteSize);
            keyPolygon << QPoint(columnWidth * (i + 1) + (columnWidth * 4 * 0.3 + columnWidth * (i + 1) * 0.4 - columnWidth * (i + 1)) * noteSize / columnHeight, noteSize);
            keyPolygon << QPoint(columnWidth * (i + 1), 0);
            painter.drawPolygon(keyPolygon);
        };
}

void Level_Widget::updateNotes()
{
    for (int i = 0; i < 4; i++)
        if (notesVector[i].size() != 0)
            if (offset + ((notesVector[i][0].first + notesVector[i][0].second) * spb - getSongTime()) * 1000 < -1000)
                notesVector[i].erase(notesVector[i].begin());
    update();
}

void Level_Widget::updateVisualizerData(QAudioBuffer buffer)
{
    unsigned short *data = const_cast<unsigned short*>(buffer.constData<quint16>());
    for (int i = 0; i < visualizerDataSize; i++)
        visualizerData[i] = data[i];
    qDebug() << "help";
}

void Level_Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat() == false) {
        if (event->key() == Qt::Key_S) {
            pause();
        };
        if (event->key() == 16777220) {
            if (isPaused)
                resume();
            else
                pause();
        };
        if (isPaused == false && (event->key() == Qt::Key_D || event->key() == Qt::Key_F || event->key() == Qt::Key_J || event->key() == Qt::Key_K)) {
            QMediaPlayer *tapSoundPlayer;
            if (event->key() == Qt::Key_D) {
                if (notesVector[0].size() != 0)
                    addPointsToScore(notesVector[0][0].first);
                tapSoundPlayer = tapSoundPlayers[0];
                isActive[0] = true;
            }
            else
                if (event->key() == Qt::Key_F) {
                    if (notesVector[1].size() != 0)
                        addPointsToScore(notesVector[1][0].first);
                    tapSoundPlayer = tapSoundPlayers[1];
                    isActive[1] = true;
                }
                else
                    if (event->key() == Qt::Key_J) {
                        if (notesVector[2].size() != 0)
                            addPointsToScore(notesVector[2][0].first);
                        tapSoundPlayer = tapSoundPlayers[2];
                        isActive[2] = true;
                    }
                    else
                        if (event->key() == Qt::Key_K) {
                            if (notesVector[3].size() != 0)
                                addPointsToScore(notesVector[3][0].first);
                            tapSoundPlayer = tapSoundPlayers[3];
                            isActive[3] = true;
                        };
            if (tapSoundPlayer != nullptr) {
                if (tapSoundPlayer->state() == QMediaPlayer::PlayingState)
                    tapSoundPlayer->setPosition(0);
                else
                    tapSoundPlayer->play();
            };
        };
    };
}

void Level_Widget::keyReleaseEvent(QKeyEvent *event)
{
    if (isPaused == false && event->isAutoRepeat() == false) {
        QMediaPlayer *tapSoundPlayer;
        if (event->key() == Qt::Key_D) {
            if (notesVector[0].size() != 0 && notesVector[0][0].second != 0)
                addPointsToScore(notesVector[0][0].first + notesVector[0][0].second);
            tapSoundPlayer = tapSoundPlayers[0];
            isActive[0] = false;
        }
        else
            if (event->key() == Qt::Key_F) {
                if (notesVector[1].size() != 0 && notesVector[1][0].second != 0)
                    addPointsToScore(notesVector[1][0].first + notesVector[1][0].second);
                tapSoundPlayer = tapSoundPlayers[1];
                isActive[1] = false;
            }
            else
                if (event->key() == Qt::Key_J) {
                    if (notesVector[2].size() != 0 && notesVector[2][0].second != 0)
                        addPointsToScore(notesVector[2][0].first + notesVector[2][0].second);
                    tapSoundPlayer = tapSoundPlayers[2];
                    isActive[2] = false;
                }
                else
                    if (event->key() == Qt::Key_K) {
                        if (notesVector[3].size() != 0 && notesVector[3][0].second != 0)
                            addPointsToScore(notesVector[3][0].first + notesVector[3][0].second);
                        tapSoundPlayer = tapSoundPlayers[3];
                        isActive[3] = false;
                    };
        if (tapSoundPlayer != nullptr) {
            if (tapSoundPlayer->state() == QMediaPlayer::PlayingState && tapSoundPlayer->position() >= 150)
                tapSoundPlayer->setPosition(0);
            else
                if (tapSoundPlayer->state() == QMediaPlayer::StoppedState)
                    tapSoundPlayer->play();
        };
    };
}

void Level_Widget::setMusicVolume(int n)
{
    songPlayer.setVolume(n);
}

void Level_Widget::setFxVolume(int n)
{
    for (int i = 0; i < 4; i++)
        tapSoundPlayers[i]->setVolume(n);
}

void Level_Widget::pause()
{
    timer.stop();
    songPlayer.pause();
    isPaused = true;
}

void Level_Widget::resume()
{
    timer.start(interval);
    songPlayer.play();
    isPaused = false;
}
