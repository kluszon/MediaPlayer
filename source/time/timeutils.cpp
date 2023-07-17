#include "timeutils.h"
#include <QDebug>

TimeUtils::TimeUtils(QObject *parent) : QObject(parent)
{

}

int TimeUtils::timeFromString(QString string, QString format)
{
    QTime result = QTime::fromString(string, format);
    if(!result.isValid()){
        return -1;
    }

    return result.msecsSinceStartOfDay();
}

QString TimeUtils::timeToString(int value, QString format)
{
    QTime time = QTime::fromMSecsSinceStartOfDay(value);

    return time.toString(format);
}
