#ifndef SETTINGS_WIDGET_H
#define SETTINGS_WIDGET_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QPalette>
#include <QDialog>

class Settings_Widget : public QDialog
{
    Q_OBJECT
public:
    explicit Settings_Widget(QWidget *parent = nullptr);
    void set_sliders(int m, int f);
private:
    QSlider* music_slider;
    QSlider* fx_slider;
private slots:
    void ok_slot();
    void change_level();
signals:
    void level_changed(int mLevel, int fLevel );
};

#endif // SETTINGS_WIDGET_H
