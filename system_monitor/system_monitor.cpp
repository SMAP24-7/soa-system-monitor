#include "system_monitor.h"
#include "ui_system_monitor.h"

System_monitor::System_monitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::System_monitor)
{
    ui->setupUi(this);
}

System_monitor::~System_monitor()
{
    delete ui;
}
