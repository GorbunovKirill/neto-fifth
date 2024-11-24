#include "stopwatch.h"
#include <QDebug>

Stopwatch::Stopwatch() : currentTime(0), running(false), lapCount(0)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stopwatch::updateTime);
}

Stopwatch::~Stopwatch()
{
    delete timer;
}

void Stopwatch::startStop()
{
    if (running) {
        timer->stop();
    } else {
        timer->start(100);
    }
    running = !running;
    emit runningStateChanged(running);
}

void Stopwatch::reset()
{
    timer->stop();
    currentTime = 0;
    lapCount = 0;
    running = false;
    emit timeUpdated(0, 0, 0);
    emit runningStateChanged(false);
}

void Stopwatch::lap()
{
    lapCount++;
    int minutes = static_cast<int>(currentTime) / 60;
    int seconds = static_cast<int>(currentTime) % 60;
    int milliseconds = static_cast<int>((currentTime - static_cast<int>(currentTime)) * 100);
    emit lapTimeUpdated(QString("Lap %1, time: %2:%3.%4")
                            .arg(lapCount)
                            .arg(minutes, 2, 10, QLatin1Char('0'))
                            .arg(seconds, 2, 10, QLatin1Char('0'))
                            .arg(milliseconds, 2, 10, QLatin1Char('0')));
}

void Stopwatch::updateTime()
{
    currentTime += 0.1;
    int minutes = static_cast<int>(currentTime) / 60;
    int seconds = static_cast<int>(currentTime) % 60;
    int milliseconds = static_cast<int>((currentTime - static_cast<int>(currentTime)) * 100);
    emit timeUpdated(minutes, seconds, milliseconds);
}

float Stopwatch::getTime() const
{
    return currentTime;
}
