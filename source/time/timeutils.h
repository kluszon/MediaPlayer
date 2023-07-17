#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <QObject>
#include <QTime>

class TimeUtils : public QObject
{
    Q_OBJECT
public:
    explicit TimeUtils(QObject *parent = nullptr);

public slots:
    int timeFromString(QString string, QString format);
    QString timeToString(int value, QString format = "mm:ss:zzz");
};

#endif // TIMEUTILS_H
