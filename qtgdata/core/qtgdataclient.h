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

/**
  \class QtgdataClient
  Base class for any Qtgdata API client
  */
class QtgdataClient : public QObject
{
    Q_OBJECT

protected:
    //for now the only authentication supported is oauth v1.0
    enum AuthenticationMode { OAUTH_1_0 } authenticationMode;

    HttpConnector httpConnector;
    IAuthentication *authenticationData;
    int version;

    HttpRequest* authenticatedRequest();
public:
    /**
      Constructor QtgdataClient
      Creates a new QtgdataClient object      
      */
    QtgdataClient(int version, QObject *parent = 0);

    /**
      Destructor
      */
    ~QtgdataClient();

    void setAuthenticationData(IAuthentication *authenticationData);    
};

#endif // QTGDATACLIENT_H
