#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SavingGraph_clicked()
{
    QString filePath;

    filePath = QFileDialog::getSaveFileName( this, tr( "Save file" ), ".", tr( "Bitmap (*.bmp)" ) );

    emit sendSaveFilePath(filePath);
}

void MainWindow::on_RefreshGraph_clicked()
{

}

void MainWindow::on_graphicsView_sendSaveFilePath(const QString &filePath ){
    FILE* file;
    bmpHeader h1;
    bmpInfoHeader h2;
    PixelInfo* bitmap;

    file = fopen( filePath.toStdString().c_str(), "wb" );
    if( file != NULL ){
        bitmap = new PixelInfo[ rowSize_ * height_ ];
        glPixelStorei( GL_PACK_ALIGNMENT, 4 );
        glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
        glReadPixels( 0, 0, width_, height_, GL_BGR, GL_UNSIGNED_BYTE, bitmap );
        glPixelStorei( GL_PACK_ALIGNMENT, 1 );
        glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

        h2.infoHeaderSize = 40;
        h2.width = width_;
        h2.height = height_;
        h2.nPlanes = 1;
        h2.colorDepth = 24;
        h2.compressionMethod = 0;
        h2.imageSize = width_ * 3;
        while( h2.imageSize % 4 != 0 ){
            h2.imageSize++;
        }
        h2.imageSize *= height_;
        h2.hResolution = 0;
        h2.vResolution = 0;
        h2.nColors = 0;
        h2.nImportantColors = 0;

        h1.signature = 0x4D42;
        h1.fileSize = 14 + sizeof( bmpInfoHeader ) + h2.imageSize;
        h1.reservedField = 0;
        h1.offset = 54;

        fwrite( &h1.signature, sizeof( short ), 1, file );
        fwrite( &h1.fileSize, sizeof( long ), 1, file );
        fwrite( &h1.reservedField, sizeof( long ), 1, file );
        fwrite( &h1.offset, sizeof( long ), 1, file );
        fwrite( &h2, sizeof( bmpInfoHeader ), 1, file );
        fwrite( bitmap, h2.imageSize, 1, file );

        fclose( file );
        delete bitmap;
    }
}
