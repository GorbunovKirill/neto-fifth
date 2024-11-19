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

void MainWindow::updateTimeDisplay(float time)
{
    ui->timeLabel->setText(QString("Time: %1 sec").arg(time));
}

void MainWindow::addLap(const QString &lapTime)
{
    ui->lapBrowser->append(lapTime);
}

void MainWindow::onStartStopClicked()
{
    stopwatch->startStop();
    if (stopwatch->getTime() == 0) {
        ui->startStopButton->setText("Stop");
    } else {
        ui->startStopButton->setText("Start");
    }
    ui->lapButton->setEnabled(stopwatch->getTime() > 0);
}

void MainWindow::onResetClicked()
{
    stopwatch->reset();
    ui->startStopButton->setText("Start");
    ui->lapButton->setEnabled(false);
    ui->lapBrowser->clear();
}

void MainWindow::onLapClicked()
{
    stopwatch->lap();
}
