#ifndef THREADHWMON_H
#define THREADHWMON_H

#include "obj_cola.h"


#include <QFile>
#include <iostream>
#include <QMainWindow>
#include <QPair>
#include <QQueue>
#include <QRunnable>
#include <QVector>

class Threadhwmon: public QRunnable
{
public:
    Threadhwmon();
};

#endif // THREADHWMON_H
