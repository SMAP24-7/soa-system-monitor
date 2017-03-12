#include "obj_cola.h"

Obj_Cola::Obj_Cola(QWidget *parent) : QMainWindow(parent)
{

}

Obj_Cola::Obj_Cola(QString Tag, QString Name, QList<QPair<QString, int> > Par):
    Tag_(Tag), Name_(Name), Par_(Par)
{

}

Obj_Cola::Obj_Cola(const Obj_Cola &rhs)
{
    Tag_ = rhs.Get_Tag_();
    Name_ = rhs.Get_Name_();
    Par_ = rhs.Get_Par_();
}


Obj_Cola::~Obj_Cola()
{
    Tag_.clear();
    Name_.clear();
    Par_.clear();
}


QString Obj_Cola::Get_Tag_() const
{
    return Tag_;
}

QString Obj_Cola::Get_Name_() const
{
    return Name_;
}

QList<QPair<QString, int> > Obj_Cola::Get_Par_() const
{
    return Par_;
}


void Obj_Cola::Put_Tag_( QString Tag)
{
    Tag_ = Tag;
}

void Obj_Cola::Put_Name_( QString Name)
{
    Name_ = Name;
}

void Obj_Cola::Put_Par_(QList<QPair<QString, int> > Par)
{
    Par_ = Par;
}

void Obj_Cola::Set_Par_(QList<QPair<QString, int> > Par)
{
    Par_ << Par;
}

Obj_Cola& Obj_Cola::operator =(const Obj_Cola &rhs)
{
    Obj_Cola aux(rhs.Get_Tag_(), rhs.Get_Name_(), rhs.Get_Par_());
    return aux;
}



