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
      m_preNum(QRandomGenerator::global()->bounded(9))
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
    QGridLayout *glayout = new QGridLayout;
    for(int row = 0; row < 3; row++) {
        for(int col = 0; col < 3; col++) {
            qDebug() << col + row * 3;
            m_btns[col + row * 3] = new Button(col + row * 3,this);
            m_btns[col + row * 3]->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            connect(m_btns[col + row * 3],&QToolButton::clicked,this,&MainWindow::onClicked);
            glayout->addWidget(m_btns[col + row * 3], row, col);
        }
    }
    centralWidget->setLayout(glayout);
    m_timer.setInterval(1000);
    connect(&m_timer,&QTimer::timeout,this,&MainWindow::onTimeout);
    QToolBar *toolBar = new QToolBar(this);
    addToolBar(toolBar);
    QAction *action_start = new QAction("Start",this);
    toolBar->addAction(action_start);
    connect(action_start,&QAction::triggered,[&]{
        m_timer.start();
    });
}

void MainWindow::onClicked()
{
    Button *btn = dynamic_cast<Button *>(sender());
    if(btn->getFlag() == m_preBtn->getFlag())
    {
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

