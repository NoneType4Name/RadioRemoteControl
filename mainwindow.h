#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "uart.hxx"
#include <QMainWindow>
#include <qtmetamacros.h>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow( uart &ard, QWidget *parent = nullptr );
    ~MainWindow();

  private:
    Ui::MainWindow *ui;
    uart &Serial;

  private slots:
    void on_lineEdit_editingFinished();
};
#endif // MAINWINDOW_H
