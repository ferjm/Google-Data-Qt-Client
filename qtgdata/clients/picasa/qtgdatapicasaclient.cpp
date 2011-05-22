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
    atomFeed = new AtomFeed();
    return atomFeed;
}

AtomEntry* QtgdataPicasaClient::createAtomEntry()
{
    return new AtomEntry();
}

void QtgdataPicasaClient::emitAtomFeedRetrieved()
{
    if(atomFeed)
    {
        AtomFeed *feed = dynamic_cast<AtomFeed*>(atomFeed);
        if(feed) emit picasaFeedRetrieved(feed);
    }
}

const int QtgdataPicasaClient::appendEntry(AtomEntry *entry)
{
    AtomFeed* feed = dynamic_cast<AtomFeed*>(atomFeed);
    if(feed) feed->entries.append(entry);
    else return -1;
    return 0;
}

void QtgdataPicasaClient::parseEntry(int id,AtomEntry *atomEntry,IEntity *entry)
{
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
