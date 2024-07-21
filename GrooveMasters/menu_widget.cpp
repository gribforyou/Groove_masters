#include "menu_widget.h"
#include <QApplication>

Menu_Widget::Menu_Widget(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout* hlayout = new QHBoxLayout();
    QVBoxLayout* layout = new QVBoxLayout();

    QLabel* label = new QLabel("Menu");
    label->setAlignment(Qt::AlignCenter);
    QPushButton* settings_button = new QPushButton("settings");
    QPushButton* exit_button = new QPushButton("exit");
    QPushButton* back_button = new QPushButton("back");

    connect(back_button, SIGNAL(clicked()), this, SLOT(back_slot()));
    connect(settings_button, SIGNAL(clicked()), this, SLOT(settings_slot()));
    connect(exit_button, SIGNAL(clicked()), this, SLOT(exit_slot()));


    layout->addStretch();
    layout->addWidget(label);
    layout->addWidget(settings_button);
    layout->addWidget(exit_button);
    layout->addWidget(back_button);
    layout->addStretch();

    hlayout->addStretch();
    hlayout->addLayout(layout);
    hlayout->addStretch();

    this->setLayout(hlayout);

    QPalette* pal = new QPalette();
    pal->setColor(this->backgroundRole(), Qt::lightGray);
    this->setPalette(*pal);
    this->setAutoFillBackground(true);
}

void Menu_Widget::back_slot()
{
    emit back_signal();
}

void Menu_Widget::settings_slot()
{
    emit settings_signal();
}

void Menu_Widget::exit_slot()
{
    emit exit_signal();
}
