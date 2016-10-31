#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "date.h"
#include <unordered_set>
#include <cstdlib>
#include <QtSql>
#include <QDebug>
#include <fstream>
#include <iostream>
#define element  std::pair< std::pair<QString, double>, double>
#define hard_d first.second
#define cost_d second
#define name_d first.first

namespace std {
template<>
class hash<element> {
public:
    size_t operator()(const element &s) const
    {
        return std::hash<double>()(s.second);
    }

};
};

std::unordered_set<element> order;
QSqlDatabase db;
int show_data = 10;
int type_data = 0;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setlocale(LC_ALL, "ru_RU");
    std::ifstream file("works.txt");

    if (!file.is_open()) {qDebug()<<"Ошибка открытия файла";
                      exit(1);
                     }
    ui->widget->hide();
    std::string str;
    while(getline(file, str))
    {
        QListWidgetItem *item = new QListWidgetItem(tr(str.c_str()), ui->listWidget);

        ui->listWidget->addItem(item);
    }
    ui->Layout->setHorizontalHeaderLabels({"Наименование","Трудозатратность", "Расходы на материалы"});
    ui->Layout->resizeColumnsToContents();
    file.close();
    db = QSqlDatabase::addDatabase("QSQLITE", "Connection");
    db.setDatabaseName("Database.db");
    if (!db.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Error"),
               db.lastError().text());
    }
    QSqlQuery query(db);
    query.prepare("CREATE TABLE IF NOT EXISTS orders (contract, customer, contacts, cost, hard, time, works)");
        if (!query.exec()) {
            qDebug("Error occurred creating table.");
            qDebug("%s.", qPrintable(db.lastError().text()));
        }

}



void MainWindow::Galocka(QListWidgetItem* itemy)
{
        bool ok = 0;
        const double cost = QInputDialog::getDouble(this, tr("Бюджет"),
                                                    itemy->text() + tr(" - бюджет (тысяч рублей)"), 0, 0,
                                                    10000000, 2, &ok);
        if (ok)
        {
             const double hard = QInputDialog::getDouble(this, tr("Нагрузка"),
                                                         itemy->text() + tr(" - нагрузка (человекодней)"),
                                                         0, 0, 200000000, 1, &ok);
             if (ok)
             {
                             if(ok)
                             {
                                QString name = itemy->text();
                                ui->Layout->insertRow(order.size());

                                QTableWidgetItem *item = new QTableWidgetItem();
                                item->setText(name);
                                ui->Layout->setItem(order.size(),0, item);

                                item = new QTableWidgetItem();
                                item->setText(QString::number(cost));
                                ui->Layout->setItem(order.size(),1, item);

                                item = new QTableWidgetItem();
                                item->setText(QString::number(hard));
                                ui->Layout->setItem(order.size(),2, item);

                                ui->Layout->resizeColumnsToContents();

                                order.insert({ {name, hard}, {cost} });
                                QMessageBox::about(0, " ", "Пункт добавлен!");

                  }
             }
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Layout_cellDoubleClicked(int row, int column)
{
        QMessageBox msgBox;
        msgBox.setText("Вы действительно хотите удалить эту строку?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Ok)
        {
            QString name = ui->Layout->item(row, 0)->text();
            double cost = std::atof(ui->Layout->item(row, 1)->text().toUtf8().constData());
            double hard = std::atof(ui->Layout->item(row, 2)->text().toUtf8().constData());
            order.erase(order.find({{name, cost}, hard}));
            ui->Layout->removeRow(row);
            QMessageBox::about(0, " ", "Пункт удалён!");
        }
}

void MainWindow::on_CreateZAKAZ_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Вы действительно хотите создать заказ?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok)
    {
            if (!db.open())
            {
              QMessageBox::critical(0, QObject::tr("Database Error"),
                        db.lastError().text());
            }
            std::unordered_set<element>::iterator it;
            char* buf = new char[1000000];
            buf[0] = '8';
            double hard = 0, cost = 0;
            int i = 0;
            bool ok = 0;
            for(it=order.begin(); it!=order.end(); it++, i++)
            {
                hard+=(*it).hard_d;
                cost+=(*it).cost_d;
                for(int j =0; ((QString) (*it).name_d).at(j).toLatin1()!= 0; j++)
                    buf[i]+= ((QString) (*it).name_d).at(j).toLatin1();
            }


            QString contract = QInputDialog::getText(this, tr("Номер заказа"), tr("Введите номер заказа"), QLineEdit::Normal, tr("00000000"), &ok);
            QString customer;
            if(ok)
                customer = QInputDialog::getText(this, tr("Заказчик"), tr("Введите заказчика"), QLineEdit::Normal, tr("Фирма"), &ok);

            QString contacts;
            if(ok)
                contacts = QInputDialog::getText(this, tr("Контакты"), tr("Введите контакты заказчика"), QLineEdit::Normal, tr("Контакты фирмы"), &ok);
            QString date;
            if(ok)
                date = QInputDialog::getText(this, tr("Сроки"), tr("Cрок выполнения\nФормат ввода: ДД/ММ/ГГГГ"), QLineEdit::Normal, tr("01/01/2015"), &ok);
            QSqlQuery query(db);
            if (ok)
            {
                int time = (date.toStdString()[0]-'0')*10+(date.toStdString()[1]-'0') + (date.toStdString()[3]-'0')*1000+(date.toStdString()[4]-'0')*100+(date.toStdString()[6]-'0')*10000000    \
                        + (date.toStdString()[7]-'0')*1000000 + (date.toStdString()[8]-'0')*100000 + (date.toStdString()[9]-'0')*10000;
                ok = query.exec( QString("INSERT INTO orders (contract, customer, contacts, cost, hard, time, works) VALUES (")+ contract.toUtf8()
                                      + QString(", '") + customer.toUtf8() + QString("', '") + contacts + QString("', ") + QString(std::to_string(cost).c_str()) + QString(", ") +
                               QString(std::to_string(hard).c_str())+ QString(", ") + QString(std::to_string(time).c_str()) + QString(", '") + QString(buf) + QString("');"));

                if(!ok)
                {
                    QMessageBox::critical(0, QObject::tr("Database Error"),
                            db.lastError().text());
                    qDebug() << query.lastQuery();
                }
                else
                {
                    order.clear();
                    ui->Layout->clear();
                    ui->Layout->setRowCount(0);
                    ui->Layout->setHorizontalHeaderLabels({"Наименование", "Трудозатратность", "Расходы на материалы"});
                    ui->Layout->resizeColumnsToContents();
                    QMessageBox::about(0, " ", "Заказ создан!");
                }


            }

            else
            {
                QMessageBox::critical(0, QObject::tr("Database Error"),
                        db.lastError().text());
                qDebug() << query.lastQuery();
            }
        }
}

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Вы действительно хотите выбрать существующий заказ?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok)
    {
        ui->Cost->hide();
        ui->Hardness->hide();
        ui->label_4->hide();
        ui->Layout->hide();
        ui->listWidget->hide();
        ui->CreateZAKAZ->hide();
        ui->pushButton_2->hide();
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("SELECT * FROM orders GROUP BY cost LIMIT "+ QString(std::to_string(show_data).c_str()) + ";", db);
        ui->tableView->setModel(model);
        ui->widget->show();
    }
}




