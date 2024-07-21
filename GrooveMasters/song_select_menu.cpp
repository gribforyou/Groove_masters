#include "song_select_menu.h"

Song_Select_Menu::Song_Select_Menu(QWidget *parent) : QWidget(parent)
{
    songInfoWidget = new Song_Info_Widget();
    songListWidget = new Song_List_Widget();
    difficultListWidget = new Difficult_List_Widget();
    QPushButton* startButton = new QPushButton("start");
    startButton->setFixedHeight(60);
    startButton->setStyleSheet("QPushButton { font-size: 20px; }");
    connect(startButton, &QPushButton::clicked, this, [=]{difficultListWidget->emitDifficultySelected();});

    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(songListWidget);
    layout->addWidget(difficultListWidget);
    layout->addWidget(startButton);

    mainLayout->addWidget(songInfoWidget);
    mainLayout->addLayout(layout);

    loadSongInfoVector();

    songListWidget->updateSongListWidget(songInfoVector);

    connect(songListWidget, &Song_List_Widget::selectedSongChanged, this, &Song_Select_Menu::changeSelectedSong);
    connect(difficultListWidget, &Difficult_List_Widget::difficultySelected, this, &Song_Select_Menu::emitLevelSelected);
    connect(difficultListWidget, SIGNAL(backToSongs()), this, SLOT(backToSongs()));
    connect(songListWidget, &Song_List_Widget::songSelected, this, &Song_Select_Menu::selectDifficulty);


    songInfoWidget->loadSongInfo(songInfoVector[0]);

    previewPlayer.setVolume(20);
}

void Song_Select_Menu::loadSongInfoVector()
{
    std::ifstream fin("songinfo.dat");
    if (!fin) {
        qDebug() << "error!";
        return;
    };
    while (!fin.eof()) {
        std::string input;
        getline(fin, input);
        if (input != "") {
            QString songInfoLine = QString::fromStdString(input);
            QStringList songInfoList = songInfoLine.split(";");
            Song_Info songInfo;
            songInfo.setId(songInfoList[0]);
            songInfo.setTitle(songInfoList[1]);
            songInfo.setAuthor(songInfoList[2]);
            songInfoVector.push_back(songInfo);
        };
    };
    std::sort(songInfoVector.begin(), songInfoVector.end(), [](const Song_Info &song1, const Song_Info &song2) { return (song1.getTitle() < song2.getTitle()); });
}

Song_List_Widget *Song_Select_Menu::getSongListWidget()
{
    return this->songListWidget;
}

Song_Info_Widget *Song_Select_Menu::getSongInfoWidget()
{
    return this->songInfoWidget;
}

Difficult_List_Widget *Song_Select_Menu::getDifficultListWidget()
{
    return this->difficultListWidget;
}

int Song_Select_Menu::getSelectedSong() const
{
    return selectedSong;
}

void Song_Select_Menu::setMusicVolume(int n)
{
    previewPlayer.setVolume(n);
}

void Song_Select_Menu::hideEvent(QHideEvent *event)
{
    previewPlayer.stop();
}

void Song_Select_Menu::paintEvent(QPaintEvent *event)
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
    int wid = 5; // visualizer
    int max_heig = 50;
    int dif = 20;
    int heig;
    for(int i=0; i<width(); i+=(wid+dif)){
        heig = rand()%max_heig;
        painter.drawRect(i, size().height()*0.4-heig, wid, heig);
    };
}

void Song_Select_Menu::backToSongs()
{
    this->songListWidget->setFocus();
}

void Song_Select_Menu::changeSelectedSong(int selectedSong)
{
    Song_Info songInfo = songInfoVector[selectedSong];
    previewPlayer.setMedia(QUrl::fromLocalFile("audio/previews/" + songInfo.getId() + ".mp3"));
    previewPlayer.play();
    songInfoWidget->loadSongInfo(songInfo);
    this->selectedSong = selectedSong;
}

void Song_Select_Menu::emitLevelSelected(QString difficulty)
{
    emit levelSelected(songInfoVector[selectedSong], difficulty);
}

void Song_Select_Menu::selectDifficulty()
{
    this->difficultListWidget->selectDifficulty();
}
