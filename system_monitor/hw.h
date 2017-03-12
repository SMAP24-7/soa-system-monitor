#ifndef HW_H
#define HW_H

#include <QObject>

class hw : public QObject
{
    Q_OBJECT
public:
    explicit hw(QObject *parent = 0);

signals:

public slots:
};

#endif // HW_H