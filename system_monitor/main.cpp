#include "system_monitor.h"

#include <QApplication>
#include <QThreadPool>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    System_monitor w;
    w.show();

    return a.exec();
}
