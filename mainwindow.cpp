#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qnamespace.h>
#include <QTimer>
#include <qobject.h>

MainWindow::MainWindow( uart &ard, QWidget *parent ) :
    QMainWindow( parent ), ui( new Ui::MainWindow ), Serial( ard ), th( dummy, this )
{
    ui->setupUi( this );
    m_timer = new QTimer( this );
    connect( m_timer, &QTimer::timeout, this, &MainWindow::onTimerTimeout );
    m_timer->start( 1 );
}

MainWindow::~MainWindow()
{
    mayThWork = 0;
    th.join();
    delete ui;
}

void MainWindow::keyPressEvent( QKeyEvent *event )
{
    if ( !m_pressedKeys.contains( event->key() ) )
    {
        m_pressedKeys.insert( event->key() );
    }
}

void MainWindow::keyReleaseEvent( QKeyEvent *event )
{
    m_pressedKeys.remove( event->key() );
}

void dummy( MainWindow *wnd )
{
    while ( wnd->mayThWork )
    {
        std::string data { "p" };
        data += wnd->pos[ 0 ] + wnd->pos[ 1 ];
        // wnd->ui->label->setText( data.data() );
        wnd->Serial.writeLine( data );
        data.clear();
        wnd->Serial.readLine( data );
        if ( data.size() )
            continue;
    }
}

void MainWindow::on_pushButton_w_pressed()
{
    if ( pos[ 0 ] < 127 - 5 )
        pos[ 0 ] += 5;
    // ui->label->setText( QString::number( pos[ 0 ] ) );
}

void MainWindow::on_pushButton_s_pressed()
{
    if ( pos[ 0 ] > -128 + 5 )
        pos[ 0 ] -= 5;
}

void MainWindow::on_pushButton_pressed()
{
    pos[ 0 ] = 0;
    pos[ 1 ] = 0;
}

void MainWindow::onTimerTimeout()
{
    if ( m_pressedKeys.contains( Qt::Key_W ) )
    {
        ui->pushButton_w->click();
    }
    if ( m_pressedKeys.contains( Qt::Key_S ) )
    {
        ui->pushButton_s->click();
    }
    if ( m_pressedKeys.contains( Qt::Key_X ) )
    {
        ui->pushButton->click();
    }
}
