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
    /*!
      Creates a new QtgdataClient object
      */
    QtgdataClient(int version, QObject *parent = 0);
    /**
      Destructor
      */
    virtual ~QtgdataClient();

    //! Sets the client authentication data.
    /*!
      \param authenticationData Client authentication parameters
    */
    void setAuthenticationData(IAuthentication *authenticationData);

protected:    
    // now the only authentication supported is oauth v1.0
    enum AuthenticationMode { OAUTH_1_0 } authenticationMode;
    enum ClientID { BASE, BLOGGER, CODESEARCH, PICASA } ID;

    /*! Instance of the HttpConnector used to send
     * and receive clients requests to the servers */
    HttpConnector httpConnector;
    /*! Client authentication data */
    IAuthentication *authenticationData;
    /*! Google Data Protocol version */
    int version;
    /*! Contains the last atom feed retrieved from the server */
    AtomFeedBase *atomFeed;

    /*! \returns instance of an authenticated http request object*/
    HttpRequest* authenticatedRequest();
    /*! Helper function for child class to send a client request
     * \param method The type of HTTP request method (GET, POST, PUT, HEAD or DELETE)
     * \param endpoint URL of the service endpoint to send the HTTP request
     * \param headers List of HTTP headers that will be sent within the HTTP request.
     *  Note that there is no need to include the authorization header to this list.
     * \param body Request body. Note that you must set the content-type header according
     *  the body type. Default value is NULL.
     * \param oauth If true, the authorization header will be included within the request.
     */
    void sendClientRequest(HttpRequest::RequestHttpMethod method,
                           QUrl endpoint,
                           QList<QPair<QByteArray,QByteArray> > &headers,
                           QByteArray *body = NULL,
                           bool oauth = true);
    /*!
     * Pure virtual function returning an specific AtomFeedBase child object
     * used by the QtgdataClient child specialization
     * \returns AtomFeedBase* child */
    virtual AtomFeedBase* createAtomFeed() = 0;
    /*!
     * Pure virtual function returning an specific AtomEntry child object
     * used by the QtgdataClient child specialization
     * \returns AtomEntry* child*/
    virtual AtomEntry* createAtomEntry() = 0;
    /*!
     * Appends a new entry to the QtgdataClient atomFeed field
     * \returns QTGDATA_SUCCESS if the entry is correctly appended
     */
    virtual const int appendEntry(AtomEntry *entry) = 0;
    /*!
     * Pure virtual helper function that would emit an specific
     * client child signal in the event of an atom feed retrieved
     */
    virtual void emitAtomFeedRetrieved() = 0;
    /*!
     * Pure virtual function to parse an specific entry within the
     * child client.
     */
    virtual void parseEntry(int id,AtomEntry *atomEntry,IEntity *entry) = 0;
    /*!
     * Pure virtual function to parse an specific feed within the
     * child client.
     *
     */
    virtual void parseFeed(IEntity *entity) = 0;

protected slots:
    void onAtomFeedRetrieved(QByteArray reply);       
};

#endif // QTGDATACLIENT_H
