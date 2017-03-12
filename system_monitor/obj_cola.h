#ifndef OBJ_COLA_H
#define OBJ_COLA_H

#include <QMainWindow>
#include <QPair>
#include <QVector>

class Obj_Cola : public QMainWindow
{
    Q_OBJECT
    QString Tag_;           //hwmonX
    QString Name_;          //nombre del archivo "name"
    QList<QPair<QString,int>> Par_;    //Par nombre-fichero <> valor
public:
    explicit Obj_Cola(QWidget *parent = 0);

    Obj_Cola(QString Tag, QString Name, QList<QPair<QString,int>> Par);
    Obj_Cola(const Obj_Cola &rhs);
    ~Obj_Cola();

    QString Get_Tag_()const;
    QString Get_Name_()const;
    QList<QPair<QString,int>> Get_Par_()const;

    void Put_Tag_( QString Tag);
    void Put_Name_( QString Name);
    void Put_Par_( QList<QPair<QString,int>> Par);

    void Set_Par_(QList<QPair<QString,int>> Par);

    Obj_Cola &operator =(const Obj_Cola &rhs);

signals:

public slots:
};

#endif // OBJ_COLA_H
