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

#include "qtgdatabloggerclient.h"
#include "qtgdataoauthrequest.h"
#include "qtgdataxmlparser.h"

#include <QDebug>

#define BLOGGER_FEEDS "http://www.blogger.com/feeds/"

QtgdataBloggerClient::QtgdataBloggerClient(IAuthentication *auth, int version, QObject *parent) :
    QtgdataClient(version,parent)
{
    setAuthenticationData(auth);
}

void QtgdataBloggerClient::retrieveListOfBlogs(QString profileID)
{
    HttpRequest *request = authenticatedRequest();
    request->setRequestEndpoint(QUrl(QString(BLOGGER_FEEDS) + profileID +"/blogs"));    
    request->setHttpMethod(HttpRequest::GET);
    request->setHeader(QByteArray("GData-Version"),QByteArray::number(this->version));
    request->setAuthHeader();
    connect(&(this->httpConnector), SIGNAL(requestFinished(QByteArray)), this, SLOT(onRetrieveListOfBlogsFinished(QByteArray)));
    this->httpConnector.httpRequest(request);
    delete request;
}

void QtgdataBloggerClient::onRetrieveListOfBlogsFinished(QByteArray reply)
{
#ifdef QTGDATA_DEBUG
    qDebug() << "onRetrieveListOfBlogsFinished";
#endif
    XMLParser parser;
    try {
        IEntity *entity = parser.parse(reply,reply.size());
        delete entity;
    } catch(XMLParserException e) {
        qDebug() << e.what();
    }
}
