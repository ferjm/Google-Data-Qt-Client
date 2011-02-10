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

#include <sstream>
#include <cstdio>

#include <QDebug>
#include <QNetworkAccessManager>

#include "httpconnector.h"

HttpConnectorException::HttpConnectorException(const QString &what) : _what(what)
{
}

const char* HttpConnectorException::what() const throw()
{
    QString retval = "HttpConnectorException: " + _what;
    return retval.toAscii();
}

void HttpConnector::httpRequest(HttpMethod httpMethod,
                                QUrl url,
                                HttpHeaders httpHeaders,
                                const QByteArray &data)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    switch(httpMethod)
    {
    case GET:
        break;
    case POST:
        break;
    case PUT:
        break;
    case HEAD:
        break;
    default:
        delete manager;
        throw HttpConnectorException("Invalid HTTP method\n");
    }

    delete manager;
}
