
#include "PaintWindow.h"
#include "PaintWidget.h"

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

int PaintWindow::width_ = 500;
int PaintWindow::height_ = 500;

PaintWindow::PaintWindow(){
    lastFile = "";

    paintWidget = new PaintWidget;

    setCentralWidget( paintWidget );

    mainToolBar = new QToolBar( tr( "Drawing Tools" ), this );
    mainToolBar -> setMovable( false );
    createMainToolBar();

    createFileMenu();

    colorMenu = menuBar() -> addMenu( tr( "Color" ) );
    pickColorAction = new QAction( tr( "Pick color..." ), this );
    pickColorAction -> setStatusTip( tr( "Pick color" ) );
    colorMenu -> addAction( pickColorAction );

    connect( this, SIGNAL( changeTool( int ) ), paintWidget, SLOT( setSelectedTool( int ) ) );
    connect( this, SIGNAL( changePolygonSides( int ) ), paintWidget, SLOT( setNSides( int ) ) );
    connect( saveFileAs, SIGNAL( triggered() ), this, SLOT( getSaveFilePath() ) );
    connect( this, SIGNAL( sendSaveFilePath( const QString& ) ), paintWidget, SLOT( saveToFile( const QString& ) ) );
    connect( paintWidget, SIGNAL( resetFilePath() ), this, SLOT( resetFilePath() ) );
    connect( pickColorAction, SIGNAL( triggered() ), this, SLOT( pickColor() ) );
    connect( this, SIGNAL( sendColor( const QColor& ) ), paintWidget, SLOT( setColor( const QColor& ) ) );

}

int PaintWindow::width(){
    return width_;
}

int PaintWindow::height(){
    return height_;
}

void PaintWindow::setWidth( int w ){
    width_ = w;
}

void PaintWindow::setHeight( int h ){
    height_ = h;
}

void PaintWindow::lineSelected(){
    emit changeTool( PaintWindow::Line );
}

void PaintWindow::ellipseSelected(){
    emit changeTool( PaintWindow::Ellipse );
}

void PaintWindow::pencilSelected(){
    emit changeTool( PaintWindow::Pencil );
}


void PaintWindow::getSaveFilePath(){
    QString filePath;

    filePath = QFileDialog::getSaveFileName( this, tr( "Save file" ), ".", tr( "Bitmap (*.bmp)" ) );

    if( !filePath.isEmpty() ){
        lastFile = filePath;
        emit sendSaveFilePath( filePath );
    }
}

void PaintWindow::resetFilePath(){
    lastFile = "";
}

void PaintWindow::pickColor(){
    QColor color;

    color = QColorDialog::getColor( QColor( 255, 255, 255 ), this, tr( "Pick color" ) );
    emit sendColor( color );
}

void PaintWindow::createMainToolBar(){
    addToolBar( Qt::LeftToolBarArea, mainToolBar );
    lineToolAction = new QAction(tr( "Line" ),this);
    lineToolAction -> setStatusTip( tr( "Draw line" ) );
    connect( lineToolAction, SIGNAL( triggered() ), this, SLOT( lineSelected() ) );
    mainToolBar -> addAction( lineToolAction );

    ellipseToolAction = new QAction(tr( "Ellipse" ), this );
    ellipseToolAction -> setStatusTip( tr( "Draw ellipse" ) );
    connect( ellipseToolAction, SIGNAL( triggered() ), this, SLOT( ellipseSelected() ) );
    mainToolBar -> addAction( ellipseToolAction );

    pencilToolAction = new QAction(tr( "Pencil" ), this );
    pencilToolAction -> setStatusTip( tr( "Pencil tool" ) );
    connect( pencilToolAction, SIGNAL( triggered() ), this, SLOT( pencilSelected() ) );
    mainToolBar -> addAction( pencilToolAction );
}

void PaintWindow::createFileMenu(){
    fileMenu = menuBar() -> addMenu( tr( "File" ) );
    saveFileAs = new QAction( tr( "Save as..." ), this );
    saveFileAs -> setStatusTip( tr( "Save file as..." ) );
    saveFileAs -> setShortcut( QKeySequence::SaveAs );
    fileMenu -> addAction( saveFileAs );
}
