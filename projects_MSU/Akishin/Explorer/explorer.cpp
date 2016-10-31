#include "explorer.h"
#include "ui_explorer.h"

Explorer::Explorer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Explorer)
{
    ui->setupUi(this);
    FInf = new QFileInfo;
    provider = new QFileIconProvider;
    direct = direct.root();
    ui->Loc->setText(direct.path());
    foreach( const QString& item, direct.entryList() )
    {
        QListWidgetItem* listItem = new QListWidgetItem;
        FInf->setFile(direct.path(), item);
        Ic = new QIcon(provider->icon(*FInf));
        listItem->setIcon(*Ic);
        listItem->setText(item);
        ui->Dir->addItem(listItem );
    }
}

Explorer::~Explorer()
{
    delete ui;
}

void Explorer::on_BackButton_clicked()
{
    direct.cdUp();
    ui->Loc->setText(direct.path());
    ui->Dir->clear();
    foreach( const QString& item, direct.entryList() )
        if(item != ".." && item != "."){
            QListWidgetItem* listItem = new QListWidgetItem;
            FInf->setFile(direct.path(), item);
            Ic = new QIcon(provider->icon(*FInf));
            listItem->setIcon(*Ic);
            listItem->setText(item);
            ui->Dir->addItem(listItem );
    }
}

void Explorer::on_Dir_itemDoubleClicked(QListWidgetItem *item)
{
    if(!direct.cd(item->text()))
    {
         QMessageBox msgBox;
         msgBox.setText("Can't go there!");
         msgBox.exec();
    }
    ui->Loc->setText(direct.path());
    ui->Dir->clear();
    foreach( const QString& item, direct.entryList() )
    if(item != ".." && item != "."){
        QListWidgetItem* listItem = new QListWidgetItem;
        FInf->setFile(direct.path(), item);
        Ic = new QIcon(provider->icon(*FInf));
        listItem->setIcon(*Ic);
        listItem->setText(item);
        ui->Dir->addItem(listItem );
    }
}

void Explorer::on_Loc_returnPressed()
{
    QMessageBox::aboutQt(0,"Чтение содержимого...");
    if(!direct.cd(ui->Loc->text()))
    {
         QMessageBox msgBox;
         msgBox.setText("Can't go there!");
         msgBox.exec();
    }
    direct.refresh();
    ui->Loc->setText(direct.path());
    ui->Dir->clear();
    foreach( const QString& item, direct.entryList() )
    if(item != ".." && item != "."){
        QListWidgetItem* listItem = new QListWidgetItem;
        FInf->setFile(direct.path(), item);
        Ic = new QIcon(provider->icon(*FInf));
        listItem->setIcon(*Ic);
        listItem->setText(item);
        ui->Dir->addItem(listItem );
    }
}

void Explorer::CopyAction()
{
    if(QMessageBox::warning(0,"Copy?","Should I copy this?", "Yes", "No", QString(), 1, 0 ))
        return;
    direct.refresh();
    CopyBuff.clear();
    CopyBuff += direct.path() + "/" + ui->Dir->currentItem()->text();
    CopyFileName.clear();
    CopyFileName += ui->Dir->currentItem()->text();
}

void Explorer::PasteAction()
{
    QFile file1(direct.path() + '/' + CopyFileName);
    QFile file2(CopyBuff);
    if(file1.exists())
        if(QMessageBox::warning(0,"Warning","File already exists. Should I rewrite it?", "Yes", "No", QString(), 1, 0 ) )
            return;
    file1.open(QIODevice::WriteOnly);
    file2.open(QIODevice::ReadOnly);
    if(!file1.size())
    {
        file1.resize( file2.size());
        file1.write(file2.readAll());
    }
    file1.close();
    file2.close();
    direct.refresh();
    ui->Loc->setText(direct.path());
    ui->Dir->clear();
    foreach( const QString& item, direct.entryList() )
    if(item != ".." && item != "."){
        QListWidgetItem* listItem = new QListWidgetItem;
        FInf->setFile(direct.path(), item);
        Ic = new QIcon(provider->icon(*FInf));
        listItem->setIcon(*Ic);
        listItem->setText(item);
        ui->Dir->addItem(listItem );
    }

}

void Explorer::DeleteAction()
{
    if(QMessageBox::warning(0,"Delete?","Should I delete this?", "Yes", "No", QString(), 1, 0 ))
           return;
    direct.remove(ui->Dir->currentItem()->text());
    direct.rmdir(ui->Dir->currentItem()->text());
    direct.refresh();
    ui->Loc->setText(direct.path());
    ui->Dir->clear();
    foreach( const QString& item, direct.entryList() )
    if(item != ".." && item != "."){
        QListWidgetItem* listItem = new QListWidgetItem;
        FInf->setFile(direct.path(), item);
        Ic = new QIcon(provider->icon(*FInf));
        listItem->setIcon(*Ic);
        listItem->setText(item);
        ui->Dir->addItem(listItem );
    }
}
