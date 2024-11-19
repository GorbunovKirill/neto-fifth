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
    void timeUpdated(float time);
    void lapTimeUpdated(const QString &lapTime);

private slots:
    void updateTime();

private:
    QTimer *timer;
    float currentTime;
    bool running;
    int lapCount;
};

#endif // STOPWATCH_H
