#include "hwmon.h"


hwmon::hwmon(QObject *parent) : QObject(parent)
{

}

void hwmon::Calc_Hwmon(QString name_folder)
{
    QThread::msleep(500);
    QString Name;
    QList<QPair<QString, int> > Par;
    Read_Hw_(Name, name_folder, Par);
    Obj_Cola Block_(name_folder, Name, Par);

    emit Result_Hwmon(Block_);

}

void hwmon::Read_Hw_(QString &Name,QString name_folder, QList<QPair<QString, int> > &Par)
{

    QString dir = "/sys/class/hwmon/";
    dir.append(name_folder);
    QDir directory(dir);
    QFile File(directory.absoluteFilePath("name"));
    QString name;
    int count_temp = 1;
    int count_fan = 1;
    bool files_temp = true;
    bool files_fan = true;
    if (File.open(QIODevice::ReadOnly)){
        Name = File.readLine();
        Name.remove('\n');

        while (files_temp){
            name = "temp";
            files_temp = Get_Hw_Valor_Input(count_temp, directory,name, Par);
            count_temp++;
        }
        while (files_fan){
            name = "fan";
            files_fan = Get_Hw_Valor_Input(count_temp, directory,name, Par);
            count_fan++;
        }
    }
    File.close();
}

bool hwmon::Get_Hw_Valor_Input(int count_temp, QDir dir, QString name, QList<QPair<QString, int> > &Par)
{
    QString file_temp_name = name ;
    Get_Senssor_hwmon_input(count_temp,file_temp_name,dir);
    QFile file(dir.absoluteFilePath(file_temp_name));
    if(file.open(QIODevice::ReadOnly)){
        bool ok;
        QString aux = file.readLine();
        file.close();
        Par << (qMakePair(file_temp_name,aux.toInt(&ok,10)/1000));
       return true;
        }
    else return false;
}

bool hwmon::Get_Hw_fan_Input(int count_temp, QDir dir, QList<QPair<QString, int> > &Par)
{
    QString file_temp_name = "fan" ;
    Get_Senssor_hwmon_input(count_temp,file_temp_name,dir);
    QFile file(dir.absoluteFilePath(file_temp_name));
    if(file.open(QIODevice::ReadOnly)){
        bool ok;
        QString aux = file.readLine();
        file.close();
        Par << (qMakePair(file_temp_name,aux.toInt(&ok,10)/1000));
       return true;
        }
    else return false;
}

void hwmon::Get_Senssor_hwmon_input(int count, QString &file_name, QDir dir)
{
    QString name = file_name;
    name.append(QString::number(count));
    name.append("_input");
    QFile file_sensor(dir.absoluteFilePath(name));
    if (file_sensor.open(QIODevice::ReadOnly))
        file_name=name;
}
