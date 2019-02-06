#include "mainhorserace.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainHorseRace w;
    w.show();

    return a.exec();
}
