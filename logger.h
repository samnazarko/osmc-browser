/*
 * (c) 2014-2015 Sam Nazarko
 * email@samnazarko.co.uk
*/

#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QStringList>
#include "logger.h"

class Logger
{
public:
    Logger();
    void addLine(QString line);
    QStringList getLog() { return log; }
private:
    QStringList log;
    Logger *logger;
};

#endif // LOGGER_H
