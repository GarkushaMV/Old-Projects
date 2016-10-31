#include "commander.h"
#include "ui_commander.h"

Commander::Commander(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Commander)
{
    ui->setupUi(this);
    activity = 0;
    FInf = new QFileInfo;
    provider = new QFileIconProvider;
    direct_1 = direct_1.root();
    ui->Loc_1->setText(direct_1.path());
    foreach( const QString& item, direct_1.entryList() )
    {
        QListWidgetItem* listItem = new QListWidgetItem;
        FInf->setFile(direct_1.path(), item);
        Ic = new QIcon(provider->icon(*FInf));
        listItem->setIcon(*Ic);
        listItem->setText(item);
        ui->Dir_1->addItem(listItem );
    }
    direct_2 = direct_2.root();
    ui->Loc_2->setText(direct_2.path());
    foreach( const QString& item, direct_2.entryList() )
    {
        QListWidgetItem* listItem = new QListWidgetItem;
        FInf->setFile(direct_2.path(), item);
        Ic = new QIcon(provider->icon(*FInf));
        listItem->setIcon(*Ic);
        listItem->setText(item);
        ui->Dir_2->addItem(listItem );
    }
}

Commander::~Commander()
{
    delete ui;
}

void Commander::on_CopyButton_clicked()
{
    if(QMessageBox::warning(0,"Copy?","Should I copy this?", "Yes", "No", QString(), 1, 0 ))
        return;
    if(activity == 1)
    {

        QFile file1(direct_1.path() + '/'+ ui->Dir_1->currentItem()->text());
        QFile file2(direct_2.path() + '/'+ ui->Dir_1->currentItem()->text());
        if(file2.exists())
            if(QMessageBox::warning(0,"Warning","File already exist. Should I rewrite it?", "Yes", "No", QString(), 1, 0 ) )
                return;
        file2.resize( file1.size());
        file2.open(QIODevice::WriteOnly);
        file2.write(file1.readAll());
        file1.close();
        file2.close();
    }
    else if(activity == 2)
    {
        QFile file2(direct_2.path() + '/'+ ui->Dir_2->currentItem()->text());
        QFile file1(direct_1.path() + '/'+ ui->Dir_2->currentItem()->text());
        if(file1.exists())
            if(QMessageBox::warning(0,"Warning","File already exist. Should I rewrite it?", "Yes", "No", QString(), 1, 0 ) )
                return;
        file1.open(QIODevice::WriteOnly);
        file1.resize( file2.size());
        file1.write(file2.readAll());
        file1.close();
        file2.close();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Choose, please, what should I copy!");
        msgBox.exec();
    }

    direct_1.refresh();
    ui->Loc_1->setText(direct_1.path());
    ui->Dir_1->clear();
    foreach( const QString& item, direct_1.entryList() )
    {
        QListWidgetItem* listItem = new QListWidgetItem;
        FInf->setFile(direct_1.path(), item);
        Ic = new QIcon(provider->icon(*FInf));
        listItem->setIcon(*Ic);
        listItem->setText(item);
        ui->Dir_1->addItem(listItem );
    }
    direct_2.refresh();
    ui->Loc_2->setText(direct_2.path());
    ui->Dir_2->clear();
    foreach( const QString& item, direct_2.entryList() )
    {
        QListWidgetItem* listItem = new QListWidgetItem;
        FInf->setFile(direct_2.path(), item);
        Ic = new QIcon(provider->icon(*FInf));
        listItem->setIcon(*Ic);
        listItem->setText(item);
        ui->Dir_2->addItem(listItem );
    }
    activity = 0;
}

