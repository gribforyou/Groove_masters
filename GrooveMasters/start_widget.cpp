#include "start_widget.h"


Start_Widget::Start_Widget(QWidget *parent)
{
    QHBoxLayout* hlayout = new QHBoxLayout();
    QVBoxLayout* layout = new QVBoxLayout();

    QLabel* title = new QLabel("Groove Master");
    title->setObjectName("gameTitle");
    title->setAlignment(Qt::AlignCenter);
    title->setFont(QFont("OCR A Extended", 60));

    QLabel* press = new QLabel("Press any key to start");
    press->setAlignment(Qt::AlignCenter);

    layout->addStretch();
    layout->addWidget(title);
    layout->addWidget(press);
    layout->addStretch();

    hlayout->addStretch();
    hlayout->addLayout(layout);
    hlayout->addStretch();

    this->setLayout(hlayout);
    //this->setObjectName("startWidget");
    //setStyleSheet("#startWidget{background-image: url(./bg1.png)}");
}

void Start_Widget::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    QLinearGradient gradient;
//    gradient.setColorAt(0, Qt::black);
//    gradient.setColorAt(1, Qt::transparent);
//    gradient.setStart(0, 0);
//    gradient.setFinalStop(0, size().height() * 0.8);
//    painter.setBrush(QBrush(gradient));
//    painter.setPen(Qt::NoPen);
//    painter.drawRect(0, size().height() * 0.4, size().width(), size().height() * 0.6);
//    gradient.setStart(0, size().height() * 0.8);
//    gradient.setFinalStop(0, 0);
//    painter.setBrush(QBrush(gradient));
//    painter.setPen(Qt::NoPen);
//    painter.drawRect(0, 0, size().width(), size().height() * 0.4);
//    painter.setPen(QPen(Qt::black, 3));
//    painter.drawLine(0, size().height() * 0.4, size().width(), size().height() * 0.4);
//    painter.setPen(Qt::NoPen);
//    painter.setBrush(QBrush(Qt::black));
//    int wid = 5;
//    int max_heig = 30;
//    int dif = 8;
//    int heig;
//    for(int i=0; i<width(); i+=(wid+dif)){
//        heig = rand()%max_heig;
//        painter.drawRect(i, height()*2/5 - heig, wid, heig);
//    };
}
