#include "system_monitor.h"
#include "ui_system_monitor.h"

System_monitor::System_monitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::System_monitor)
{
    ui->setupUi(this);
    QThreadPool::globalInstance()->maxThreadCount();

    qRegisterMetaType<Obj_Cola>("Obj_Cola");
    qRegisterMetaType<QString>("QString");
    qRegisterMetaType<QStringList>("QStringList");

    connect(this,SIGNAL(Get_hardware_()),&hardware_,SLOT(read_hardware()));
    connect(&hardware_,SIGNAL(Result_Hardware(QStringList)),this,SLOT(write_hardware(QStringList)));
    hardware_.moveToThread(&Work_hardware_);
    Work_hardware_.start();


    connect(this,SIGNAL(Get_Hmon_(QString)), &hwmon_,SLOT(Calc_Hwmon(QString)));
    connect(&hwmon_,SIGNAL(Result_Hwmon(Obj_Cola)),this,SLOT(Insert_on_Cola_(Obj_Cola)));
    hwmon_.moveToThread(&Work_hwmon_);
    Work_hwmon_.start();



    connect(&Watcher_,SIGNAL(finished()),&process_,SLOT(Process_Lis()));
    Future_ = QtConcurrent::run(&process_,&process::Process_Lis);
    Watcher_.setFuture(Future_);


}

System_monitor::~System_monitor()
{
    delete ui;

    Work_hwmon_.quit();
    Work_hwmon_.wait();
}

void System_monitor::Read_Hw_()
{

    QDir dir_hwmon("/sys/class/hwmon");
    int count_hwmon =0;
    QString name_folder_hwmon = "hwmon";
    name_folder_hwmon.append(QString::number(count_hwmon));

    while( dir_hwmon.cd(name_folder_hwmon)){
        emit Get_Hmon_(name_folder_hwmon);
        name_folder_hwmon = "hwmon";
        count_hwmon++;
        name_folder_hwmon.append(QString::number(count_hwmon));
        dir_hwmon.cdUp();
    }
}

void System_monitor::Print_HW_()
{

    if (!Cola_.empty()){
        Obj_Cola Block = Get_Head_Cola_();
        QList<QPair<QString,int>> list = Block.Get_Par_();

        if (ui->hwmontable->columnCount() == 0){
            QTableWidgetItem *name_col = new QTableWidgetItem("name");
            QTableWidgetItem *valor_col = new QTableWidgetItem("valor");
            ui->hwmontable->setColumnCount(2);
            ui->hwmontable->setHorizontalHeaderItem(0,name_col);
            ui->hwmontable->setHorizontalHeaderItem(1,valor_col);
            annadir_row_hwmon(Block.Get_Tag_(),Block.Get_Name_(),list);
        }
        else{
            bool new_row = true;
            int row = ui->hwmontable->rowCount();
            for (int q  = 0; q < row && new_row ; q++){
                if (ui->hwmontable->item(q,0)->text() == Block.Get_Name_()){
                    new_row = false;
                    if (list.size()){
                        for (int w = 0; w < list.size();w++){
                            QTableWidgetItem *valor = new QTableWidgetItem(QString::number(list[w].second,10));
                            ui->hwmontable->setItem(q+w+1,1,valor);
                        }
                    }
                }
            }
            if (new_row){
                new_row = true;
                annadir_row_hwmon(Block.Get_Tag_(),Block.Get_Name_(),list); //Añade una nueva fila con todos los datos + hace bucle con la lista
            }
        }
    }
}

Obj_Cola System_monitor::Get_Head_Cola_()
{
    mutex_Cola_.lock();

    Obj_Cola Block = Cola_.first();
    Cola_.pop_front();
    insert_cola_.wakeAll();

    mutex_Cola_.unlock();
    return Block;
}

bool System_monitor::Max_Tam_Cola()
{
    if (Cola_.size() < MAX_TAM ) return false;
    else return true;
}