void Commander::on_DeleteButton_clicked()
{
    if(QMessageBox::warning(0,"Delete?","Should I delete this?", "Yes", "No", QString(), 1, 0 ))
           return;
    if(activity == 1)
    {
        direct_1.remove(ui->Dir_1->currentItem()->text());
        direct_1.rmdir(ui->Dir_1->currentItem()->text());
    }
    else if(activity == 2)
    {
        direct_2.remove(ui->Dir_2->currentItem()->text());
        direct_2.rmdir(ui->Dir_2->currentItem()->text());
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Choose, please, what should I delete!");
        msgBox.exec();
    }
    direct_1.refresh();
    ui->Loc_1->setText(direct_1.path());
    ui->Dir_1->clear();
    foreach( const QString& item, direct_1.entryList() )
    {
        QListWidgetItem* listItem = new QListWidgetItem;
        FInf->setFile(direct_1.path(), item);
        Ic = new QIcon(provider->icon(*FInf));
        listItem->setIcon(*Ic);
        listItem->setText(item);
        ui->Dir_1->addItem(listItem );
    }
    direct_2.refresh();
    ui->Loc_2->setText(direct_2.path());
    ui->Dir_2->clear();
    foreach( const QString& item, direct_2.entryList() )
    {
        QListWidgetItem* listItem = new QListWidgetItem;
        FInf->setFile(direct_2.path(), item);
        Ic = new QIcon(provider->icon(*FInf));
        listItem->setIcon(*Ic);
        listItem->setText(item);
        ui->Dir_2->addItem(listItem );
    }
}




void Commander::on_Loc_1_returnPressed()
{
    if(!direct_1.cd(ui->Loc_1->text()))
    {
         QMessageBox msgBox;
         msgBox.setText("Can't go there!");
         msgBox.exec();
    }
    ui->Loc_1->setText(direct_1.path());
    ui->Dir_1->clear();
    foreach( const QString& item, direct_1.entryList() )
    {
        QListWidgetItem* listItem = new QListWidgetItem;
        FInf->setFile(direct_1.path(), item);
        Ic = new QIcon(provider->icon(*FInf));
        listItem->setIcon(*Ic);
        listItem->setText(item);
        ui->Dir_1->addItem(listItem );
    }
}
void Commander::on_Loc_2_returnPressed()
{
    if(!direct_2.cd(ui->Loc_2->text()))
    {
         QMessageBox msgBox;
         msgBox.setText("Can't go there!");
         msgBox.exec();
    }
    ui->Loc_2->setText(direct_2.path());
    ui->Dir_2->clear();
    foreach( const QString& item, direct_2.entryList() )
    {
        QListWidgetItem* listItem = new QListWidgetItem;
        FInf->setFile(direct_2.path(), item);
        Ic = new QIcon(provider->icon(*FInf));
        listItem->setIcon(*Ic);
        listItem->setText(item);
        ui->Dir_2->addItem(listItem );
    }
}


void Commander::on_Dir_1_itemDoubleClicked(QListWidgetItem *item)
{
    if(!direct_1.cd(item->text()))
    {
         QMessageBox msgBox;
         msgBox.setText("Can't go there!");
         msgBox.exec();
    }
    ui->Loc_1->setText(direct_1.path());
    ui->Dir_1->clear();
    foreach( const QString& item, direct_1.entryList() )
    {
        QListWidgetItem* listItem = new QListWidgetItem;
        FInf->setFile(direct_1.path(), item);
        Ic = new QIcon(provider->icon(*FInf));
        listItem->setIcon(*Ic);
        listItem->setText(item);
        ui->Dir_1->addItem(listItem );
    }
}


void Commander::on_Dir_2_itemDoubleClicked(QListWidgetItem *item)
{
    if(!direct_2.cd(item->text()))
    {
         QMessageBox msgBox;
         msgBox.setText("Can't go there!");
         msgBox.exec();
    }
    ui->Loc_2->setText(direct_2.path());
    ui->Dir_2->clear();
    foreach( const QString& item, direct_2.entryList() )
    {
        QListWidgetItem* listItem = new QListWidgetItem;
        FInf->setFile(direct_2.path(), item);
        Ic = new QIcon(provider->icon(*FInf));
        listItem->setIcon(*Ic);
        listItem->setText(item);
        ui->Dir_2->addItem(listItem );
    }
}


void Commander::on_Dir_1_activated(const QModelIndex &index)
{
    activity = 1;
}

void Commander::on_Dir_2_activated(const QModelIndex &index)
{
    activity = 2;
}

void Commander::on_Dir_1_itemClicked(QListWidgetItem *item)
{
    activity = 1;
}

void Commander::on_Dir_2_itemClicked(QListWidgetItem *item)
{
    activity = 2;
}
