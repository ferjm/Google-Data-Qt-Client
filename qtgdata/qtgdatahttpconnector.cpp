/***************************************************************************
 *   Copyright (C) 2010 Fernando Jiménez Moreno <ferjmoreno@gmail.com>     *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <QDebug>
#include <QNetworkAccessManager>
#include <QEventLoop>

#include "qtgdatahttpconnector.h"

HttpConnectorException::HttpConnectorException(const QString &what) : _what(what)        
{    
}

const char* HttpConnectorException::what() const throw()
{
    QString retval = "HttpConnectorException: " + _what;
    return retval.toAscii();
}

HttpConnector::HttpConnector()
{   
    manager = new QNetworkAccessManager();
}

HttpConnector::~HttpConnector()
{
    delete manager;
}

void HttpConnector::httpRequest(HttpMethod httpMethod,
                                QUrl url,
                                HttpHeaders httpHeaders,
                                const QByteArray &data)
{                    
    replyData.clear();
    QNetworkRequest request(url);
    HttpHeaders::const_iterator it = httpHeaders.begin();
    for(;it != httpHeaders.end(); it++)
        request.setHeader((*it).first,(*it).second);    
    QEventLoop *loop = new QEventLoop;
    switch(httpMethod)
    {
    case GET:
        reply = manager->get(request);                
        break;
    case POST:
        reply = manager->post(request,data);
        break;
    case PUT:
        reply = manager->put(request,data);
        break;
    case HEAD:
        reply = manager->head(request);
        break;
    case DELETE:
        reply = manager->deleteResource(request);
        break;
    }
    connect(reply, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply *)),loop, SLOT(quit()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    loop->exec();
}

void HttpConnector::finished(QNetworkReply *mReply)
{    
    mReply->deleteLater();
}

void HttpConnector::readyRead()
{    
    replyData = reply->readAll();    
#ifdef QTGDATA_DEBUG
    qDebug() << "HTTP Reply: \n\t" << replyData;
#endif
    //TODO: parse replyData and return IEntity body + header
    emit requestFinished(replyData);
}

void HttpConnector::error(QNetworkReply::NetworkError errorCode)
{    
    QString errorCodeStr;
    switch(errorCode)
    {
    case QNetworkReply::NoError:
        break;
    case QNetworkReply::ConnectionRefusedError:
    case QNetworkReply::RemoteHostClosedError:
    case QNetworkReply::HostNotFoundError:
    case QNetworkReply::TimeoutError:
    case QNetworkReply::OperationCanceledError:
    case QNetworkReply::SslHandshakeFailedError:
    case QNetworkReply::TemporaryNetworkFailureError:
    case QNetworkReply::UnknownNetworkError:
        errorCodeStr = "Network layer error [relating to the destination server]";
        break;
    case QNetworkReply::ProxyConnectionRefusedError:
    case QNetworkReply::ProxyConnectionClosedError:
    case QNetworkReply::ProxyNotFoundError:
    case QNetworkReply::ProxyTimeoutError:
    case QNetworkReply::ProxyAuthenticationRequiredError:
    case QNetworkReply::UnknownProxyError:
        errorCodeStr = "Proxy error";
        break;
    case QNetworkReply::ContentAccessDenied:
    case QNetworkReply::ContentOperationNotPermittedError:
    case QNetworkReply::ContentNotFoundError:
    case QNetworkReply::AuthenticationRequiredError:
    case QNetworkReply::ContentReSendError:
    case QNetworkReply::UnknownContentError:
        errorCodeStr = "Content error";
        break;
    case QNetworkReply::ProtocolUnknownError:
    case QNetworkReply::ProtocolInvalidOperationError:
    case QNetworkReply::ProtocolFailure:
        errorCodeStr = "Protocol error";
        break;
    }
#ifdef QTGDATA_DEBUG
    qDebug() << "NetworkError: " << errorCodeStr;
#endif
    throw HttpConnectorException(QString("NetworkError: " + errorCodeStr));
}
