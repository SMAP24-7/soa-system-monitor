#ifndef HARDWARE_H
#define HARDWARE_H

#include <QByteArray>
#include <QMainWindow>
#include <QObject>
#include <QProcess>
#include <QTreeWidgetItem>

class hardware : public QObject
{
    Q_OBJECT
public:
    explicit hardware(QObject *parent = 0);

signals:
     void Result_Hardware(QStringList &data);
public slots:

    void read_hardware();

private:
};

#endif // HARDWARE_H
