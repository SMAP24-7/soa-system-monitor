#ifndef HWMON_H
#define HWMON_H

#include <QObject>

class hwmon : public QObject
{
    Q_OBJECT
public:
    explicit hwmon(QObject *parent = 0);

signals:

public slots:
};

#endif // HWMON_H