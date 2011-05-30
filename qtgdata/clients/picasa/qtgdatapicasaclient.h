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

/*!
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
    explicit QtgdataPicasaClient(IAuthentication *auth, int version = 2, QObject *parent = 0);
    virtual ~QtgdataPicasaClient();

    virtual AtomFeedBase* createAtomFeed();
    virtual AtomEntry* createAtomEntry();
    virtual const int appendEntry(AtomEntry *entry);
    virtual void emitAtomFeedRetrieved();
    virtual void parseEntry(int id,AtomEntry *atomEntry,IEntity *entry);
    virtual void parseFeed(IEntity *entity);

    /*!
      * Get a feed listing all of the albums belonging to user userID
      * \param userID ID of the owner of the albums to retrieve.
      * The string 'default' can be used in place of a real user ID, in which
      * case the server uses the ID of the user whose credentials authenticated the request.      
      * \param queryParams <a href=http://code.google.com/apis/picasaweb/docs/2.0/reference.html#Parameters>
      * List of supported query parameters</a>
      * \returns QTGDATASuccess if the retrieval procedure has been successfully completed
      */
    QTGDATAReturnCode retrieveListOfAlbums(QString userID = "default",
                                           QString queryParams = QString());
    /*!
     * Creates a new album using the data you sent, the server returns an HTTP 201 status code,
     * along with a copy of the new album in the form of an <entry> element that can be retrieved
     * via the picasaFeedRetrieved signal or by calling the getLastFeedRetrieved() function.
     * The returned entry is similar to the one you sent, but it contains various elements
     * added by the server, such as an <id> element
     * \returns QTGDATASuccess if the creation procedure have been successfully completed
     */
    QTGDATAReturnCode createAlbum(PicasaEntry &album);
    /*!
     * After retrieving an album entry, you can modify it using this function,
     * with the modified album data as parameter.
     * \param album The album entry with the modifications to commit to the server.
     * \param eTag if you want to  make sure that your update doesn't overwrite
     *  another client's changes, you must provide the album's ETag value.
     *  You can determine the original album's ETag value by examining the entry
     *  element's etag attribute.
     * \returns QTGDATASuccess id the modification procedure have been successfully completed.
     */
    QTGDATAReturnCode updatedAlbum(PicasaEntry &album,
                                   QString eTag = QString());
    /*!
     * Deletes the album corresponding to albumID param.
     * \param albumID The ID of the album to be deleted
     * \param eTag If you want to make sure that you don't delete
     *  an album that has been changed by another client since
     *  you retrieved it, you must provide the album's ETag value.
     *  You can determine the original album's ETag value
     *  by examining the entry element's etag attribute.
     *  \returns QTGDATASuccess if the deletion procedure
     *  have been successfully completed
     */
    QTGDATAReturnCode deleteAlbum(QString albumID,
                                  QString eTag = QString());



signals:
    /**
      * Signal emited when picasa feeds are retrieved from the server.
      */
    void picasaFeedRetrieved(PicasaFeed*);

public slots:

};

#endif // QTGDATAPICASACLIENT_H
