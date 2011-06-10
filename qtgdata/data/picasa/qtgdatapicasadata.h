/***************************************************************************
 *   Copyright (C) 2010-2011 Fernando Jiménez Moreno <ferjmoreno@gmail.com>*
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
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


#ifndef QTGDATAPICASADATA_H
#define QTGDATAPICASADATA_H

#include "qtgdataatomentry.h"

/*!
  */
class GPhoto
{
public:
    QString gphotoId; /*! The ID of the current element. */
    QString albumId; /*! The album's ID. */
    QString access; /*! The album's access level */
    QString timestamp; /*! The photo's timestamp, represented as
                           the number of milliseconds since January 1st, 1970.
                           Contains the date of the photo either set externally
                           or retrieved from the Exif data. */
    QString user; /*! The user's username. This is the name that is used in all feed URLs. */
    QString nickName; /*! The user's nickname. This is a user-specified value that should be
                          used when referring to the user by name.*/
    QString albumType;
    QString location; /*! The user-specified location associated with the album. */
    QString snippet; /*! Snippet that matches the search text. */
    enum SnippetType { PHOTO_DESCRIPTION,
                       PHOTO_TAGS,
                       ALBUM_TITLE,
                       ALBUM_DESCRIPTION,
                       ALBUM_LOCATION } snippetType; /*! Describes where the match with the search query was found,
                                                        and thus where the snippet is from: the photo caption,
                                                        the photo tags, the album title, the album description,
                                                        or the album location.Possible values are . */
    bool truncated; /*! Indicates whether search results are truncated or not */
    int numPhotos; /*! The number of photos in the album. */
    int numPhotosRemaining; /*! The number of remaining photo uploads allowed in this album.
                                This is equivalent to the user's maximum number of photos per album
                                (<gphoto:maxPhotosPerAlbum>) minus the number of photos currently
                                in the album (<gphoto:numphotos>). */
    int maxPhotosPerAlbum; /*! The maximum number of photos allowed in an album. */
    int quotaCurrent; /*! The number of bytes of storage currently in use by the user. */
    int quotaLimit; /*! The total amount of space allotted to the user. */
    long int bytesUsed; /*! The number of bytes of storage that this album uses. */
    QUrl thumbnail; /*! The URL of a thumbnail-sized portrait of the user.*/
};

/*!
  \class MediaContent
  Contains the URL and other information about the full version of the entry's media content
  */
class MediaContent
{
public:
    QUrl url; /*! The URL of the full version of the media for the current entry.*/
    QString type; /*! The MIME type of the media. */
    QString medium; /*! Either image or video. Somewhat redundant, as type contains a more
                    specific MIME type, but medium may be simpler for the client to interpret*/
    int height; /*! The height of the image or video represented by this <media:content> element. */
    int width; /*! The width of the image or video represented by this <media:content> element. */
    long int fileSize; /*! The file size in bytes of the image or video represented by this <media:content> element. */
};

/*!
  \class MediaThumbnail
  Contains the URL of a thumbnail of a photo or album cover.
  */
class MediaThumbnail
{
public:
    QUrl url; /*! The URL of the thumbnail image. */
    int height; /*! The height of the thumbnail image */
    int width; /*! The width of the thumbnail image */
};

/*!
  \class MediaGroup
  Picasa Web Albums uses the media (http://search.yahoo.com/mrss/) namespace for elements defined
  in the Media RSS specification. For information about the media namespace,
  <a href="http://search.yahoo.com/mrss">see the Media RSS specification.</a>
  */
class MediaGroup
{
public:
    MediaThumbnail thumbnail; /*! Contains the URL of a thumbnail of a photo or album cover. */
    MediaContent content; /*! Contains the URL and other information about the full version of the entry's media content */
    QString title; /*! Contains the title of the entry's media content, in plain text. */
    QString credit; /*! Contains the nickname of the user who created the content.
                        This is a user-specified value that should be used when referring to the user by name. */
    QStringList keywords; /*! Lists the tags associated with the entry.
                            Tags are limited to 128 characters and 100 tags per item.
                            Tags use the UTF-8 character set, so they are not limited to ASCII.*/
};

class PicasaEntry : public AtomEntry
{
public:
    virtual ~PicasaEntry()
    {

    }

    QDateTime edited;
    QString rights;
    MediaGroup mediaGroup;
    GPhoto gphoto;
};

class PicasaFeed : public AtomFeedBase
{
public:
    QList<PicasaEntry*> entries;
    GPhoto gphoto;
    virtual void clear() {
        this->id.clear();
        this->title.clear();
        this->authors.clear();
        this->categories.clear();
        this->links.clear();
        //this->gPhoto->clear();
        for(int i=0;i<this->entries.size();i++)
            if(this->entries.at(i) != NULL) delete this->entries.at(i);
        this->published = QDateTime();
    }
};

#endif // QTGDATAPICASADATA_H
