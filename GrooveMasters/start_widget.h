#ifndef START_WIDGET_H
#define START_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QLinearGradient>

class Start_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Start_Widget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
signals:

};

#endif // START_WIDGET_H
