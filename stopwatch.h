#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class Stopwatch : public QObject
{
    Q_OBJECT

public:
    Stopwatch();
    ~Stopwatch();

    void startStop();
    void reset();
    void lap();

    float getTime() const;

signals:
    void timeUpdated(int minutes, int seconds, int milliseconds);
    void lapTimeUpdated(const QString &lapTime);
    void runningStateChanged(bool running);

private slots:
    void updateTime();

private:
    QTimer *timer;
    float currentTime;
    bool running;
    int lapCount;
};

#endif
