#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stopwatch.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateTimeDisplay(int minutes, int seconds, int milliseconds);
    void addLap(const QString &lapTime);
    void updateButtonStates(bool running);
    void onStartStopClicked();
    void onResetClicked();
    void onLapClicked();

private:
    Ui::MainWindow *ui;
    Stopwatch *stopwatch;
};

#endif // MAINWINDOW_H
