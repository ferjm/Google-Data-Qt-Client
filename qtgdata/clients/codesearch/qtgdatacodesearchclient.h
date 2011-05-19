#ifndef QTGDATACODESEARCHCLIENT_H
#define QTGDATACODESEARCHCLIENT_H

#include "qtgdataclient.h"

class QtgdataCodeSearchClient : public QtgdataClient
{
    Q_OBJECT
public:
    explicit QtgdataCodeSearchClient(IAuthentication *auth, int version = 2, QObject *parent = 0);

    void query(QStringList keywords);

signals:
    virtual void atomFeedRetrievedFinished(AtomFeed);
};

#endif // QTGDATACODESEARCHCLIENT_H
