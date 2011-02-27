#include "qtgdatahttprequest.h"

HttpRequest::HttpRequest(QObject *parent) :
    QObject(parent)
{
    httpMethod = HttpRequest::POST;
}

void HttpRequest::setHttpMethod(HttpRequest::RequestHttpMethod httpMethod)
{
    this->httpMethod = httpMethod;
}

HttpRequest::RequestHttpMethod HttpRequest::getHttpMethod()
{
    return this->httpMethod;
}

void HttpRequest::setRequestEndpoint(QUrl requestEndpoint)
{
    this->requestEndpoint = requestEndpoint;
}

QUrl HttpRequest::getRequestEndpoint()
{
    return this->requestEndpoint;
}

void HttpRequest::setRequestBody(QByteArray body)
{
    this->requestBody = body;
}

void HttpRequest::setRequestBody(QMultiMap<QString, QString> body)
{
    QList<QString> postBodyKeys = body.keys();
    QList<QString> postBodyValues = body.values();

    requestBody.clear();
    bool first = true;
    for(int i=0; i<postBodyKeys.size(); i++)
    {
        if(!first)
        {
            requestBody.append("&");
        }
        else
        {
            first = false;
        }
        QString key = postBodyKeys.at(i);
        QString value = postBodyValues.at(i);
        requestBody.append(QUrl::toPercentEncoding(key) + QString("=").toUtf8() +
                               QUrl::toPercentEncoding(value));
    }
}

QByteArray HttpRequest::getRequestBody() const
{
    return requestBody;
}

bool HttpRequest::isValid() const
{
    return(requestEndpoint.isValid());

}

