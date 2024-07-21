#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("OCR A Extended"));
    MainWindow w;
    w.show();
    return a.exec();
}
