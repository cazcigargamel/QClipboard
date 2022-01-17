#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    newAction = new QAction(QIcon(QPixmap(":/files/images/new.png")), "New", this);
    toolBar = new QToolBar(this);
    toolBar->addAction(newAction);
    addToolBar(Qt::ToolBarArea::RightToolBarArea, toolBar);
}

MainWindow::~MainWindow()
{
}

