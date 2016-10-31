#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QFont>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QFont sansFont("Helvetica [Cronyx]", 14);

    // central panel

    imageLabel = new MyLabel;
    imageLabel->setBackgroundRole(QPalette::Light);
    imageLabel->setMaxTime(100);

    //right panel
    rightPanel = new QLabel;
    rightPanel->setFont(sansFont);
    rightPanel->setBackgroundRole(QPalette::Light);
    rightPanel->setScaledContents(true);
    rightPanel->setFixedWidth(70);
    rightPanel->setFixedHeight(400);

    QLabel *title500 = new QLabel(rightPanel);
    title500->setAttribute(Qt::WA_DeleteOnClose);
    title500->setText(tr("t0 = 500"));
    title500->move(0, 0);

    QLabel *title0 = new QLabel(rightPanel);
    title0->setAttribute(Qt::WA_DeleteOnClose);
    title0->setText(tr("t0 = 0"));
    title0->move(10, 380);

    QSlider *rotation = new QSlider(rightPanel);
    rotation->move(20, 20);
    rotation->setOrientation(Qt::Vertical);
    rotation->setAttribute(Qt::WA_DeleteOnClose);
    rotation->setMinimum(0);
    rotation->setMaximum(1000);
    rotation->setFixedSize(30, 360);
    rotation->setSingleStep(1);
    connect(rotation, SIGNAL(valueChanged(int)), imageLabel, SLOT(setMaxTime(int)));
    rotation->setValue(100);

    // all panel
    layout = new QHBoxLayout;
    layout->addWidget(imageLabel);
    layout->addWidget(rightPanel);

    allPanels = new QWidget(this);
    allPanels->setLayout(layout);
    allPanels->setAttribute(Qt::WA_DeleteOnClose);
    setCentralWidget(allPanels);

    setWindowTitle(tr("Агабябян, задача 21"));
    resize(800, 600);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete imageLabel;
    delete rightPanel;
    delete layout;
    delete allPanels;

}
