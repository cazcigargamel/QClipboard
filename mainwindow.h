#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QPixmap>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QAction *newAction = nullptr;
    QAction *openAction = nullptr;
    QAction *saveAction = nullptr;
    QAction *saveAsAction = nullptr;
    QAction *startAction = nullptr;
    QAction *stopAction = nullptr;
    QAction *copyAsAction = nullptr;
    QAction *cutAction = nullptr;
    QAction *pasteAction = nullptr;
    QAction *deleteAction = nullptr;

    QToolBar *toolBar = nullptr;


};
#endif // MAINWINDOW_H
