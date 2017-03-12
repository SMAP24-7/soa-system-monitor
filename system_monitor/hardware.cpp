#include "hardware.h"

hardware::hardware(QObject *parent): QObject(parent)
{

}


void hardware::read_hardware()
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
