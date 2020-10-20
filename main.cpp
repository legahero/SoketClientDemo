#include "soketmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SoketMainWindow w;
    w.show();
    return a.exec();
}
