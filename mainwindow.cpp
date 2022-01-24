#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    newAction = new QAction(QIcon(QPixmap(":/files/images/new.png")), "New", this);
    openAction = new QAction(QIcon(QPixmap(":/files/images/open.png")), "Open", this);
    saveAction = new QAction(QIcon(QPixmap(":/files/images/save.png")), "Save", this);
    saveAsAction = new QAction(QIcon(QPixmap(":/files/images/save_as.png")), "SaveAs", this);
    /////////////////////////////
    startAction = new QAction(QIcon(QPixmap(":/files/images/control_play_blue.png")), "Start", this);
    stopAction = new QAction(QIcon(QPixmap(":/files/images/control_stop_blue.png")), "Stop", this);
    ////////////////////////////
    copyAsAction = new QAction(QIcon(QPixmap(":/files/images/page_copy.png")), "Copy", this);
    cutAction = new QAction(QIcon(QPixmap(":/files/images/cut.png")), "Cut", this);
    pasteAction = new QAction(QIcon(QPixmap(":/files/images/page_paste.png")), "Paste", this);
    deleteAction = new QAction(QIcon(QPixmap(":/files/images/delete.png")), "Delete", this);

    toolBar = new QToolBar(this);
    toolBar->addAction(newAction);
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(saveAsAction);
    toolBar->addSeparator();
    toolBar->addAction(startAction);
    toolBar->addAction(stopAction);
    toolBar->addSeparator();
    toolBar->addAction(copyAsAction);
    toolBar->addAction(cutAction);
    toolBar->addAction(pasteAction);
    toolBar->addAction(deleteAction);

    addToolBar(Qt::ToolBarArea::RightToolBarArea, toolBar);

    connect(newAction, &QAction::triggered, this, &MainWindow::handleNew);
    connect(openAction, &QAction::triggered, this, &MainWindow::handleOpen);

    listView = new QListView(this);
    setCentralWidget(listView);

    init();
}

MainWindow::~MainWindow()
{
}

void MainWindow::init()
{
    m_changed = false;
    m_path = "";
    m_model.setStringList(m_list);
    listView->setModel(&m_model);
    connect(&m_timer, &QTimer::timeout, this, &MainWindow::timeout);
    m_timer.setInterval(500);
    m_timer.start();

}

void MainWindow::checkedSaved()
{

}

void MainWindow::handleNew()
{
    checkedSaved();
    m_list.clear();
    m_path.clear();
    m_changed = false;
    m_model.setStringList(m_list);
}

void MainWindow::handleOpen()
{
//    checkedSaved();
//    m_list.clear();
//    m_path = QFileDialog::getOpenFileName(this, "Open File");
//    if(m_path.isEmpty()) return;
//    QFile file(m_path);
//    if(!file.open(QIODevice::ReadOnly))
//    {
//        QMessageBox::critical(this, "Error", file.errorString());
//        return;
//    }
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<< "dfasd";
}

void MainWindow::timeout()
{

}
