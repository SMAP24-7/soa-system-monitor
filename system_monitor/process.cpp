#include "process.h"

process::process(QWidget *parent) : QWidget(parent)
{

}

QStringList process::Process_Lis()
{
    QThread::msleep(500);
    QStringList data,filter,list;
    QList<QByteArray> get_data;
    QString line, state, name, thread,pid,uid;
    QDir dir("/proc");
    QRegExp s( "\t" );
    filter << "[0-9]*";

    const char PID_PROCESS[]  = "Pid:";
    const char UID_PROCESS[]  = "Uid";
    const char NAME_PROCESS[] = "Name:";
    const char STATE_PROCESS[] = "State";
    const char THREAD_PROCESS[]= "Threads:";

    QStringList process = dir.entryList(filter);
    for (int q = 0; q < process.size();q++){
        QFile file(dir.absolutePath() + '/' + process[q] + "/cmdline");
        if(file.open(QIODevice::ReadOnly))
            line = QString(file.readAll());

        QFile file_status(dir.absolutePath()+'/'+ process[q] + "/status");
        if (file_status.open(QIODevice::ReadOnly)){
            get_data = file_status.readAll().split('\n');
            for (int w = 0; w < get_data.size(); w++)
                list << get_data[w];
            pid     = list.filter(PID_PROCESS).value(0).mid(sizeof(PID_PROCESS));
            uid     = list.filter(UID_PROCESS).value(0).mid(sizeof(UID_PROCESS));
            name    = list.filter(NAME_PROCESS).value(0).mid(sizeof(NAME_PROCESS));
            state   = list.filter(STATE_PROCESS).value(0).mid(sizeof(STATE_PROCESS));
            thread  = list.filter(THREAD_PROCESS).value(0).mid(sizeof(THREAD_PROCESS));

            list.clear();
            uid = uid.replace(s," ");
            state = state.replace(s, "");
            thread = thread.replace(s,"");

            data.push_back(pid);
            data.push_back(uid);
            data.push_back(name);
            data.push_back(state);
            data.push_back(thread);
            data.push_back(line);

        }
        file_status.close();
    }
    return data;
}
