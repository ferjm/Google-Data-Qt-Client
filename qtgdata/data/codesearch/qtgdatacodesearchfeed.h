#ifndef QTGDATACODESEARCHFEED_H
#define QTGDATACODESEARCHFEED_H

#include "common/qtgdataatomentry.h"

class Match
{
    QString type;
    QString lineNumber;
};

class Package
{
    QString name;
    QUrl uri;
};

class CodeSearchFeed : public AtomFeed
{
    QString file;
    Match match;
    Package package;
};

#endif // QTGDATACODESEARCHFEED_H
