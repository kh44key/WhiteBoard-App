#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "whiteboard.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void setPenBlue();
    void setPenRed();
    void setPenGreen();
    void clearScreen();
    void setPenSizeSmall();
    void setPenSizeMedium();
    void setPenSizeLarge();
    void undoAction();
    void redoAction();

protected:
    virtual void keyPressEvent(QKeyEvent* k) override;

private:
    WhiteBoard* m_whiteboard;
};

#endif
