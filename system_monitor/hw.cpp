#include "hw.h"

hw::hw(QObject *parent) : QObject(parent)
{

}

void hw::read_hardware()
{
    QString lshw = "lshw";
    QStringList argum;
    argum << "-json";

    QProcess *myprocess = new QProcess(this);
    myprocess->start(lshw,argum);
    myprocess->waitForReadyRead();
    QList<QByteArray> data = myprocess->readAll().split('\n');

    QStringList list;
    for (int q  = 0; q < data.size(); q++)
        list << data[q];

    emit Result_Hardware(list);
}
