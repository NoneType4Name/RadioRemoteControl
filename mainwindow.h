#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "uart.hxx"
#include <QMainWindow>
#include <QKeyEvent>
#include <QSet>
#include <thread>

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
    int8_t pos[ 2 ] { 0, 0 };
    std::thread th;
    bool mayThWork { 1 };
    friend void dummy( MainWindow *wnd );
    QTimer *m_timer;
    QSet<int> m_pressedKeys;
    Qt::KeyboardModifiers modifiers;

  private slots:
    void onTimerTimeout();
    void keyPressEvent( QKeyEvent *event );
    void keyReleaseEvent( QKeyEvent *event );
    void on_pushButton_w_pressed();
    void on_pushButton_s_pressed();
    void on_pushButton_pressed();
};

void dummy( MainWindow *wnd );

#endif // MAINWINDOW_H
