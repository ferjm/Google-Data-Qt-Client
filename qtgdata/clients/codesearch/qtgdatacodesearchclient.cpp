#include "qtgdatacodesearchclient.h"

QtgdataCodeSearchClient::QtgdataCodeSearchClient(IAuthentication *auth, int version, QObject *parent) :
    QtgdataClient(version,parent)
{
    setAuthenticationData(auth);
}

void QtgdataCodeSearchClient::query(QStringList keywords)
{
    QList<QPair<QByteArray,QByteArray> > headers;
    headers.append(qMakePair(QByteArray("GData-Version"),QByteArray::number(this->version)));
    QString url("https://www.google.com/codesearch/feeds/search?q=");
    for(int i=0; i<keywords.size(); i++)
        url += keywords.at(i) + "+";
    sendClientRequest(HttpRequest::GET,
                      QUrl(url),
                      headers,
                      NULL);
}
