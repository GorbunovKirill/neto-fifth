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
}

void Stopwatch::reset()
{
    currentTime = 0;
    lapCount = 0;
    emit timeUpdated(currentTime);
}

void Stopwatch::lap()
{
    lapCount++;
    float lapTime = currentTime;
    emit lapTimeUpdated(QString("Lap %1, time: %2 sec").arg(lapCount).arg(lapTime));
}

void Stopwatch::updateTime()
{
    currentTime += 0.1;
    emit timeUpdated(currentTime);
}

float Stopwatch::getTime() const
{
    return currentTime;
}
