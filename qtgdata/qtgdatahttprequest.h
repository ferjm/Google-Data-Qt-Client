#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QMultiMap>
#include <QUrl>
#include <QPair>
#include <QNetworkRequest>

class HttpRequest : public QObject
{
    Q_OBJECT

public:
    explicit HttpRequest(QObject *parent = 0);

    enum RequestHttpMethod { GET, POST, PUT, HEAD, DELETE };
    typedef QList<QPair<QNetworkRequest::KnownHeaders,QVariant> > HttpHeaders;

    virtual bool isValid() const;

    void setHttpMethod(HttpRequest::RequestHttpMethod httpMethod = HttpRequest::POST);
    void setRequestEndpoint(QUrl requestEndpoint);
    void setRequestBody(QByteArray body);
    void setRequestBody(QMultiMap<QString, QString> body);

    HttpRequest::RequestHttpMethod getHttpMethod();
    QUrl getRequestEndpoint();
    QByteArray getRequestBody() const;

private:
    QUrl requestEndpoint;
    HttpRequest::RequestHttpMethod httpMethod;
    QByteArray requestBody;
};

#endif // HTTPREQUEST_H
