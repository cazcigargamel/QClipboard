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
    copyAction = new QAction(QIcon(QPixmap(":/files/images/page_copy.png")), "Copy", this);
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
    toolBar->addAction(copyAction);
    toolBar->addAction(cutAction);
    toolBar->addAction(pasteAction);
    toolBar->addAction(deleteAction);

    addToolBar(Qt::ToolBarArea::RightToolBarArea, toolBar);

    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    connect(newAction, &QAction::triggered, this, &MainWindow::handleNew);
    connect(openAction, &QAction::triggered, this, &MainWindow::handleOpen);
    connect(saveAction, &QAction::triggered, this, &MainWindow::handleSave);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::handleSaveAs);
    connect(startAction, &QAction::triggered, this, &MainWindow::handleStart);
    connect(stopAction, &QAction::triggered, this, &MainWindow::handleStop);
    connect(copyAction, &QAction::triggered, this, &MainWindow::handleCopy);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::handleDelete);

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
    if(!m_changed) return;
    QMessageBox::StandardButton btn = QMessageBox::question(this, "Save Changes","Would like to save your changes");
    if(btn == QMessageBox::StandardButton::Yes) handleSave();
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
    checkedSaved();
    QString tmp;
    tmp = QFileDialog::getOpenFileName(this, "Open File");
    if(tmp.isEmpty()) return;

    m_path = tmp;
    m_list.clear();

    QFile file(m_path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }
    QTextStream stream(&file);
    while(!stream.atEnd())
    {
        m_list.append(stream.readLine());
    }
    file.close();
    m_changed = false;
    m_model.setStringList(m_list);
    statusBar->showMessage("Opened", 2000);
}

void MainWindow::handleSave()
{
    QFile file(m_path);
    if(m_path.isEmpty())
    {
        handleSaveAs();
        return;
    }
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }

    QTextStream stream(&file);
    foreach(QString line, m_list)
    {
        stream << line << "/r/n";
    }
    file.close();
    m_changed = false;
    statusBar->showMessage("Opened", 2000);
}

void MainWindow::handleSaveAs()
{
    QString tmp = QFileDialog::getSaveFileName(this, "Save File");
    if(tmp.isEmpty()) return;

    m_path = tmp;
    handleSave();
}

void MainWindow::handleStart()
{
    m_timer.start();
    statusBar->showMessage("Start", 2000);
}

void MainWindow::handleStop()
{
    m_timer.stop();
    statusBar->showMessage("Stop", 2000);
}

void MainWindow::handleCopy()
{
    QClipboard *clipboard = QApplication::clipboard();
    int index = listView->currentIndex().row();
    clipboard->setText(m_list.at(index));
    statusBar->showMessage("Copied", 2000);
}

void MainWindow::handleCut()
{
    QClipboard *clipboard = QApplication::clipboard();
    int index = listView->currentIndex().row();
    m_list.removeAt(index);
    m_model.setStringList(m_list);
    m_changed = true;
    clipboard->setText(m_list.at(index));
    statusBar->showMessage("Cut", 2000);
}

void MainWindow::handlePaste()
{
    timeout();
}

void MainWindow::handleDelete()
{
    int index = listView->currentIndex().row();
    m_list.removeAt(index);
    m_model.setStringList(m_list);
    m_changed = true;
    statusBar->showMessage("Delete", 2000);
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<< "dfasd";
}

void MainWindow::timeout()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString data = clipboard->text();
    if(data.compare(this->m_last))
    {
        m_last = data;
        qDebug()<< "YES: ";
        if(!m_list.contains(m_last))
        {
            m_list.append(m_last);
            m_model.setStringList(m_list);
            statusBar->showMessage("Added form the clipboard", 2000);
        }
    }
}
