#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qobject.h>
#include <synchapi.h>

MainWindow::MainWindow( uart &ard, QWidget *parent ) : QMainWindow( parent ), ui( new Ui::MainWindow ), Serial( ard )
{
    ui->setupUi( this );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_editingFinished()
{
    Serial.writeLine( ui->lineEdit->text().toStdString() );
    ui->lineEdit->clear();
    std::string data;
    Serial.readLine( data );
    ui->listWidget->addItem( QString( data.c_str() ) );
}
