#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

#include <QMainWindow>

namespace Ui {
class System_monitor;
}

class System_monitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit System_monitor(QWidget *parent = 0);
    ~System_monitor();

private:
    Ui::System_monitor *ui;
};

#endif // SYSTEM_MONITOR_H
