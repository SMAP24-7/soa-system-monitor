#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

#define MAX_TAM 15

#include "obj_cola.h"
#include "hw.h"
#include "hwmon.h"
#include "process.h"

#include <iostream>
#include <QByteArray>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QFileSystemModel>
#include <QFuture>
#include <QFutureWatcher>
#include <QMainWindow>
#include <QMutex>
#include <QQueue>
#include <QStringList>
#include <QtConcurrent>
#include <QThreadPool>
#include <QTreeView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QList>
#include <QWaitCondition>

namespace Ui {
class System_monitor;
}

class System_monitor : public QMainWindow
{
    Q_OBJECT
    QQueue<Obj_Cola> Cola_;
    hwmon hwmon_;
    process process_;
    hw hardware_;

    QThread Work_hwmon_;
    QThread Work_hardware_;

    QMutex mutex_Cola_;
    QMutex print_;

    QWaitCondition insert_cola_;
    QWaitCondition get_Cola_;

    QStringList nombre_columnas_;

    QFuture<QStringList> Future_;
    QFutureWatcher<QStringList> Watcher_;

public:
    explicit System_monitor(QWidget *parent = 0);
    ~System_monitor();
signals:
       void Get_Hmon_(QString name_folder);
       void Get_hardware_();

private slots:
    void on_tabWidget_tabBarClicked(int index);

    void Insert_on_Cola_(const Obj_Cola &Block);
public slots:
    void write_hardware(const QStringList &list);

private:
    Ui::System_monitor *ui;


    void Read_Hw_(); //Lee en las carpetas hwmon
    void Print_HW_(); // Imprime los datos de los sensores

    Obj_Cola Get_Head_Cola_();
    bool Max_Tam_Cola();//Top de la cola

    void annadir_row_hwmon(QString Tag, QString name, QList<QPair<QString,int>> list);
    void actualized_valor_hwmon(QString valor, int row, int column);

    void Add_Tree_hwmon_(Obj_Cola Block);
    void Actualized_tree_hwmon_(QString name, QList<QPair<QString,int>> list);

    QStringList Process_List();
    void ProcessResult();

    QList<QByteArray> read_hardware();

    void add_tree_child(int &num, int sz, QTreeWidgetItem *parent, QStringList data);

};

#endif // SYSTEM_MONITOR_H
