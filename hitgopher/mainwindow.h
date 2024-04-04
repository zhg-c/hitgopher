#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "button.h"
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void InitDlg();
private slots:
    void onClicked();
    void onTimeout();
private:
    Ui::MainWindow *ui;
    QTimer m_timer;
    Button *m_btns[9];
    Button *m_preBtn;
    int m_preNum;
};
#endif // MAINWINDOW_H
