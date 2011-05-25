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

#include "qtgdatapicasaclient.h"

#define PICASA_BASE "https://picasaweb.google.com/data"

QtgdataPicasaClient::QtgdataPicasaClient(IAuthentication *auth, int version, QObject *parent) :
    QtgdataClient(version,parent)
{
    ID = PICASA;
    setAuthenticationData(auth);
}

QtgdataPicasaClient::~QtgdataPicasaClient()
{

}

AtomFeedBase* QtgdataPicasaClient::createAtomFeed()
{
    if(atomFeed) delete atomFeed;
    atomFeed = new PicasaFeed();
    return atomFeed;
}

AtomEntry* QtgdataPicasaClient::createAtomEntry()
{
    return new PicasaEntry();
}

void QtgdataPicasaClient::emitAtomFeedRetrieved()
{
    if(atomFeed)
    {
        PicasaFeed *feed = dynamic_cast<PicasaFeed*>(atomFeed);
        if(feed) emit picasaFeedRetrieved(feed);
    }
}

const int QtgdataPicasaClient::appendEntry(AtomEntry *entry)
{
    PicasaFeed* pfeed = dynamic_cast<PicasaFeed*>(atomFeed);
    PicasaEntry* pentry = dynamic_cast<PicasaEntry*>(entry);
    if(pfeed) pfeed->entries.append(pentry);
    else return -1;
    return 0;
}

void QtgdataPicasaClient::parseEntry(int id,AtomEntry *atomEntry,IEntity *entry)
{
    PicasaEntry *picasaEntry = dynamic_cast<PicasaEntry*>(atomEntry);
    if(picasaEntry)
    {
        switch(id)
        {
        case Id::nickname:
            picasaEntry->gphoto.nickName = entry->getValue();
            break;
        case Id::user:
            picasaEntry->gphoto.user = entry->getValue();
            break;
        case Id::thumbnail:
            picasaEntry->gphoto.thumbnail = QUrl(entry->getValue());
            break;
        case Id::quotalimit:
            picasaEntry->gphoto.quotaLimit = entry->getValue().toInt();
            break;
        case Id::quotacurrent:
            picasaEntry->gphoto.quotaCurrent = entry->getValue().toInt();
            break;
        case Id::maxPhotosPerAlbum:
            picasaEntry->gphoto.maxPhotosPerAlbum = entry->getValue().toInt();
            break;
        case Id::edited:
            picasaEntry->edited.fromString(entry->getValue(),Qt::ISODate);
            break;
        case Id::rights:
            picasaEntry->rights = entry->getValue();
            break;
        case Id::id:
            if(entry->getNamespaceId() == NamespaceId::gphoto)
                picasaEntry->gphoto.gphotoId = entry->getValue();
            break;
        case Id::access:
            if(entry->getNamespaceId() == NamespaceId::gphoto)
                picasaEntry->gphoto.access = entry->getValue();
            break;
        case Id::timestamp:
            if(entry->getNamespaceId() == NamespaceId::gphoto)
                picasaEntry->gphoto.timestamp = entry->getValue();
            break;
        case Id::numphotos:
            if(entry->getNamespaceId() == NamespaceId::gphoto)
                picasaEntry->gphoto.numPhotos = entry->getValue().toInt();
            break;
        case Id::numphotosremaining:
            if(entry->getNamespaceId() == NamespaceId::gphoto)
                picasaEntry->gphoto.numPhotosRemaining = entry->getValue().toInt();
            break;
        case Id::bytesUsed:
            if(entry->getNamespaceId() == NamespaceId::gphoto)
                picasaEntry->gphoto.bytesUsed = entry->getValue().toInt();
            break;
        case Id::albumType:
            if(entry->getNamespaceId() == NamespaceId::gphoto)
                picasaEntry->gphoto.albumType = entry->getValue();
            break;
        case Id::group:
            if(entry->getNamespaceId() == NamespaceId::media)
            {
                IEntity::itConstEntities begin,end;
                entry->getEntityList(begin,end);
                if(begin != end)
                {
                    for(IEntity::itConstEntities it = begin; it != end; it++)
                    {
                        IEntity *sit = dynamic_cast<IEntity *>(*it);
                        switch(sit->getId())
                        {
                        case Id::content:
                            picasaEntry->mediaGroup.content.url = QUrl(sit->getAttribute(AttributeId::url)->sValue);
                            picasaEntry->mediaGroup.content.type = sit->getAttribute(AttributeId::type)->sValue;
                            break;
                        case Id::credit:
                            picasaEntry->mediaGroup.credit = sit->getValue();
                            break;
                         case Id::thumbnail:
                            picasaEntry->mediaGroup.thumbnail.url = QUrl(sit->getAttribute(AttributeId::url)->sValue);
                            picasaEntry->mediaGroup.thumbnail.height = sit->getAttribute(AttributeId::height)->sValue.toInt();
                            picasaEntry->mediaGroup.thumbnail.width = sit->getAttribute(AttributeId::width)->sValue.toInt();
                            break;
                         case Id::title:
                            picasaEntry->mediaGroup.title = sit->getValue();
                            break;
                         default:
                            break;
                        }
                    }
                }
            }
        default:
            break;
        }
    }
}

void QtgdataPicasaClient::parseFeed(IEntity *entity)
{
    PicasaFeed *picasaFeed = dynamic_cast<PicasaFeed*>(atomFeed);
    if(picasaFeed)
    {
        int id = entity->getId();
        switch(id)
        {
        case Id::nickname:
            picasaFeed->gphoto.nickName = entity->getValue();
            break;
        case Id::user:
            picasaFeed->gphoto.user = entity->getValue();
            break;
        case Id::thumbnail:
            picasaFeed->gphoto.thumbnail = QUrl(entity->getValue());
            break;
        case Id::quotalimit:
            picasaFeed->gphoto.quotaLimit = entity->getValue().toInt();
            break;
        case Id::quotacurrent:
            picasaFeed->gphoto.quotaCurrent = entity->getValue().toInt();
            break;
        case Id::maxPhotosPerAlbum:
            picasaFeed->gphoto.maxPhotosPerAlbum = entity->getValue().toInt();
            break;
        default:
            break;
        }
    }
}

QtgdataPicasaClient::PicasaClientReturnCode
QtgdataPicasaClient::retrieveListOfAlbums(QString userID,
                                          QString queryParams)
{
    QList<QPair<QByteArray,QByteArray> > headers;
    headers.append(qMakePair(QByteArray("GData-Version"),QByteArray::number(this->version)));
    QString endpoint = QString(PICASA_BASE) + "/feed/api/user/" + userID;
    sendClientRequest(HttpRequest::GET,
                      QUrl(endpoint),
                      headers,
                      NULL);
    return OK;
}
