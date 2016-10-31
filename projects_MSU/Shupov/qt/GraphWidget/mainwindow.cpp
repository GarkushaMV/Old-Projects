#include "mainwindow.h"
#include <iostream>
#include <cmath>
#include <QDialog>
#include <QMessageBox>
#include <QPaintEvent>
#include "dialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect( this, SIGNAL(sendSaveFilePath(  const QString&  )), ui->graphWidget, SLOT( saveToFile(const QString&)) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_NewGrathButton_clicked()
{
    Dialog asking;
    if(asking.exec())
    {
        QMessageBox msgBox;
        if(asking.MinDegreeNumber > asking.MaxDegreeNumber)
        {
            msgBox.setText("Incorrect input! Minimal degree should be smaller than maximal degree. Please, try again.");
            msgBox.exec();
            emit on_NewGrathButton_clicked();
            return;
        }


        if(asking.MinDegreeNumber == 0 && asking.MaxDegreeNumber == 0 && asking.VertexNumber != asking.ComponentNumber)
        {
            msgBox.setText("Incorrect input! If minimal and maximal degree is zero - component number should be equal number of vertex. Please, sure nothigh affects your mental healph and try again.");
            msgBox.exec();
            emit on_NewGrathButton_clicked();
            return;
        }
        if(asking.MinDegreeNumber == 0 && asking.MaxDegreeNumber > 0 && asking.ComponentNumber == 1)
        {
            msgBox.setText("Incorrect input! If minimal and maximal degree is zero - component number should be equal number of vertex. Please, try again.");
            msgBox.exec();
            emit on_NewGrathButton_clicked();
            return;
        }
        if((asking.MaxDegreeNumber == 1 && asking.MinDegreeNumber == 1) && (asking.ComponentNumber != (asking.VertexNumber / 2)))
        {
                msgBox.setText("Incorrect input! If minimal and maximal degree is one - component number should be equal number of vertex, divided by 2. Please, try again.");
                msgBox.exec();
                emit on_NewGrathButton_clicked();
                return;
        }


        if((asking.ComponentNumber - 1) * (asking.MinDegreeNumber + 1)  + asking.MaxDegreeNumber + 1 > asking.VertexNumber)
        {
            msgBox.setText("Incorrect input! Number of vertex too small. Such grath is impossible. Try again.");
            msgBox.exec();
            emit on_NewGrathButton_clicked();
            return;
        }

        if(2 * asking.EdgesNumber > ((asking.VertexNumber - 1) * asking.MaxDegreeNumber + asking.MinDegreeNumber))
        {
            msgBox.setText("Incorrect input! Too much edges for this set of start conditions. Such grath is impossible. Try again.");
            msgBox.exec();
            emit on_NewGrathButton_clicked();
            return;
        }
        if(2 * asking.EdgesNumber < (asking.VertexNumber - 1) * asking.MinDegreeNumber + asking.MaxDegreeNumber)
        {
            msgBox.setText("Incorrect input! Too few edges for this set of start conditions. Such grath is impossible. Try again.");
            msgBox.exec();
            emit on_NewGrathButton_clicked();
            return;
        }

        for(int i=0; i < 100; i++)
            for(int j=0; j<100; j++)
                ui->graphWidget->conmat[i][j] = 0;
        int deg[asking.VertexNumber];
        ui->graphWidget->vertex = asking.VertexNumber;
        int difdeg  = asking.MaxDegreeNumber - asking.MinDegreeNumber;
        int flag = 0, max_bor = 0, min_bor = asking.VertexNumber;
        int sumdeg = asking.EdgesNumber;
        if(difdeg != 0)
        {
            sumdeg  = (2*asking.EdgesNumber - asking.VertexNumber * asking.MinDegreeNumber)/difdeg;
            min_bor = (asking.MinDegreeNumber + 1)*std::min((asking.VertexNumber - sumdeg - 1)/(asking.MinDegreeNumber + 1), asking.ComponentNumber - 1);
            max_bor = (asking.MaxDegreeNumber + 1)*std::min((asking.ComponentNumber - min_bor/(asking.MinDegreeNumber + 1) - 1), (sumdeg+1)/(asking.MaxDegreeNumber + 1));
            flag    = (min_bor == asking.VertexNumber) + (max_bor == 0) * 2;
            min_bor = asking.VertexNumber - min_bor;
            sumdeg  = asking.EdgesNumber - (max_bor * asking.MaxDegreeNumber + (asking.VertexNumber - min_bor) * asking.MinDegreeNumber)/2;
}
        int ver = min_bor - max_bor;

        for(int i = max_bor; i < min_bor; i++)
            deg[i] = 0;


        for(int i = 0; i < max_bor; i++)
            for(int h = 0; h <= asking.MaxDegreeNumber; h++, i++)
                for(int j = h+1; j <= asking.MaxDegreeNumber; j++)
                {
                    ui->graphWidget->conmat[h][j] = 1;
                    ui->graphWidget->conmat[j][h] = 1;
                    deg[h]++;
                    deg[j]++;
                }




 /*       std::cout << std::endl << flag << ' ' << max_bor << ' ' << min_bor << ' ' << sumdeg << ' ' << std::endl;
        for(int h = 0; h < asking.VertexNumber; h++)
            std::cout << int(deg[h]) << ' ';
        std::cout << std::endl;
        for(int h = 0; h < asking.VertexNumber; h++, std::cout << std::endl)
            for(int i = 0; i < asking.VertexNumber; i++)
                    std::cout << int(conmat[h][i]); */


        if(flag / 2 != 0)
        {
                for(int j = 1; j <= asking.MaxDegreeNumber; j++)
                {
                    ui->graphWidget->conmat[max_bor][(max_bor+j)]++;
                    ui->graphWidget->conmat[(max_bor+j)][max_bor]++;
                    deg[max_bor]++;
                    deg[j]++;
                    sumdeg --;
                }
            max_bor++;
        }
        if(flag % 2 != 0)
        {
             min_bor--;
                for(int j = 1; j <= asking.MinDegreeNumber; j++)
                {
                    ui->graphWidget->conmat[min_bor][(min_bor - j)]++;
                    ui->graphWidget->conmat[(min_bor-j)][min_bor]++;
                    deg[min_bor]++;
                    deg[(min_bor-j)]++;
                    sumdeg --;
                }
        }

/*
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl << flag << ' ' << max_bor << ' ' << min_bor << ' ' << sumdeg << ' ' << std::endl;
        for(int h = 0; h < asking.VertexNumber; h++)
            std::cout << int(deg[h]) << ' ';
        std::cout << std::endl;
        for(int h = 0; h < asking.VertexNumber; h++, std::cout << std::endl)
            for(int i = 0; i < asking.VertexNumber; i++)
                    std::cout << int(conmat[h][i]);


        for(int i = max_bor; i < min_bor; i++)
            for(int j = 1; deg[i] < asking.MinDegreeNumber; j++)
            {
                conmat[i][(max_bor+(i+j - max_bor)%ver)]++;
                conmat[(max_bor+(i+j - max_bor)%ver)][i]++;
                deg[i]++;
                deg[(max_bor+(i+j - max_bor)%ver)]++;
                sumdeg --;
            }
        */

        for(int h = 0; sumdeg > 0; h++)
            for(int i = max_bor + ((h + 1) % 2); i < min_bor && sumdeg != 0; i++)
                for(int j = 1; (deg[i] < asking.MinDegreeNumber + h) && sumdeg != 0; j++)
                    if(deg[(max_bor+(i+j - max_bor)%ver)] < asking.MaxDegreeNumber && ui->graphWidget->conmat[i][(max_bor+(i+j - max_bor)%ver)] == 0)
                    {
                        ui->graphWidget->conmat[i][(max_bor+(i+j - max_bor)%ver)]++;
                        ui->graphWidget->conmat[(max_bor+(i+j - max_bor)%ver)][i]++;
                        deg[i]++;
                        deg[(max_bor+(i+j - max_bor)%ver)]++;
                        sumdeg --;
                    }
/*
        for(int h = 0; h < asking.VertexNumber; h++)
            std::cout << int(deg[h]) << ' ';
        std::cout << std::endl;
        for(int h = 0; h < asking.VertexNumber; h++, std::cout << std::endl)
            for(int i = 0; i < asking.VertexNumber; i++)
                    std::cout << int(conmat[h][i]);

        std::cout << std::endl << flag << ' ' << max_bor << ' ' << min_bor << ' ' << sumdeg << ' ' << std::endl;

*/

//        QPixmap* pixDraw = new QPixmap;



    }

    else
    {
        asking.VertexNumber    = 5;
        asking.EdgesNumber     = 10;
        asking.ComponentNumber = 1;
        asking.MaxDegreeNumber = 4;
        asking.MinDegreeNumber = 4;
    }
}

void MainWindow::on_SaveGrathButton_clicked()
{
    QString filePath;

    filePath = QFileDialog::getSaveFileName( this, tr( "Save file" ), ".", tr( "Bitmap (*.bmp)" ) );
    if( !filePath.isEmpty() )
        emit sendSaveFilePath( filePath );
}
