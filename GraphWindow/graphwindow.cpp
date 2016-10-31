#include "graphwindow.h"
#include "qgraphwidget.h"
#include "ui_graphwindow.h"

#include <QIcon>
#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <QButtonGroup>
#include <QMenu>
#include <QMenuBar>
#include <QString>
#include <QKeySequence>
#include <QFileDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QColor>

GraphWindow::GraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::on_NewGraphButton_clicked()
{

}

void GraphWindow::on_SaveAsButton_clicked()
{

}
