#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFontDatabase db;
    QStringList fonts = db.families(QFontDatabase::Cyrillic);
    ui->FontBox->addItems(fonts);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenFileButton_clicked()
{
    QFileDialog dialog(this);
    QString filePath;
    dialog.setFileMode(QFileDialog::AnyFile);
    filePath = QFileDialog::getOpenFileName( this, tr( "Open file" ), ".", tr( "HTML file (*.html)" ) );
    dialog.show();
    QFile html_file(filePath);
    if (!html_file.open(QIODevice::ReadOnly | QIODevice::Text))  // открываем
        qDebug() << "can't open account list";                  //на всякий случай
    else
    {
        ui->HTML_View->clear();
        for(int i=0; !html_file.atEnd(); i++)
        {
            QString str = html_file.readLine();
            ui->HTML_View->insertHtml(str);
        }
    }
}

void MainWindow::on_FontBox_activated(const QString &arg1)
{
    QFont font;
    font.fromString(arg1);
    ui->HTML_View->setFont(font);
    update();
}

void MainWindow::on_FontSizeBox_valueChanged(int arg1)
{
    QFont font;
    font.setPointSize(arg1);
    ui->HTML_View->setFont(font);
    update();
}
