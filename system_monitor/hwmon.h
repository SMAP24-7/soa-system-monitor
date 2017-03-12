#ifndef HWMON_H
#define HWMON_H

#include "obj_cola.h"

#include <QDir>
#include <QObject>
#include <QThread>

class hwmon : public QObject
{
    Q_OBJECT

public:
    explicit hwmon(QObject *parent = 0);

signals:
    void Result_Hwmon(const Obj_Cola &Block);

public slots:
        void Calc_Hwmon(QString name_folder);

private:
        void Read_Hw_(QString &Name, QString name_folder, QList<QPair<QString,int>> &Par);

        bool Get_Hw_Valor_Input(int count_temp, QDir dir, QString name, QList<QPair<QString,int>> &Par);
        bool Get_Hw_fan_Input(int count_temp, QDir dir, QList<QPair<QString,int>> &Par);

        void Get_Senssor_hwmon_input(int count_temp, QString &file_name, QDir dir);

};

#endif // HWMON_H