void System_monitor::annadir_row_hwmon(QString Tag, QString name, QList<QPair<QString, int>> list)
{
    QTableWidgetItem *tag_row = new QTableWidgetItem(Tag);
    QTableWidgetItem *name_row = new QTableWidgetItem(name);

    ui->hwmontable->setRowCount(ui->hwmontable->rowCount()+1);
    ui->hwmontable->setVerticalHeaderItem(ui->hwmontable->rowCount()-1,tag_row);
    ui->hwmontable->setItem(ui->hwmontable->rowCount()-1,0,name_row);

    if (list.size()){
        for (int q = 0; q < list.size();q++){
            QTableWidgetItem *valor_name = new QTableWidgetItem(list[q].first);
            QTableWidgetItem *valor = new QTableWidgetItem(QString::number(list[q].second,10));
            ui->hwmontable->setRowCount(ui->hwmontable->rowCount()+1);
            ui->hwmontable->setVerticalHeaderItem(ui->hwmontable->rowCount()-1,tag_row);
            ui->hwmontable->setItem(ui->hwmontable->rowCount()-1,0,valor_name);
            ui->hwmontable->setItem(ui->hwmontable->rowCount()-1,1,valor);
        }
    }
}

void System_monitor::actualized_valor_hwmon(QString valor, int row, int column)
{
   QTableWidgetItem *modify = new QTableWidgetItem(valor);
   ui->hwmontable->setItem(row,column,modify);
}

void System_monitor::ProcessResult()
{
    QStringList Table_Process = Future_.result();
    if (ui->processtable->columnCount() == 0){
        QStringList column_name;
        column_name << "PID" << "UID" << "name" << "state" << "thread" << "line";
        ui->processtable->setColumnCount(6);
        ui->processtable->setHorizontalHeaderLabels(column_name);
    }
    int col = ui->processtable->columnCount();
    int row = Table_Process.size()/col;
    ui->processtable->setRowCount(row);
    for (int q = 0; q < row ; q++)
        for(int w = 0; w < col; w++)
            ui->processtable->setItem(q,w,new QTableWidgetItem(Table_Process[q*col + w]));
}


void System_monitor::write_hardware(const QStringList &list)
{
    QTreeWidgetItem *tag = new QTreeWidgetItem(ui->hardwaretree);
    //QList<QByteArray> data = read_hardware();
    int num = 0;
    add_tree_child(num,list.size(),tag, list);
}

void System_monitor::add_tree_child(int &num, int sz, QTreeWidgetItem *parent, QStringList data)
{
    QTreeWidgetItem *child = new QTreeWidgetItem();
    QRegExp s( "children|:[|]" );
    bool father = false;
    for (int q = num;q < sz && !father ; q++){
        if (QString(data[q]).contains("{")){
            parent->addChild(child);
            q++;
            add_tree_child(q,sz,child,data);
        }
        else if (QString(data[q]).contains("}")){
            father = true;
            q--;
        }
        else if (q < sz && !father && (!QString(data[q]).contains(s) && !QString(data[q]).contains("]") )){
            QTreeWidgetItem *child = new QTreeWidgetItem();
            child->setText(0,QString(data[q]).replace("  ", ""));
            parent->addChild(child);
        }
        num = q;
    }
    num ++;
}

void System_monitor::on_tabWidget_tabBarClicked(int index)
{
    bool do_hardware = true;
    if (index == 0){
        Read_Hw_();
        Print_HW_();
    }
    else if (index == 1){
        connect(&Watcher_,SIGNAL(finished()),&process_,SLOT(Process_Lis()));
        Future_ = QtConcurrent::run(&process_,&process::Process_Lis);
        Watcher_.setFuture(Future_);
        ProcessResult();
    }
    else if (index == 2){
        if (do_hardware){
            emit Get_hardware_();
        }
        else do_hardware = false;
    }
}

void System_monitor::Insert_on_Cola_(const Obj_Cola &Block)
{
    mutex_Cola_.lock();
    if (!Max_Tam_Cola()){
        Cola_.push_back(Block);
        get_Cola_.wakeAll();
    }
    else
        insert_cola_.wait(&mutex_Cola_);

    mutex_Cola_.unlock();
    on_tabWidget_tabBarClicked(0);
}
