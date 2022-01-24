#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include <QStringListModel>
#include <QList>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QListView>

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

    QTimer m_timer;
    QString m_last;
    QStringListModel m_model;
    QStringList m_list;
    QString m_path;
    bool m_changed;

    void init();
    void checkedSaved();

    QListView *listView;
    // QWidget interface

private slots:
    void timeout();
    void handleNew();
    void handleOpen();
protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
