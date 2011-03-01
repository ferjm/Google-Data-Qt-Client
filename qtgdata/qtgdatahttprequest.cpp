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

HttpRequest::RequestHttpMethod HttpRequest::getHttpMethod() const
{
    return this->httpMethod;
}

void HttpRequest::setRequestEndpoint(QUrl requestEndpoint)
{
    this->requestEndpoint = requestEndpoint;
}

QUrl HttpRequest::getRequestEndpoint() const
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

void HttpRequest::setHeader(HttpRequest::HttpHeader header)
{
    this->requestHeaders.append(header);
}

void HttpRequest::setContentTypeHeader(QVariant contentTypeHeader)
{
    HttpHeader h;
    h.first = QNetworkRequest::ContentTypeHeader;
    h.second = contentTypeHeader;
    this->requestHeaders.append(h);
}

HttpRequest::HttpHeaders HttpRequest::getHttpHeaders() const
{
    return requestHeaders;
}
