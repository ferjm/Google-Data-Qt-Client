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

#ifndef QTGDATACLIENT_H
#define QTGDATACLIENT_H

#include <QObject>

#include "qtgdatahttpconnector.h"
#include "qtgdataiauthentication.h"
#include "qtgdataatomentry.h"

/**
  \class QtgdataClient
  Base class for any Qtgdata API client
  */
class QtgdataClient : public QObject
{
    Q_OBJECT

public:
    /**
      Constructor QtgdataClient
      Creates a new QtgdataClient object
      */
    QtgdataClient(int version, QObject *parent = 0);

    /**
      Destructor
      */
    virtual ~QtgdataClient();

    void setAuthenticationData(IAuthentication *authenticationData);

protected:    
    //for now the only authentication supported is oauth v1.0
    enum AuthenticationMode { OAUTH_1_0 } authenticationMode;
    enum ClientID { BASE, BLOGGER, CODESEARCH } ID;

    HttpConnector httpConnector;
    IAuthentication *authenticationData;
    int version;    
    AtomFeedBase *atomFeed;

    HttpRequest* authenticatedRequest();
    void sendClientRequest(HttpRequest::RequestHttpMethod method,
                           QUrl endpoint,
                           QList<QPair<QByteArray,QByteArray> > &headers,
                           QByteArray *body = NULL,
                           bool oauth = true);    
    virtual AtomFeedBase* createAtomFeed() = 0;
    virtual AtomEntry* createAtomEntry() = 0;
    virtual const int appendEntry(AtomEntry *entry) = 0;
    virtual void emitAtomFeedRetrieved() = 0;
    virtual void parseEntry(int id,AtomEntry *atomEntry,IEntity *entry) = 0;

protected slots:
    void onAtomFeedRetrieved(QByteArray reply);       
};

#endif // QTGDATACLIENT_H
