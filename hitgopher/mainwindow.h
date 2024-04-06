#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "button.h"
#include "settingdlg.h"
#include <QMainWindow>
#include <QTimer>
#include <vector>
#include <QGridLayout>
#include <QMediaPlayer>

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
    void InitBtns();
    void InitTimer();
private slots:
    void onClicked();
    void onTimeout();
    void onSettings(const std::tuple<int,int,int> &tSets);
private:
    Ui::MainWindow *ui;
    QTimer m_timer;
    std::vector<Button *> m_btns;
    Button *m_preBtn;
    int m_preNum;
    std::tuple<int,int,int> m_tSets;
    SettingDlg *m_settingDlg;
    QGridLayout *m_glayout;
    QMediaPlayer *m_player;
};
#endif // MAINWINDOW_H
