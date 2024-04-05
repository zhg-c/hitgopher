#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QWidget>
#include <QDebug>
#include <QRandomGenerator>
#include <QToolBar>
#include <QAction>
#include <QEventLoop>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_preBtn(nullptr),
      m_preNum(QRandomGenerator::global()->bounded(9)),
      m_tSets(std::make_tuple(3,3,1000))
{
    ui->setupUi(this);
    InitDlg();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitDlg()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    m_glayout = new QGridLayout;
    InitBtns();
    centralWidget->setLayout(m_glayout);
    m_timer.setInterval(1000);
    connect(&m_timer,&QTimer::timeout,this,&MainWindow::onTimeout);
    QToolBar *toolBar = new QToolBar(this);
    addToolBar(toolBar);
    QAction *action_start = new QAction("开始",this);
    toolBar->addAction(action_start);
    connect(action_start,&QAction::triggered,[&]{
        m_timer.start();
    });
    QAction *action_setting = new QAction("设置",this);
    toolBar->addAction(action_setting);
    connect(action_setting,&QAction::triggered,[&]{
        m_timer.stop();
        m_preBtn = nullptr;
        m_settingDlg->setSettings(m_tSets);
        m_settingDlg->exec();
    });
    m_settingDlg = new SettingDlg(this);
    connect(m_settingDlg,&SettingDlg::settings,this,&MainWindow::onSettings);
}

void MainWindow::InitBtns()
{
    for(size_t i = 0;i < m_btns.size();i++)
    {
        delete m_btns[i];
    }
    m_btns.clear();
    for(int row = 0; row < std::get<0>(m_tSets); row++) {
        for(int col = 0; col < std::get<1>(m_tSets); col++) {
             qDebug() << (col + row * std::get<1>(m_tSets));
            m_btns.emplace_back(new Button(col + row * std::get<1>(m_tSets)));
            m_btns[col + row * std::get<1>(m_tSets)]->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            connect(m_btns[col + row * std::get<1>(m_tSets)],&QToolButton::clicked,this,&MainWindow::onClicked);
            m_glayout->addWidget(m_btns[col + row * std::get<1>(m_tSets)], row, col);
        }
    }
}

void MainWindow::InitTimer()
{
    m_timer.setInterval(std::get<2>(m_tSets));
}

void MainWindow::onClicked()
{
    if(!m_preBtn)
    {
        return;
    }
    Button *btn = dynamic_cast<Button *>(sender());
    if(btn->getFlag() == m_preBtn->getFlag())
    {
        btn->setEnabled(false);
        m_timer.stop();
        m_preBtn->setStyleSheet("QToolButton { border-image: url(:/res/hited.jfif); }");
        m_preBtn->repaint();
        QEventLoop loop;
        QTimer::singleShot(1000,[&]{loop.quit();});
        loop.exec();
        m_preBtn->setStyleSheet("QToolButton { border-image: none; }");
        m_preBtn->repaint();
        onTimeout();
        m_timer.start();
        btn->setEnabled(true);
    }
}

void MainWindow::onTimeout()
{
    if(m_preBtn)
    {
        m_preBtn->setStyleSheet("QToolButton { border-image: none; }");
        m_preBtn->repaint();
        m_preBtn = nullptr;
        int num = m_preNum;
        do {
            num = QRandomGenerator::global()->bounded(9);
        } while (num == m_preNum);
        m_preNum = num;
    }
    m_preBtn =m_btns[m_preNum];
    m_preBtn->setStyleSheet("QToolButton { border-image: url(:/res/show.jfif); }");
    m_preBtn->repaint();
}

void MainWindow::onSettings(const std::tuple<int, int,int> &tSets)
{
    m_tSets = tSets;
    InitBtns();
    InitTimer();
}

