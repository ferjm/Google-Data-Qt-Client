#ifndef QTGDATACODESEARCHCLIENT_H
#define QTGDATACODESEARCHCLIENT_H

#include "qtgdataclient.h"

class QtgdataCodeSearchClient : public QtgdataClient
{
    Q_OBJECT
public:
    explicit QtgdataCodeSearchClient(IAuthentication *auth, int version = 2, QObject *parent = 0);

signals:

public slots:

};

#endif // QTGDATACODESEARCHCLIENT_H
