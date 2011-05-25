/***************************************************************************
 *   Copyright (C) 2010-2011 Fernando Jiménez Moreno <ferjmoreno@gmail.com>*
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

#ifndef QTGDATAPICASACLIENT_H
#define QTGDATAPICASACLIENT_H

#include "qtgdataclient.h"
#include "qtgdatapicasadata.h"

/**
  \class QtgdataPicasaClient
  Picasa Web Albums allows client applications to view and update albums, photos,
  and comments in the form of Google Data API feeds. Your client application can
  use the Picasa Web Albums Data API to create new albums, upload photos, add
  comments, edit or delete existing albums, photos, and comments, and query for
  items that match particular criteria.
 */
class QtgdataPicasaClient : public QtgdataClient
{
    Q_OBJECT
public:
    enum PicasaClientReturnCode
    {
        OK = 0
    };

    explicit QtgdataPicasaClient(IAuthentication *auth, int version = 2, QObject *parent = 0);
    virtual ~QtgdataPicasaClient();

    virtual AtomFeedBase* createAtomFeed();
    virtual AtomEntry* createAtomEntry();
    virtual const int appendEntry(AtomEntry *entry);
    virtual void emitAtomFeedRetrieved();
    virtual void parseEntry(int id,AtomEntry *atomEntry,IEntity *entry);
    virtual void parseFeed(IEntity *entity);

    /**
      * Get a feed listing all of the albums belonging to user userID
      * @param userID ID of the owner of the albums to retrieve.
      * The string 'default' can be used in place of a real user ID, in which
      * case the server uses the ID of the user whose credentials authenticated the request.      
      * @param queryParams <a href=http://code.google.com/apis/picasaweb/docs/2.0/reference.html#Parameters>
      * List of supported query parameters</a>
      * @return picasaClientReturnCode
      */
    PicasaClientReturnCode retrieveListOfAlbums(QString userID = "default",
                                                QString queryParams = QString());

signals:
    void picasaFeedRetrieved(PicasaFeed*);

public slots:

};

#endif // QTGDATAPICASACLIENT_H
