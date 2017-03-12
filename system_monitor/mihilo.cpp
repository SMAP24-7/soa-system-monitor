
    #include "mihilo.h"


    MiHilo::MiHilo()
    {

    }

    MiHilo::~MiHilo()
    {

    }

    void MiHilo::Calc_hwmon_( Obj_Cola &Block)
    {
        count_ = 0;
        QString Tag, Name;
        QList<QPair<QString,int>> Par;
        Tag = "hwmon";
        Tag.append(QString::number(count_));
        int count =0;
        Read_Hw_(count, Name, Par);
        Block.Put_Name_(Name);
        Block.Put_Par_(Par);
        Block.Put_Tag_(Tag);

        emit Send_hwmon_result_(Block);
    }


    bool MiHilo::Read_Hw_(int count, QString &Name,QList<QPair<QString,int>> &Par)
    {
        QString dir = "/sys/class/hwmon/hwmon";
        QString Val_temp = dir;
        int count_temp = 1;
        int count_fan = 1;
        bool files_temp = true;
        bool files_fan = true;
        Name_Hw_(count, dir, dir);
        QFile File(dir);
        if (File.open(QIODevice::ReadOnly)){
            Name = File.readLine();

            while (files_temp){
            files_temp = Get_Hw_Temp_Input(count, count_temp, Val_temp, Par);
            count_temp++;
            }
            while (files_fan){
            files_fan = Get_Hw_fan_Input(count, count_fan, Val_temp, Par);
            count_fan++;
            }

            File.close();
            return true;
        }
        File.close();
        return false;
    }

    bool MiHilo::Get_Hw_Temp_Input(int count, int count_temp, QString dir, QList<QPair<QString,int>> &Par)
    {
        QString name, file_name ;
        Name_Hw_Temp(count,count_temp,name,file_name,dir);
        QFile file(name);
        if(file.open(QIODevice::ReadOnly)){
            bool ok;
            QString aux = file.readLine();
            file.close();
            Par << (qMakePair(file_name,aux.toInt(&ok,10)/1000));
           return true;
            }
        else return false;
    }

    bool MiHilo::Get_Hw_fan_Input(int count, int count_fan, QString dir, QList<QPair<QString,int>> &Par)
    {
        QString file_dir, file_name;
        Name_Hw_fan(count,count_fan,file_dir, file_name,dir);
        QFile file(file_dir);
        if(file.open(QIODevice::ReadOnly)){
            bool ok;
            QString aux = file.readLine();
            file.close();
            Par << (qMakePair(file_name,aux.toInt(&ok,10)/1000));
           return true;
            }
        else return false;
    }

    void MiHilo::Name_Hw_(int count, QString &Tag, QString dir)
    {
        Tag = dir;
        Tag.append(QString::number(count));
        Tag.append("/name");
    }

    void MiHilo::Name_Hw_Temp(int count, int count_temp, QString &name,QString &file_name, QString dir)
    {
        name = dir;
        name.append(QString::number(count));
        name.append("/");
        file_name.append("temp");

        file_name.append(QString::number(count_temp));
        file_name.append("_input");
        name.append(file_name);
    }

    void MiHilo::Name_Hw_fan(int count, int count_fan, QString &name, QString &file_name, QString dir)
    {
        name = dir;
        name.append(QString::number(count));
        name.append("/");
        file_name.append("fan");
        file_name.append(QString::number(count_fan));
        file_name.append("_input");
        name.append(file_name);
    }
