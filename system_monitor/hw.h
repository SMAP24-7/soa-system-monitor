#ifndef HW_H
#define HW_H

#include <QByteArray>
#include <QMainWindow>
#include <QObject>
#include <QProcess>
#include <QTreeWidgetItem>

class hw : public QObject
{
    Q_OBJECT
public:
    explicit hw(QObject *parent = 0);

signals:
    void Result_Hardware(const QStringList &data);
public slots:
    void read_hardware();
};

#endif // HW_H
