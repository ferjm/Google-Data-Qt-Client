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

#include "qtgdatacontactsclient.h"
#include "core/qtgdataoauthrequest.h"
#include "core/qtgdataxmlparser.h"

#include <QDebug>

#define GOOGLE_FEEDS "https://www.google.com/m8/feeds"
#define GOOGLE_CONTACTS "/contacts/default"


QtgdataContactsClient::QtgdataContactsClient(IAuthentication *auth, QObject *parent) :
    QtgdataClient(parent)
{
    setAuthenticationData(auth);
}

void QtgdataContactsClient::retrieveAllContacts()
{
    HttpRequest *request = authenticatedRequest();
    request->setRequestEndpoint(QUrl(QString(GOOGLE_FEEDS) + QString(GOOGLE_CONTACTS) + "/full"));
    request->setHttpMethod(HttpRequest::GET);
    request->setAuthHeader();
    connect(&(this->httpConnector), SIGNAL(requestFinished(QByteArray)), this, SLOT(onRetrieveAllContactsFinished(QByteArray)));
    this->httpConnector.httpRequest(request);
    delete request;
}

void QtgdataContactsClient::onRetrieveAllContactsFinished(QByteArray reply)
{
#ifdef QTGDATA_DEBUG
    qDebug() << "onRetrieveAllContactsFinished";
#endif
    XMLParser parser;
    try {
        IEntity *entity = parser.parse(reply,reply.size());
#ifdef QTGDATA_DEBUG
        qDebug() << entity->toString();
#endif
    } catch(XMLParserException e) {
        qDebug() << e.what();
    }
}

