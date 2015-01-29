/*
 * (c) 2014-2015 Sam Nazarko
 * email@samnazarko.co.uk
*/

#include "logger.h"
#include <QDateTime>
#include <QFile>
#include <QDebug>

Logger::Logger()
{
}

void Logger::addLine(QString line)
{
    QDateTime timestamp = QDateTime::currentDateTime();
    qDebug() << timestamp.toString() << " " << line;
    log.append(timestamp.toString() + " " + line + "\n");
    fflush(stdout);
}
