#ifndef QTGDATAIAUTHENTICATION_H
#define QTGDATAIAUTHENTICATION_H

#include <QVariant>

class IAuthentication
{
public:
    virtual QVariant getAuthentication() = 0;
};

#endif // QTGDATAIAUTHENTICATION_H
