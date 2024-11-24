#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stopwatch.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    stopwatch(new Stopwatch)
{
    ui->setupUi(this);

    connect(stopwatch, &Stopwatch::timeUpdated, this, &MainWindow::updateTimeDisplay);
    connect(stopwatch, &Stopwatch::lapTimeUpdated, this, &MainWindow::addLap);
    connect(stopwatch, &Stopwatch::runningStateChanged, this, &MainWindow::updateButtonStates);

    connect(ui->startStopButton, &QPushButton::clicked, this, &MainWindow::onStartStopClicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::onResetClicked);
    connect(ui->lapButton, &QPushButton::clicked, this, &MainWindow::onLapClicked);

    ui->lapButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete stopwatch;
}

void MainWindow::updateTimeDisplay(int minutes, int seconds, int milliseconds)
{
    ui->minutesLabel->setText(QString("%1").arg(minutes, 2, 10, QLatin1Char('0')));
    ui->secondsLabel->setText(QString("%1").arg(seconds, 2, 10, QLatin1Char('0')));
    ui->millisecondsLabel->setText(QString("%1").arg(milliseconds, 2, 10, QLatin1Char('0')));
}

void MainWindow::addLap(const QString &lapTime)
{
    ui->lapBrowser->append(lapTime);
}

void MainWindow::updateButtonStates(bool running)
{
    ui->lapButton->setEnabled(running);
    ui->startStopButton->setText(running ? "Stop" : "Start");
}

void MainWindow::onStartStopClicked()
{
    stopwatch->startStop();
}

void MainWindow::onResetClicked()
{
    stopwatch->reset();
    ui->lapBrowser->clear();
}

void MainWindow::onLapClicked()
{
    stopwatch->lap();
}
