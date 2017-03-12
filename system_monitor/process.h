#ifndef PROCESS_H
#define PROCESS_H

#include <QDir>
#include <QMainWindow>
#include <QThread>
#include <QWidget>

class process : public QWidget
{
    Q_OBJECT
public:
    explicit process(QWidget *parent = 0);
    QStringList Process_Lis();
signals:

public slots:
};

#endif // PROCESS_H