void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Вы действительно хотите создать новый заказ?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok)
    {
        ui->Cost->show();
        ui->Hardness->show();
        ui->label_4->show();
        ui->Layout->show();
        ui->listWidget->show();
        ui->CreateZAKAZ->show();
        ui->pushButton_2->show();

        ui->widget->hide();
    }
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    show_data = arg1;
    QSqlQueryModel *model = new QSqlQueryModel;

    switch(type_data)
    {
    case(0):
        model->setQuery("SELECT * FROM orders GROUP BY cost LIMIT "+ QString(std::to_string(show_data).c_str()) + ";", db);
        break;
    case(1):
        model->setQuery("SELECT * FROM orders GROUP BY -cost LIMIT "+ QString(std::to_string(show_data).c_str()) + ";", db);
        break;
    case(2):
        model->setQuery("SELECT * FROM orders GROUP BY hard LIMIT "+ QString(std::to_string(show_data).c_str()) + ";", db);
        break;
    case(3):
        model->setQuery("SELECT * FROM orders GROUP BY -hard LIMIT "+ QString(std::to_string(show_data).c_str()) + ";", db);
        break;
    case(4):
        model->setQuery("SELECT * FROM orders GROUP BY time LIMIT "+ QString(std::to_string(show_data).c_str()) + ";", db);
        break;
    case(5):
        model->setQuery("SELECT * FROM orders GROUP BY -time LIMIT "+ QString(std::to_string(show_data).c_str()) + ";", db);
        break;
    default:
        qDebug("Error occurred with the load");
        break;
    }
    ui->tableView->setModel(model);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    type_data = index;
    QSqlQueryModel *model = new QSqlQueryModel;

    switch(type_data)
    {
    case(0):
        model->setQuery("SELECT * FROM orders GROUP BY cost LIMIT " + QString(std::to_string(show_data).c_str()) + ";", db);
        break;
    case(1):
        model->setQuery("SELECT * FROM orders GROUP BY -cost LIMIT "+ QString(std::to_string(show_data).c_str()) + ";", db);
        break;
    case(2):
        model->setQuery("SELECT * FROM orders GROUP BY hard LIMIT " + QString(std::to_string(show_data).c_str()) + ";", db);
        break;
    case(3):
        model->setQuery("SELECT * FROM orders GROUP BY -hard LIMIT "+ QString(std::to_string(show_data).c_str()) + ";", db);
        break;
    case(4):
        model->setQuery("SELECT * FROM orders GROUP BY time LIMIT " + QString(std::to_string(show_data).c_str()) + ";", db);
        break;
    case(5):
        model->setQuery("SELECT * FROM orders GROUP BY -time LIMIT "+ QString(std::to_string(show_data).c_str()) + ";", db);
        break;
    default:
        qDebug("Error occurred with te load");
        break;
    }
    ui->tableView->setModel(model);
}




void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QMessageBox msgBox;
    msgBox.setText("Вы действительно хотите оформить заказ?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok)
    {

            setlocale(LC_ALL, "ru_RU");
            std::ifstream file("template.xml");
            std::ofstream agreement("agreement.xml");
            char buff[2]={0,0};
            for(int i = 0; file >> buff[(i%2)]; i++)
            {

                if(buff[(i%2)] == 'Z')
                {
                    file >> buff[((i+1)%2)];
                    if(buff[((i+1)%2)] == 'X')
                    {
                        file >> buff[0];
                        switch(buff[0])
                        {
                        case 'N':
                            break;
                        case 'A':
                            break;
                        case 'P':
                            break;
                        case 'D':
                            break;
                        case 'C':
                            break;
                        case 'T':
                            break;
                        default:
                            qDebug() << "Error, ZX EXEPTION";
                        }
                    }
                    else
                    {
                        agreement << buff[(i%2)];
                        i++;
                        agreement << buff[(i%2)];
                    }
                }
                else
                    agreement << buff[(i%2)];
            }

    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Вы действительно хотите переместиться в архив заказов?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok)
    {

    }
}

void MainWindow::on_pushButton_5_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Вы действительно хотите переместиться в архив заказов?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok)
    {

    }
}
